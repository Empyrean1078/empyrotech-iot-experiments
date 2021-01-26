/* Including the C standard library----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
#include <sys/unistd.h>
#include <stdlib.h>
/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/





/* Including the String library--------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
#include <string.h>
/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/





/* Including the FreeRTOS libraries ---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"
/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/





/* Including the wifi library ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
#include "WiFi.h"
/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/





/* Including the HTTP client library---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
#include <HTTPClient.h>
/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/





/* Including the DHT 11 library---------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
#include "DHTesp.h"
/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/





/* WiFi related -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/* The wifi manage task stack size in bytes*/
#define WIFI_MANAGER_STACK_SIZE 2000

#define WIFI_LED 22

/* Maximum time (in seconds) for which the device can stay disconnected from access point. If the device is disconnected from access point for this time period then, the chip will reboot. Change it accordingly */
#define MAX_WIFI_DISCONNECTED_PERIOD 120

/* ! PUT YOUR OWN WIFI CREDENTIALS BELOW ! */
const char * wifi_ssid="SSID";
const char * wifi_pass="PASSWORD";

/* this variable stores the status of wifi connection*/
char wifi_connected=0;

/* This variable stores the time (in seconds) for which the device has been disconnected from the a access point*/
uint32_t wifi_disconnected_period=0;

/* The declaration of wifi manager task/process */
void wifi_manager(void *);

/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/





/* DHT11 SENSOR RELATED VARIABLES AND OBJECTS ----------------------------------------------------------------------------------------------------------------------------------------------------------*/

/* This is the pin which the output of DHT11 sensor is connected to.*/
#define DHT11_PIN 18

DHTesp sensor;
/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/





/* LOGGER ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

#define LOGGER_ENABLED 1

typedef enum esp_logger_cat { LOG, EVENT, ERR, WARNING, CONTENT } esp_logger_cat;

void LOGGER( esp_logger_cat, char *, char *, int8_t);
/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/




/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

#define UPDATE_LED 19

#define S_TO_uS_FACTOR 1000000

/* This is the interval in seconds*/
#define SLEEP_INTERVAL_SECS 1800

String timeStamp;

String server_url="http://api.thingspeak.com/update?apikey=<CHANNEL WRITE API KEY>&field1=";

uint8_t sendReadingToServer(String, double, String);
/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/





/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

String world_time_api_url="http://worldtimeapi.org/api/timezone/";

class INTERNET_TIME
{
  private:
    String requestPath;

    String getParameter(String, String);
    
  public:
    INTERNET_TIME(String);

    String getTime(void);

    String getDate(void);

    String getDateTime(void);

    String getDateTimeUTC(void);

    uint32_t getUnixTime(void);
};

INTERNET_TIME local_clock( String("Asia/Kolkata") );
/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/





/* ONE TIME FUNCTION - USED FOR VARIOUS INITIALIZATIONS AND DRIVER INSTALLATIONS */
void setup()
{
  Serial.begin(9600);

  sensor.setup(DHT11_PIN, DHTesp::DHT11);

  pinMode( WIFI_LED, OUTPUT);
  pinMode( UPDATE_LED, OUTPUT);

  digitalWrite( WIFI_LED, LOW);
  digitalWrite( UPDATE_LED, LOW);

  LOGGER( EVENT, "DEVICE", "BOOTED", 0);

  /* creating the wifi manager task */
  BaseType_t er=xTaskCreate(wifi_manager, "WIFI MANAGER TASK", WIFI_MANAGER_STACK_SIZE, NULL, 10, NULL);
  if( er != pdTRUE )
  {
    LOGGER(ERR, "WIFI TASK", "INIT FAILED", 0);
    LOGGER(LOG, "REBOOTING", "chip will shortly reboot", 0);
    delay(2000);
    esp_restart();
  }

  LOGGER(LOG, "WIFI TASK", "CREATED", 0);

  LOGGER(LOG, "WIFI CONNECTION", "connecting to access point", 0);

  /* wait until wifi connection is eastablished*/
  while( !wifi_connected )
  {
    delay(1000);
    Serial.print("# ");
  }
  Serial.println();

  LOGGER(EVENT, "WIFI CONNECTION", "connected to access point", 0);
}
/* INFINITE LOOPING FUNCTION - USED FOR REPEATEDLY PERFORMING SOME TASK */
void loop()
{
  if( wifi_connected )
  {
    // obtain the timestamp in UTC time. Thinspeak will automatically add the offset while displaying it in the field chart.
    timeStamp = local_clock.getDateTimeUTC();

    if( ! timeStamp.equals("failed") )
    {
      LOGGER( LOG, "DATA PUSH", "sending data", 1);
      
      sendReadingToServer(server_url, sensor.getTemperature(), timeStamp );

      //flash the update led to indicate the same
      for(uint8_t i=1; i<=5; i++)
      {
        digitalWrite(UPDATE_LED,HIGH);
        delay(250);
        digitalWrite(UPDATE_LED,LOW);
        delay(250);
      }

      // setup the wakeup timer
      esp_sleep_enable_timer_wakeup( SLEEP_INTERVAL_SECS * S_TO_uS_FACTOR );

      LOGGER( LOG, "DEVICE", "going to deep sleep", 0);

      delay(100);

      //go to deep sleep
      esp_deep_sleep_start();
    }
    else
    {
      LOGGER( LOG, "DATA PUSH", "failed to obtain timestamp", 1);
      delay(5000);
    }
  }
  else
  {
    LOGGER( WARNING, "DATA PUSH", "not connected to access point", 0);
    delay(5000);
  }
}





