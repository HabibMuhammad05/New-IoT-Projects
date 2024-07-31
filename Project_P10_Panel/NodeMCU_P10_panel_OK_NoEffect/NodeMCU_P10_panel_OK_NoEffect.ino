const int buzzer = D1;
int ihti = 2;
int detikbeep;
int updCnt = 0;
unsigned long waktu1=0;
bool dotTime;
String teks;
bool Clr = true;
bool Setup = true;


#include <TimeLib.h>
time_t requestSync(){
  Serial.write(7);  // ASCII bell character requests a time sync message 
  return 0; // the time will be sent later in response to serial mesg
}

const char* ssid     = "ZAINI MIFTAH";     // SSID of local network
const char* password = "120812rj";   // Password on network

#include <ESP8266WiFi.h>

#include <NTPClient.h>
#include <WiFiUdp.h>
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");
unsigned long Epoch_Time; 
uint8_t utcOffset = 7; // Time Zone setting


// PrayerTimes
#include <PrayerTimes.h>
double times[sizeof(TimeName)/sizeof(char*)];

#include <DMDESP.h>

#include "SystemFont5x7.h"
#include "Font_6x14.h" //-> This font only contains numbers from 0-9
#include "verdanav2.h"
#include "ElektronMart6x8.h"

#define DISPLAYS_WIDE 1 // Kolom Panel
#define DISPLAYS_HIGH 1 // Baris Panel
DMDESP Disp(DISPLAYS_WIDE, DISPLAYS_HIGH);

int _day, _month, _year, _hour24, _hour12, _minute, _second, _dtw;
int hr24;
String st;
char nameoftheday[7][12] = {"Ahad", "Senin", "Selasa", "Rabu", "Kamis", "Jum'at", "Sabtu"};
char month_name[12][12] = {"Jan","Feb", "Mar", "Apr", "Mei", "Jun", "Jul", "Agu", "Sep", "Okt", "Nov", "Des"};

//------------------------------------------Variable for Millis------------------------------------//
const long interval = 1000; //-> Retrieve time and date data every 1 second
unsigned long previousMillis = 0;

const long interval_for_date = 60; //-> For scroll speed
unsigned long previousMillis_for_date = 0;

unsigned long prevdateMillis = 0;

unsigned long previousMillisIsr = 0;

//-----------------------------------Variable to display hours and minutes---------------------------//
char hr_24 [3];
String str_hr_24;
char mn [3];
String str_mn;
char sc [3];
String str_sc;
//----------------------------------------------------------------------------------------------------//
void setup() {
  Serial.begin(115200);
  timeClient.begin();
  timeClient.setTimeOffset(25200); //3600 x gmt+7
  setSyncProvider(requestSync);
  Disp.start(); 
  Disp.setBrightness(5);
  Disp.setFont(SystemFont5x7); 
//-------------------------------WiFi Connect----------------------//
  Serial.print("Connecting WiFi ");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.print("Connected: "); Serial.println(WiFi.localIP());
  
//-------------------------------NTP Clock Setup----------------------//
  Serial.println("Getting data ...");
  getTime();
  Serial.println("Data loaded");
    
  WiFi.disconnect();
  Serial.println("wifi Disconnect Success");
  JadwalSholat();
}

void loop() {
  Disp.loop();
  GetDateTime();
  tampilinfo();
}

//------------------------------------------------------------------------Subroutine to retrieve or update the time and date from DS1307
void GetDateTime() {
//  DateTime now = rtc.now();
Serial.println( String(_day) + "-" + String(_month) + "-" + String(_year));

Serial.println( String(_hour24) + ":" + String(_minute) + ":" + String(_second));
  _day=day();
  _month=month();
  _year=year();
  _hour24=hour();
  _minute=minute();
  _second=second();
  _dtw=weekday();

  hr24=_hour24;
  if (hr24>12) {
    _hour12=hr24-12;
  }
  else if (hr24==0) {
    _hour12=12;
  }
  else {
    _hour12=hr24;
  }

  if (hr24<12) {
    st="AM";
  }
  else {
    st="PM"; 
  } 
}
//------------------------------------------------------------------------Subroutine to display days, months and years

