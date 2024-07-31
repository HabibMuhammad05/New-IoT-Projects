#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
 
char auth[] = "D5pjpK_LPOGpPiAGmRRzrcVxwZbxYL-i";
 
char ssid[] = "m_m_m";
char pass[] = "1qazmlp0";
 
DHT dht(0, DHT11); //0=d3

BlynkTimer timer;

void sendSensor(){
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
 
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Blynk.virtualWrite(V5, t);
  Blynk.virtualWrite(V6, h);
}
 
void setup(){
  Serial.begin(115200);
 
  Blynk.begin(auth, ssid, pass, "iot.serangkota.go.id", 8080);
  pinMode(2,OUTPUT);
  digitalWrite(2,LOW);
 
  dht.begin();
 
  timer.setInterval(1000L, sendSensor);
}
 
void loop()
{
  Blynk.run();
  timer.run();
}
