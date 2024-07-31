/*------NodeMCU sinricpro + blynk smartgarden-----------*/
/*-------------Source Code by---------------------------*/
/*------Modified & Adapted by Habib.m @Hab_mz-----------*/
/*-----------------------V1.1---------------------------*/

#include <ESP8266WiFi.h>
#include <Arduino.h>
#include "SinricPro.h"
#include "SinricProSwitch.h"
#include "SinricProTemperaturesensor.h"
#include <map>

#include <SoftwareSerial.h>
SoftwareSerial arduinoConnect (5, 4); // (D1 , D2)

#include <DHT.h>
DHT dht(0, DHT11); //0=d3

#include <BlynkSimpleEsp8266.h>
char AUTH_KEY[] = "D5pjpK_LPOGpPiAGmRRzrcVxwZbxYL-i"; 

#include <Blynk.h>
BlynkTimer arduDataReadEvent;

BlynkTimer SoilMoisture_Time;
BlynkTimer DHT11_Time;

#define ENABLE_DEBUG

#ifdef ENABLE_DEBUG
       #define DEBUG_ESP_PORT Serial
       #define NODEBUG_WEBSOCKETS
       #define NDEBUG
#endif 

#define WIFI_SSID         "m_m_m"  
#define WIFI_PASS         "1qazmlp0" 
#define APP_KEY           "956119c8-34d4-40fb-b93c-e16302d4c62f"  
#define APP_SECRET        "d8a38f9c-2d4d-40de-81e0-40455a94bf4e-013d29fd-5609-47ad-a249-7247ae74e94c" 
#define TEMP_SENSOR_ID    "62f3b483da0cc632436c1880" 
#define EVENT_WAIT_TIME   60000
#define DEBOUNCE_TIME     250

#define device_ID_1     "62f3b8fadb27003734164367"
#define device_ID_2     "62f3b646da0cc632436c19a8"

#define wifiLed   2   //D4
#define RelayPin1 15  //D8
#define RelayPin2 13  //D7

#define TACTILE_BUTTON 1
#define SwitchPin1 12  //D6
#define SwitchPin2 14   //D5

bool deviceIsOn;   
float temp;
float humid;      
unsigned long lastEvent = (-EVENT_WAIT_TIME); 
String dataIn;

void setup(){
  Serial.begin(115200);
  arduinoConnect.begin(115200);
  dht.begin();
  Serial.println();
  Serial.println("Google Home Integration via SinricPro");
  Serial.println("Connecting To WiFi");
  Blynk.begin(AUTH_KEY, WIFI_SSID, WIFI_PASS, "iot.serangkota.go.id", 8080);
  pinMode(wifiLed, OUTPUT); digitalWrite(wifiLed, HIGH);
  pinMode(A0, INPUT);
  
  SoilMoisture_Time.setInterval(1000L, SoilMoisture_Send);
  DHT11_Time.setInterval(1000L, DHT11_Send);
  arduDataReadEvent.setInterval(2000L, ardudataRead);
  
  setupRelays();
  setupFlipSwitches();
  setupWiFi();
  setupSinricPro();
  setupSinricProTemp();
}

void loop(){
  SinricPro.handle();
  handleFlipSwitches();
  handleTemperaturesensor();
  Blynk.run();
  arduDataReadEvent.run();
  SoilMoisture_Time.run();
  DHT11_Time.run();
}
