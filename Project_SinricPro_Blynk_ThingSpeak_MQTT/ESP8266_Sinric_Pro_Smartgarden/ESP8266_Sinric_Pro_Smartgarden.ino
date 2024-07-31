#include <ESP8266WiFi.h>
#include <Arduino.h>
#include "SinricPro.h"
#include "SinricProSwitch.h"
#include "SinricProTemperaturesensor.h"
#include <map>

#include <BlynkSimpleEsp8266.h>
char auth[] = "D5pjpK_LPOGpPiAGmRRzrcVxwZbxYL-i"; 
char ssid[] = "m_m_m";        
char pass[] = "1qazmlp0";

#include <DHT.h>
DHT dht(0, DHT11); 
BlynkTimer timer;

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
#define TEMP_SENSOR_ID    "624962b9d0fd258c520846d2" 
#define EVENT_WAIT_TIME   60000
#define DEBOUNCE_TIME     250

#define device_ID_1     "62f3b8fadb27003734164367"
#define device_ID_2     "62f3b646da0cc632436c19a8"

#define wifiLed   2   //D4
#define RelayPin1 15  //D8
#define RelayPin2 13  //D7
#define RelayPin3 12 //D6

#define TACTILE_BUTTON 1
#define SwitchPin1 5  //D1
#define SwitchPin2 4   //D2
#define SwitchPin3 2  //D4


bool deviceIsOn;                 
float temperature;                        
float humidity;                           
float lastTemperature;                     
float lastHumidity;                
unsigned long lastEvent = (-EVENT_WAIT_TIME); 

void setup(){
  Serial.begin(115200);
  Serial.printf("\r\n\r\n");
  dht.begin();
  Blynk.begin(auth, ssid, pass, "iot.serangkota.go.id", 8080);

  pinMode(wifiLed, OUTPUT);
  digitalWrite(wifiLed, HIGH);

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
}