/* THE WIFI MANAGER TASK/PROCESS; THIS TASK RUNS IN PARALLEL WITH THE void loop() TASK AND WILL KEEP TRACK OF THE WIFI CONNECTION; IF THE WIFI IS DISCONNECTED FROM ACCESS POINT FOR LONG ENOUGH THEN THIS
TASK WILL REBOOT THE CHIP*/
void wifi_manager(void * args)
{
  WiFi.begin(wifi_ssid, wifi_pass);
  
  while( 1 )
  {
    if(WiFi.status() != WL_CONNECTED )
    {
      digitalWrite( WIFI_LED, LOW );
      wifi_connected=0;
      wifi_disconnected_period++;
      
      if( wifi_disconnected_period >= MAX_WIFI_DISCONNECTED_PERIOD )
      {
        esp_restart();
      }
    }
    else
    {
      digitalWrite( WIFI_LED, HIGH );
      wifi_connected=1;
      wifi_disconnected_period=0;
    }
    delay(1000);
  }
}





/* This is a helper API that uses the Serial functions; it provides a convinient way to log messages from ESP32 to Serial Monitor 
 PARAMETERS -
 1. esp_logger_cat type : category of the message to be logged.
 2. char * tag : tag string; this is optional and may be set to NULL.
 3. char * msg : the actual logging message.
 4. int8_t indent : integer indentation level.
*/
void LOGGER(esp_logger_cat type, char * tag, char * msg, int8_t indent)
{
  if( LOGGER_ENABLED )
  {
    if(!indent)
      Serial.print("\n>>>");
    else
    {
      Serial.println("");
      for(;indent>0;indent--)
      {
        Serial.print(" ");
      }
      Serial.print(">>>");

    }

    switch( type )
    {
    case LOG:
      Serial.print("ESP-LOG, [ ");
      break;

    case EVENT:
      Serial.print("ESP-EVENT, [ ");
      break;

    case WARNING:
      Serial.print("ESP-WARNING, [ ");
      break;

    case ERR:
      Serial.print("ESP-ERROR, [ ");
      break;

    case CONTENT:
      Serial.print("ESP-CONTENT, [ ");
      break;
    }

    if(tag!=NULL) Serial.print(tag);

    Serial.print(" ] : ");
    if(type==CONTENT) Serial.println("");

    Serial.println(msg);
  }
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/





/* HTTP REQUEST FUNCTIONS ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/* This API is used send a reading to a server as a part of the request url*/
uint8_t sendReadingToServer( String serverUrl, double reading, String dateTime)
{

  String serverPath = serverUrl + String(reading) + String("&created_at=") + dateTime;

  Serial.print("    ");
  Serial.print(serverPath + "    RESP CODE-    ");

  HTTPClient http;

  http.begin(serverPath);

  int respCode = http.GET();

  Serial.println(respCode);

  http.end();

  return 1;
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/


INTERNET_TIME :: INTERNET_TIME( String _timeZone)
{
  // Creating the world time request path
  this->requestPath = world_time_api_url + _timeZone + String(".txt");
}

String INTERNET_TIME :: getTime(void)
{
  HTTPClient http;
  
  http.begin(requestPath);

  int respCode = http.GET();

  if( respCode == 200 )
  {
    String resp=http.getString();

    http.end();
    
    return (this->getParameter( resp, String("datetime") ) ).substring(11,19);
  }
  else
  {

    http.end();
    
    return String("failed");
  }
}

String INTERNET_TIME :: getDate(void)
{
  HTTPClient http;
  
  http.begin(requestPath);

  int respCode = http.GET();

  if( respCode == 200 )
  {
    String resp=http.getString();

    http.end();
    
    return (this->getParameter( resp, String("datetime") ) ).substring(0,10);
  }
  else
  {
    http.end();
    
    return String("failed");
  }
}

String INTERNET_TIME :: getDateTime(void)
{
  HTTPClient http;
  http.begin(requestPath);

  int respCode = http.GET();

  if( respCode == 200 )
  {
    String resp = http.getString();

    http.end();
    
    return (this->getParameter( resp, String("datetime") ) ).substring(0,19);
  }
  else
  {
    http.end();
    
    return String("failed");
  }
}

String INTERNET_TIME :: getDateTimeUTC(void)
{
  HTTPClient http;
  http.begin(requestPath);

  int respCode = http.GET();

  if( respCode == 200 )
  {
    String resp=http.getString();

    http.end();
    
    return ( (this->getParameter( resp, String("utc_datetime") ) ).substring(0,19) + String("Z") );
  }
  else
  {
    http.end();
    
    return String("failed");
  }
}

String INTERNET_TIME :: getParameter(String str, String key)
{
  // the index of the first character in the datetime String
  int start_ind_val = str.indexOf(key) + key.length() + 2 ;

  // index of the newline character after the datetime String
  int end_ind_val = str.indexOf( '\n', start_ind_val );

  return str.substring( start_ind_val, end_ind_val );
}

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
