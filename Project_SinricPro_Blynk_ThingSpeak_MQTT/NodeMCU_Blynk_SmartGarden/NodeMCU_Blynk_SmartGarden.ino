#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

//char ssid[] = "m_m_m";
//char pass[] = "1qazmlp0";
char auth[] = "D5pjpK_LPOGpPiAGmRRzrcVxwZbxYL-i";
#define WIFI_SSID         "m_m_m"  
#define WIFI_PASS         "1qazmlp0" 

DHT dht(0, DHT11); //0=d3

BlynkTimer SoilMoisture_Time;
BlynkTimer DHT11_Time;

void setup(){
  Serial.begin(115200);
  dht.begin();
 
  Blynk.begin(auth, WIFI_SSID, WIFI_PASS, "iot.serangkota.go.id", 8080);
  pinMode(2,OUTPUT); digitalWrite(2,LOW);
 
  SoilMoisture_Time.setInterval(500L, SoilMoisture_Send);
  DHT11_Time.setInterval(1000L, DHT11_Send);
}
 
void loop(){
  Blynk.run();
  SoilMoisture_Time.run();
  DHT11_Time.run();
}

//--------------Soil Moisture Sensor Data Sending-----------------//
void SoilMoisture_Send(){
  float lembab = ( 100.00 - ( (analogRead(A0)/1024.00) * 100.00 ) );
  float teg = analogRead(A0);
  teg = map(teg, 0, 1024, 1024,0);
  float tegangan = ( 5.00 - ( (teg/1024.00) * 5.00 ) );
  Serial.print("Soil Moisture = "); 
  Serial.print(lembab); Serial.print("% - ");
  Serial.print(tegangan); Serial.println("V");
  
  Blynk.virtualWrite(V7, lembab);
  Blynk.virtualWrite(V8, tegangan);
}

//----------------------DHT11 Data Sending------------------------//
void DHT11_Send(){
  float temp = dht.readTemperature();
  float humid = dht.readHumidity();
  
   if (isnan(temp) || isnan(humid)) {
     Serial.println("Pembacaan DHT error!");
     return; }
     
  Serial.print("--------DHT11 = "); 
  Serial.print(temp); Serial.print("°c - ");
  Serial.print(humid); Serial.println("%");
  
  Blynk.virtualWrite(V5, temp);
  Blynk.virtualWrite(V6, humid);
}
