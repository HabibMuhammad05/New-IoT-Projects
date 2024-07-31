#include <WiFiManager.h>
#define WiFiPB 5  //D1

void setup() {
  WiFi.mode(WIFI_STA);
  Serial.begin(115200);
  pinMode(WiFiPB, INPUT_PULLUP);
}

void loop() {
WiFiConfig();
}


void WiFiConfig(){
    if ( digitalRead(WiFiPB) == LOW){
    WiFiManager wm;    
    wm.setConfigPortalTimeout(120);//timeout 120s
      if (!wm.startConfigPortal("ESP8266_WiFi_Config")) {
        Serial.println("failed to connect and hit timeout");
        delay(3000);
        ESP.restart();
        delay(5000);
      }
    Serial.println("WiFi Connected");
  }
}
