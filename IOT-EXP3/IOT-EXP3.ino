#include <WiFi.h>
#include <WiFiUdp.h>

WiFiUDP udp;

/* Put your wifi credentials here*/
const char* ssid = "xxxx";
const char* password = "xxxx!";

/* IP address and port of the echo server*/
const char * udpAddress = "x.x.x.x";
const int udpPort = 45555;

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

void loop(){
  //only send data when connected
  Serial.println("Sending");
  //Send a packet
  udp.beginPacket(udpAddress,udpPort);
  udp.printf("Seconds since boot: %lu", millis()/1000);
  udp.endPacket();

  delay(10);
  
  int packetSize = udp.parsePacket();
  if(packetSize)
  {
    Serial.print("Echo - ");
    char buff[51]={0};
    udp.read(buff, 50);
    Serial.println(buff);
    Serial.println();
  }
  
  delay(5000);
}
