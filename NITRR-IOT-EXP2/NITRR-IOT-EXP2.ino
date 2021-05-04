#include <WiFi.h>

/* Put your wifi credentials here*/
const char* ssid = "xxxx";
const char* password = "xxxx";

/* IP address and port of the echo server*/
const uint16_t port = 8534;
const char * host = "xx.xx.xx.xx";

void setup()
{
  Serial.begin(115200);
 
  /*Connect to WiFi*/
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("...");
  }
 
  Serial.print("WiFi connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
}

void loop()
{
  WiFiClient socket_client;
  
  if (!socket_client.connect(host, port)) 
  {
    /*This block will be executed when esp32 is not able to connect to the echo server*/
    Serial.println("Failed to connect to server!");
    delay(5000);
    Serial.println("Retrying...\n");
  }
  else
  {
    /*This block is executed after esp32 successfully eastablishes a TCP connection with echo server*/
    Serial.println("Connected to server...");
    socket_client.println("ping pong");
    Serial.println("Sent : ping pong");

    while(!socket_client.available()){}
    
    String str="";

    Serial.println(socket_client.available());

    while( socket_client.available() )
    {
      str=str+ (char)socket_client.read();
    }

    Serial.print("Echo :");
    Serial.println(str);

    Serial.println("Disconnecting...\n\n");
    socket_client.stop();
    delay(5000);
  }
}
