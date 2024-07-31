#include <WiFiManager.h>
#define wifiLed   2   //D4

void setup() {
    Serial.begin(115200);
    pinMode(wifiLed, OUTPUT);
    digitalWrite(wifiLed, HIGH);
    
    SetWiFi();
}

void loop() {
  
}

void SetWiFi(){
  WiFi.mode(WIFI_STA);
    WiFiManager wm;
    bool res = wm.autoConnect("ESP8266_WiFi_Config","1qazmlp0");
    if(!res) {
        Serial.println("Failed to connect");
        for (int i; i<2;  i++) {
        digitalWrite(wifiLed, LOW);
        delay(500);
        digitalWrite(wifiLed, HIGH);
        delay(500);}} 
    else Serial.println("WiFi Connected"); digitalWrite(wifiLed, LOW);
}
