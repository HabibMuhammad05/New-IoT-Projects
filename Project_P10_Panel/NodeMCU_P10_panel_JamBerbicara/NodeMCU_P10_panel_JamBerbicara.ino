//UPLOAD SKETCH ON LOLIN (WEMOS) D1 MINI(CLONE)

//------------------------------------------------------Additional Lib----------------------------------//
#include "ESP8266WiFi.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include "DMDESP.h"
#include "TimeLib.h"
#include "NTPClient.h"
#include "WiFiUdp.h"
#include "PrayerTimes.h"

#include "SystemFont5x7.h"
#include "Font_6x14.h" 
#include "verdanav2.h"
#include "variables.h"
#include "Lib_Buzzer.h"
#include "Functions.h"

//------------------------------------------------------------------------------------------------------//
//------------------------------------------------------Void Setup--------------------------------------//
void setup() {
  Serial.begin(115200);
  pinMode(buzzer, OUTPUT);
  pinMode(tombol_jam, INPUT);

//  ConfigWifi();

//------------------------------------------------------WiFi Connect------------------------------------//
  Serial.print("Connecting WiFi ");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    setCnt = !setCnt;
    Serial.print(".");
    if(setCnt){ tone(buzzer,685); }
    else{ noTone(buzzer); }
    delay(500);}

  Serial.println("");
  Serial.print("Connected: "); Serial.println(WiFi.localIP());
  
  timeClient.begin();
  timeClient.setTimeOffset(25200); //3600 x gmt+7
  setSyncProvider(requestSync);
  Disp.start();
//-----------------------------------------------------NTP Clock Setup----------------------------------//
  //Serial.println("Getting data ...");
  getTime();
  Serial.println("Data loaded");
  noTone(buzzer);
  delay(2000);
  WiFi.disconnect();
  Serial.println("wifi Disconnect Success");
  HitungJadwalSholat();
  if (_hour24 == 0 || _hour24 == 00) {
    Serial.println(" Date Failed, Resetting...");
    ESP.restart();
  }

//----------------------------------------------------Audio Clock Setup--------------------------------//
  playercomms.begin(9600);
  mp3.begin(playercomms);
  mp3.volume(30);  //0-30
  pinMode(tombol_jam, INPUT);
}

//-----------------------------------------------------------------------------------------------------//
//------------------------------------------------------Void Loop--------------------------------------//
void loop() {
  Disp.loop();
  GetDateTime();
  AlarmSholat();
  tampilinfo();
  brightSet();
  bacaJam(jam24, _minute, false, false);
}
 