uint8_t tmpinfo;
void tampilinfo() {
  switch(tmpinfo) {

    case 0 :
      Disp.drawRect(0,0,32,15,0,0);
      BigClock();
      break;

    case 1 :
      scrolling_date();
      break;

    case 2 :
      TampilJadwalSholat();
      break;
    
  }
}
void JadwalSholat() {

  /*
    CALCULATION METHOD
    ------------------
    Jafari,   // Ithna Ashari
    Karachi,  // University of Islamic Sciences, Karachi
    ISNA,     // Islamic Society of North America (ISNA)
    MWL,      // Muslim World League (MWL)
    Makkah,   // Umm al-Qura, Makkah
    Egypt,    // Egyptian General Authority of Survey
    Custom,   // Custom Setting
    JURISTIC
    --------
    Shafii,    // Shafii (standard)
    Hanafi,    // Hanafi
    ADJUSTING METHOD
    ----------------
    None,        // No adjustment
    MidNight,   // middle of night
    OneSeventh, // 1/7th of night
    AngleBased, // angle/60th of night
    TIME IDS
    --------
    Fajr,
    Sunrise,
    Dhuhr,
    Asr,
    Sunset,
    Maghrib,
    Isha
  
  */

//  RtcDateTime now = Rtc.GetDateTime();
  
  int tahun = year();
  int bulan = month();
  int tanggal = day();
  float latitude = -6.939121;
  float longitude = 106.934425;
  int zonawaktu = 7;
  
  set_calc_method(Karachi);
  set_asr_method(Shafii);
  set_high_lats_adjust_method(AngleBased);
  set_fajr_angle(20);
  set_isha_angle(18);  

  get_prayer_times(tahun, bulan, tanggal, latitude, longitude, zonawaktu, times);

}

void TampilJadwalSholat() {

//  JadwalSholat();

  static uint8_t i;
  static uint32_t pM;
  uint32_t cM = millis();
  
  char sholat[7];
  char jam[5];
  char TimeName[][8] = {"SUBUH","TERBIT","DZUHR","ASHAR","TRBNM","MAGRB","ISYA'"};
  int hours, minutes;
  int ihti = 2;

  if (cM - pM >= 1500) {
    
    pM = cM;
    Disp.drawRect(0,0,32,15,0,0);
    
//    if (i == 1) {i = 2;} // Abaikan Terbit
    if (i == 4) {i = 5;} // Abaikan Terbenam

    get_float_time_parts(times[i], hours, minutes);
  
    minutes = minutes + ihti;

    if (minutes >= 60) {
      minutes = minutes - 60;
      hours ++;
    }

    char *sholat = TimeName[i];
    sprintf(jam,"%02d:%02d", hours, minutes);     
    Disp.setFont(verdanav2);
    textCenter(-1, sholat); 
    textCenter(7, jam);
     
    i++;

    if (i > 7) {
      get_float_time_parts(times[0], hours, minutes);
      minutes = minutes + ihti;
      if (minutes < 11) {
        minutes = 60 - minutes;
        hours --;
      } else {
        minutes = minutes - 10 ;
      }
      sprintf(jam,"%02d:%02d", hours, minutes);
      Disp.drawRect(0,0,32,15,0,0);
      Disp.setFont(verdanav2);
      textCenter(-1, "IMSAK"); 
      textCenter(7, jam); 
      
      if (i > 8) {
        i = 0;
        Disp.drawRect(0,0,32,15,0,0);
        tmpinfo = 0;
      }
    }   
  }
//    Disp.drawRect(0,0,32,15,0,0);
}

void scrolling_date() {  
  unsigned long waktusekarang = millis();
  if(Clr){
      Clr = false;
      Disp.drawRect(0,0,32,15,0,0);
  }
  
  teks = String(String(nameoftheday[_dtw-1]) + ", " +String(_day) + "-" + String(month_name[_month-1]) + "-" + String(_year) + " ");
  
      TeksJalan(8, 60); // Tampilkan teks berjalan TeksJalan(posisi y, kecepatan);
      Disp.setFont(verdanav2); // Tentukan huruf
      textCenter(-1, String(_hour24) + ":" + String(_minute)); // Tampilkan teks
     
      if(waktusekarang-waktu1>= 1000){ dotTime = !dotTime; waktu1=millis(); }
      textCenter(-1, (dotTime ? ":" : " "));

  
//  Disp.drawRect(0,0,32,15,0,0);
//  delay(100);
  //=====================================================Holds date data to display
//nameoftheday[_dtw]) + ", " + 
//  String Date = String(String(nameoftheday[_dtw-1]) + ", " +String(_day) + "-" + String(month_name[_month-1]) + "-" + String(_year));
//  char dt[50];
//  Date.toCharArray(dt,50);
//  int i=32+10;
//  int j=strlen(dt)+(strlen(dt)*5);
//  //=====================================================
//
////  Disp.setFont(SystemFont5x7);
//
//  while(1) {
//    //_____________________________________________________millis() to display time
//    unsigned long currentMillis = millis();
//    if (currentMillis - previousMillis >= interval) {
//      previousMillis = currentMillis; //-> save the last time 
//      
//      //=====================================================Showing the clock in P10
//      str_hr_24=String(_hour24);
//      str_hr_24.toCharArray(hr_24,3);
//  
//      if (_hour24<10) {
//        Disp.drawText(2, 0, "0");
//        Disp.drawText(8, 0, hr_24);
//      }
//      else {
//        Disp.drawText(2, 0, hr_24);
//      }
//      //=====================================================
//      
//      //=====================================================Showing ":" in P10
//      GetDateTime(); //-> Retrieve time and date data from DS1307
//      if (_second %2 == 0) {
//        Disp.drawText(14, 0, ":");
//      }
//      else {
//        Disp.drawText(14, 0, " ");
//      }
//      //=====================================================
//      
//      //=====================================================Showing minutes in P10
//      str_mn=String(_minute);
//      str_mn.toCharArray(mn,3);
//  
//      if (_minute<10) {
//        Disp.drawText(19, 0, "0");
//        Disp.drawText(25, 0, mn);
//      }
//      else {
//        Disp.drawText(19, 0, mn);
//      }
//      //=====================================================
//    }
//    //_____________________________________________________
//
//    //_____________________________________________________millis() for display & scrolling date
//    unsigned long currentMillis_for_date = millis();
//    if (currentMillis_for_date - previousMillis_for_date >= interval_for_date) {
//      previousMillis_for_date = currentMillis_for_date; //-> save the last time 
//      
//      i--;
//      Disp.drawText(i, 9, dt);
//      if (i<=~j) {
////        Disp.drawRect(0,0,32,15,0,0);
//        delay(100);
//        return;
//      }
//    }
//    //_____________________________________________________

//      tmpinfo = 2;
//  }
}

