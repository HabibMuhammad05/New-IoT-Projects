#define ENABLE_DEBUG

#ifdef ENABLE_DEBUG
       #define DEBUG_ESP_PORT Serial
       #define NODEBUG_WEBSOCKETS
       #define NDEBUG
#endif 
#include <WiFiManager.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "SinricPro.h"
#include "SinricProTemperaturesensor.h"
#include "DHT.h"
DHT dht(0, DHT11);
#define WIFI_SSID         "ZAINI MIFTAH"  
#define WIFI_PASS         "120812rj"   
#define APP_KEY           "e519d19c-844b-4410-aeee-e245d7d630ce" 
#define APP_SECRET        "cfa7b221-b67b-4426-bd7d-c12a974a204d-250e69be-37a4-4c05-ae61-3bf6b848e653"   
#define TEMP_SENSOR_ID    "624962b9d0fd258c520846d2" 
#define EVENT_WAIT_TIME   60000
#define wifiLed   2  
#define WiFiPB 5
long sended;
long error;
bool deviceIsOn;                 
float temperature;                        
float humidity;                           
float lastTemperature;                     
float lastHumidity;                
unsigned long lastEvent = (-EVENT_WAIT_TIME); 

void setup() {
  Serial.begin(115200); 
  Serial.printf("\r\n\r\n");
  dht.begin();
  pinMode(WiFiPB, INPUT_PULLUP);
  pinMode(wifiLed, OUTPUT);
  digitalWrite(wifiLed, HIGH);

  setupWiFi();
  setupSinricPro();
}
void loop() {
  WiFiConfig();
  SinricPro.handle();
  handleTemperaturesensor();
}
