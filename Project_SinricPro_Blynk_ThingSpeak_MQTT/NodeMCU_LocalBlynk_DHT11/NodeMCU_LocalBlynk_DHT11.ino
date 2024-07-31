#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

DHT dht(0, DHT11); //0=d3 --(DHTPIN,DHTTYPE)(DHT11,DHT22)
BlynkTimer timer;

char auth[] = "ppvAdGBqBO8kD0VOuFVtvBX6cojt7IUY"; 
char ssid[] = "m";        
char pass[] = "1qazmlp0";
 
void setup(){
  dht.begin();
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass, "iot.serangkota.go.id", 8080);
  timer.setInterval(1000L, sendSensor);
}
 
void loop(){
  Blynk.run();
  timer.run();
}

void sendSensor(){
  float h = dht.readHumidity();
  float t = dht.readTemperature(); //dht.readTemperature(true) for Fahrenheit
    if (isnan(h) || isnan(t)) {
      Serial.println("Failed to read from DHT sensor!");
      return;}
  Blynk.virtualWrite(V5, t);
  Blynk.virtualWrite(V6, h);
}