void BigClock(){
    Disp.setFont(Font_6x14);
    str_hr_24=String(_hour24);
    str_hr_24.toCharArray(hr_24,3);

//  unsigned int cM_Clock = millis();
//  unsigned int pM_Clock = 0;
//  
//// unsigned int kl = 
//
////  static uint8_t flag;
//
//  if(cM_Clock - pM_Clock > 10000) {
//    
//      Serial.println("cM="  + String(cM_Clock));
//      Serial.println("pM="  + String(pM_Clock));
//    pM_Clock = cM_Clock;
//      tmpinfo = 1;
//      Serial.print("tmpinfo 1 - menuju scrolltext");
//  }
//  else{

    if(_second == 25){
      tmpinfo = 1;
    }

    if (_hour24<10) {
      Disp.drawText(1, 0, "0");
      Disp.drawText(8, 0, hr_24);
    }
    else {
      Disp.drawText(1, 0, hr_24);
    }
    //=====================================================

    //=====================================================Showing ":" in P10
    if (_second %2 == 0) {    
        Disp.drawRect(16,3,17,4, 1,1);
        Disp.drawRect(16,11,17,12, 1,1); 
      }
     else {
        Disp.drawRect(16,3,17,4, 0,0);
        Disp.drawRect(16,11,17,12, 0,0); 
      }
    //=====================================================

    //=====================================================Showing minute and second in P10
    Disp.setFont(SystemFont5x7);
    
    str_mn=String(_minute);
    str_mn.toCharArray(mn,3);

    if (_minute<10) {
      Disp.drawText(20, 0, "0");
      Disp.drawText(26, 0, mn);
    }
    else {
      Disp.drawText(20, 0, mn);
    }

    str_sc=String(_second);
    str_sc.toCharArray(sc,3);

    if (_second<10) {
      Disp.drawText(20, 9, "0");
      Disp.drawText(26, 9, sc);
    }
    else {
      Disp.drawText(20, 9, sc);
    }
//  }
//    flag++;


//    if (flag >= 2) {
//      flag = 0;
//      Disp.drawRect(0,0,32,15,0,0);
//      tmpinfo = 1;
//    }
// }
}

void getTime(){ 
  timeClient.update();
  Epoch_Time = timeClient.getEpochTime()+ 3;
  Serial.println(Epoch_Time);
  delay(500);
  if( Epoch_Time >= 1357041600) { 
     setTime(Epoch_Time);
  }
}

void textCenter(int y,String Msg) {
  
  int center = int((Disp.width()-Disp.textWidth(Msg)) / 2);
  Disp.drawText(center,y,Msg);
  
}

void TeksJalan(int y, uint8_t kecepatan) {

  static uint32_t pM;
  static uint32_t x;
  int width = Disp.width();
  Disp.setFont(SystemFont5x7); // Tentukan huruf
  int fullScroll = Disp.textWidth(teks) + width;
  if((millis() - pM) > kecepatan) { 
    pM = millis();
    if (x < fullScroll) {
      ++x;
    } else {
      x = 0;
      tmpinfo = 2;
      Clr = true;
      return;
    }
    Disp.drawText(width - x, y, teks);
  }  

}
