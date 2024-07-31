/*--------------NodeMCU_ThinkSpeak-------------------*/
/*-------------Source Code by---------------------------*/
/*------Modified & Adapted by Habib.m @Hab_mz-----------*/
/*-----------------------V1.1---------------------------*/

#include <ThingSpeak.h>               // add librery
#include <ESP8266WiFi.h>

WiFiClient  client;
unsigned long counterChannelNumber =  1501549;                // Channel ID
const char * myCounterReadAPIKey = "SJUFSL3Z34Q9WTTU";     // Read API Key
const int FieldNumber1 = 1;                                 // The field you wish to read
const int FieldNumber2 = 2;                                 // The field you wish to read

void setup()
{
  pinMode(13,OUTPUT);
  pinMode(15,OUTPUT);
  Serial.begin(115200);
  Serial.println();

  WiFi.begin("kucing santo", "dodi1997");                     // write wifi name & password           

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
  ThingSpeak.begin(client);
}

void loop() 
{
 int A = ThingSpeak.readLongField(counterChannelNumber, FieldNumber1, myCounterReadAPIKey);
 Serial.println(A);
 digitalWrite(13,A);
 int B = ThingSpeak.readLongField(counterChannelNumber, FieldNumber2, myCounterReadAPIKey);
 Serial.println(B);
 digitalWrite(15,B);
}
