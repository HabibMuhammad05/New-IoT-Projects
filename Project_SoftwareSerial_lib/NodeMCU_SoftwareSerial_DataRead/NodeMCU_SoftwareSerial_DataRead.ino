#include <SoftwareSerial.h>
SoftwareSerial arduinoConnect (5, 4);

#include <Blynk.h>
BlynkTimer DataReadEvent;
BlynkTimer LEDBLINK;
String data;
void setup() {
  Serial.begin(115200);
  arduinoConnect.begin(115200);

  DataReadEvent.setInterval(1000L, dataRead);
  LEDBLINK.setInterval(2000L, ledblink);
}

void loop() {
  DataReadEvent.run();
  LEDBLINK.run();
}


void dataRead(){
  data = arduinoConnect.readString();
  data.trim();
  Serial.println(data); }
  
void ledblink(){
  pinMode(2, OUTPUT);
  digitalWrite(2, !digitalRead(2)); }
