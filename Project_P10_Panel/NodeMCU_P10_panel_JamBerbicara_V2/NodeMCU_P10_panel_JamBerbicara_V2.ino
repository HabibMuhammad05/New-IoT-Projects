/*---------------Wemos D1 P10 Panel Clock WITH VOICE--------------------*/
/*---------------Source Code by Bonny Useful @Busel7--------------------*/
/*--------------Modified & Adapted by Habib.m @Hab_mz-------------------*/
/*------------------------------V2.4------------------------------------*/
/*----------------------------------------------------------------------*/

//UPLOAD SKETCH ON LOLIN (WEMOS) D1 MINI(CLONE)

//FOR DEBIG SEARCH "//Serial.print" then change it to "Serial.print"

//------------------------------------------------------Additional Lib----------------------------------//
#include <ESP8266WiFi.h>
#include <EEPROM.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>
#include <DMDESP.h>
#include <PrayerTimes.h>
#include <TimeLib.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#include "SystemFont5x7.h"
#include "Font_6x14.h" 
#include "verdanav2.h"
#include "A_variables.h"
#include "B_Lib_Buzzer.h"
#include "C_Functions.h"
#include "D_WebSetup.h"

//------------------------------------------------------------------------------------------------------//
//------------------------------------------------------Void Setup--------------------------------------//
void setup() {
  Serial.begin(115200);
  pinMode(buzzer, OUTPUT);
  pinMode(tombol_jam, INPUT);

  EEPROM.begin(512);
  reload_EEPROM();
  
  if (analogRead(tombol_jam) > 180) {
    norMode = false;
  }

  if(norMode){
    //------------------------------------------------------WiFi Connect------------------------------------//
    //Serial.print("Connecting WiFi ");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      setCnt = !setCnt;
      //Serial.print(".");
      if(setCnt){ tone(buzzer,685); }
      else{ noTone(buzzer); }
      delay(500);}
    noTone(buzzer);
    //Serial.println("");
    //Serial.print("Connected: "); Serial.println(WiFi.localIP());
    
    timeClient.begin();
    timeClient.setTimeOffset(25200); //3600 x gmt+7
    setSyncProvider(requestSync);
    Disp.start();
  //-----------------------------------------------------NTP Clock Setup----------------------------------//
    //Serial.println("Getting data ...");
    getTime();
    Serial.println("Data loaded");
    
    delay(2000);
    WiFi.disconnect();
    Serial.println("wifi Disconnect Success");
    HitungJadwalSholat();
    if (_hour24 == 0 || _hour24 == 00) {
    tone(buzzer,300); delay(500); noTone(buzzer);
      //Serial.println(" Date Failed, Resetting...");
      ESP.restart();
    }
  
  //----------------------------------------------------Audio Clock Setup--------------------------------//
    playercomms.begin(9600);
    mp3.begin(playercomms);
    mp3.volume(30);  //0-30
  }
  else{
    tone(buzzer,300); delay(500); noTone(buzzer);
    WiFi.softAP("JWS SETUP", "12345678");
    IPAddress myIP = WiFi.softAPIP();
    server.on("/", handleRoot);
    server.on("/overwriteSettings",overwriteSettings);
    httpUpdater.setup(&server);
    server.begin();
    reload_EEPROM();  
  }
}

//-----------------------------------------------------------------------------------------------------//
//------------------------------------------------------Void Loop--------------------------------------//
void loop() {
  if(norMode){
    Disp.loop();
    GetDateTime();
    AlarmSholat();
    tampilinfo();
    brightSet();
    bacaJam(jam24, _minute, false, false);
  }
  else server.handleClient();
}
 
