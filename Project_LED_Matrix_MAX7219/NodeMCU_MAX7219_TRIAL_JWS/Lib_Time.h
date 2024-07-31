//--------------------------------------------------------Epoch Lib-------------------------------------//
#include <TimeLib.h>
time_t requestSync(){
  Serial.write(7); 
  return 0; 
}

//------------------------------------------------------NTP Clock Lib-----------------------------------//
#include <NTPClient.h>
#include <WiFiUdp.h>
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");
unsigned long Epoch_Time; 
uint8_t utcOffset = 7; // Time Zone setting

//----------------------------------------------------PrayerTimes Lib-----------------------------------//
#include <PrayerTimes.h>
double times[sizeof(TimeName)/sizeof(char*)];
int ihti = 2;
