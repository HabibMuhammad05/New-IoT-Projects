//------------------------------------------------------Additional Lib----------------------------------//
#include "max7219.h"
#include "fonts.h"
#include "Lib_WiFi.h"
#include "Lib_Time.h"
#include "variables.h"
#include "Lib_Buzzer.h"
#include "Functions.h"

//------------------------------------------------------------------------------------------------------//
//------------------------------------------------------Void Setup--------------------------------------//
void setup() {
  Serial.begin(115200);
  pinMode(buzzer, OUTPUT);
  timeClient.begin();
  timeClient.setTimeOffset(25200); //3600 x gmt+7
  setSyncProvider(requestSync);
  initMAX7219();
  sendCmdAll(CMD_SHUTDOWN,1);
//------------------------------------------------------WiFi Connect------------------------------------//
  Serial.print("Connecting WiFi ");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    setCnt = !setCnt;
    Serial.print(".");
    printStringWithShift("Connecting            ",16);
    if(setCnt){ tone(buzzer,685); }
    else{ noTone(buzzer); }
    delay(500);}
  Serial.println("");
  Serial.print("Connected: "); Serial.println(WiFi.localIP());
  
//-----------------------------------------------------NTP Clock Setup----------------------------------//
  Serial.println("Getting data ...");
  printStringWithShift("load....",1);
  getTime();
  Serial.println("Data loaded");
  noTone(buzzer);
  WiFi.disconnect();
  clr();
  printStringWithShift("WiFioff",5);
  Serial.println("wifi Disconnect Success");
  HitungJadwalSholat();
}

//-----------------------------------------------------------------------------------------------------//
//------------------------------------------------------Void Loop--------------------------------------//
void loop() {
  GetDateTime();
  AlarmSholat();
  tampilinfo();
  brightSet();
}
 
