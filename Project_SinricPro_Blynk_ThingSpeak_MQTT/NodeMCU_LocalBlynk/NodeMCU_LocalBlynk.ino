#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>             
#include <BlynkSimpleEsp8266.h>       

char auth[] = "ppvAdGBqBO8kD0VOuFVtvBX6cojt7IUY"; 
char ssid[] = "m";        
char pass[] = "1qazmlp0";


void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass, "iot.serangkota.go.id", 8080);
}

void loop() {
  Blynk.run();
  delay(10);
}
