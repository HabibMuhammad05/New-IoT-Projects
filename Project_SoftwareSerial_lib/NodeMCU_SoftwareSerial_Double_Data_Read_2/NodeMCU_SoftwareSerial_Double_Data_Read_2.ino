#include <SoftwareSerial.h>
SoftwareSerial arduinoConnect (5, 4);

#include <Blynk.h>
BlynkTimer DataReadEvent;
BlynkTimer LEDBLINK;
String dataIn;
void setup() {
  Serial.begin(115200);
  arduinoConnect.begin(115200);
  Serial.println("work gan");

  DataReadEvent.setInterval(1000L, dataRead);
  LEDBLINK.setInterval(2000L, ledblink);
}

void loop() {
  DataReadEvent.run();
  LEDBLINK.run();
}


void dataRead(){
  dataIn = arduinoConnect.readString();
  dataIn.trim();
  Serial.println(dataIn); 
  int data = dataIn.toInt();

  if (data >= 2000 && data <= 3023){
    int VoltDataIn = data;
    VoltDataIn = VoltDataIn - 2000;
    Serial.print("Volt in = "); Serial.println(VoltDataIn);
     
    float voltage = VoltDataIn * (6.13/880);
    Serial.print("volt= "); Serial.println(voltage);
  }

  if (data >= 4000 && data <= 5023){
    int LightDataIn = data;
    LightDataIn = LightDataIn - 4000;
    Serial.print("llght in = "); Serial.println(LightDataIn);
     
    int LightDataCalc = map(LightDataIn, 130, 950, 0, 1023);
    Serial.print("light= "); Serial.println(LightDataCalc);
  }
}
  
void ledblink(){
  pinMode(2, OUTPUT);
  digitalWrite(2, !digitalRead(2)); }
