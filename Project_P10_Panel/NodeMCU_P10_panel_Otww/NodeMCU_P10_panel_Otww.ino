//------------------------------------------------------Additional Lib----------------------------------//
#include "SystemFont5x7.h"
#include "Font_6x14.h" 
#include "verdanav2.h"
#include "Lib_WiFi.h"
#include "Lib_Time.h"
#include "Lib_DMDESP.h"
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
  Disp.start();
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
  
//-----------------------------------------------------NTP Clock Setup----------------------------------//
  Serial.println("Getting data ...");
  getTime();
  Serial.println("Data loaded");
  noTone(buzzer);
  WiFi.disconnect();
  Serial.println("wifi Disconnect Success");
  HitungJadwalSholat();
}

//-----------------------------------------------------------------------------------------------------//
//------------------------------------------------------Void Loop--------------------------------------//
void loop() {
  Disp.loop();
  GetDateTime();
  AlarmSholat();
  tampilinfo();
  brightSet();
}
 
