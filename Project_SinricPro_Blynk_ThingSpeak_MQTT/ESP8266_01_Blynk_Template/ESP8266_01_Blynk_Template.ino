/*----------------Esp8266-01 Blynk-------------------*/
/*-----------------Source Code by -------------------*/
/*------Modified & Adapted by Habib.m @Hab_mz--------*/
/*----------------------V1.0-------------------------*/

//Activates communication between the Blynk App and Serial Monitor:
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>  //Import a "ESP8266WiFi" library.
#include <BlynkSimpleEsp8266.h> //Import a "BlynkSimpleEsp8266" library.

//Authentication of account in the Blynk app.
char auth[] = "YourAuthToken";  //Enter the device's auth token code.

//Enter the WiFi credentials.
char ssid[] = "YourNetworkName";//Name of the Wi-Fi network.
char pass[] = "YourPassword"; //Wi-Fi network password.
  //Note: Set password to "" for open networks.

//Run the SETUP function only once after pressing Reset:
void setup() {
  //Starts Communication Serial:
  Serial.begin(9600);
  
  //Starts Wi-Fi communication:
  Blynk.begin(auth, ssid, pass);
}

//Run the LOOP function repeatedly.:
void loop() {
  //Starts communication with the Blynk application:
  Blynk.run();

  //Place the remaining code for your project.

  //Code break:
  delay(10);
}
