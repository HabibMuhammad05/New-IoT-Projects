// REQUIRES the following Arduino libraries:
// - Adafruit_BusIO Library:  https://github.com/adafruit/Adafruit_BusIO
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit_Sensor library found at: https://github.com/adafruit/Adafruit_Sensor
// - MD_MAX72XX library can be found at https://github.com/MajicDesigns/MD_MAX72XX
// - Programming ESP32 with Arduino IDE: https://www.youtube.com/watch?v=9b0Txt-yF7E
// Find All "Great Projects" Videos : https://www.youtube.com/channel/UCCC8DuqicBtP3A_aC53HYDQ/videos

// Header file includes
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "page.h"
#include <time.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include "Font_Data.h"
#include "DHT.h"
#define DHTPIN 2     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);

// Define the number of devices we have in the chain and the hardware interface
// NOTE: These pin numbers will probably not work with your hardware and may
// need to be adapted
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 16

#define CLK_PIN   0  // or SCK
#define DATA_PIN  3  // or MOSI
#define CS_PIN    1  // or SS

// Arbitrary output pins
MD_Parola P = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

const char* ssid     = "3tawi";     // SSID of local network
const char* password = "123456";   // Password on network
ESP8266WebServer server(80);

// Global variables
#define PAUSE_TIME  0
int SPEED_TIME = 75;
int timezone = 1;
int dst = 0;
float hu , t;
uint16_t  h, m, s;
uint8_t dow;
int  day, intensity;
int  effectL, effectR;
uint8_t month;
String  year;
String  Message;
String  NewMessage;
char szTime[9];    // mm:ss\0
char szsecond[4];    // ss
char szMesg[512];
int stat = 1; 
textEffect_t  effect[] =
{
  PA_RANDOM, PA_PRINT, PA_SCAN_HORIZ, PA_SCROLL_LEFT, PA_WIPE,
  PA_SCAN_VERTX, PA_SCROLL_UP_LEFT, PA_SCROLL_UP, PA_FADE,
  PA_OPENING_CURSOR, PA_GROW_UP, PA_SCROLL_UP_RIGHT, PA_BLINDS,
  PA_SPRITE, PA_CLOSING, PA_GROW_DOWN, PA_SCAN_VERT, PA_SCROLL_DOWN_LEFT,
  PA_WIPE_CURSOR, PA_SCAN_HORIZX, PA_DISSOLVE, PA_MESH, PA_OPENING,
  PA_CLOSING_CURSOR, PA_SCROLL_DOWN_RIGHT, PA_SCROLL_RIGHT, PA_SLICE,
  PA_SCROLL_DOWN,
};
textEffect_t scrollEffect = PA_SCROLL_LEFT;
textEffect_t scrollAlign = PA_PRINT;
uint16_t scrollPause = 2000; // in milliseconds
uint8_t degC[] = { 6, 3, 3, 56, 68, 68, 68 }; // Deg C

void(* resetFunc) (void) = 0;//declare reset function at address 0

const char* months []= 
{"January", "February", "March", "April", "May", "June","July", 
"August", "September", "October", "November", "December"};

const char* dofw []= 
{"Sunday", "Monday", "Tuesday", "Wednesday","Thursday", "Friday", "Saturday"};

void getsec(char *psz)
// Code for reading clock date
{
  sprintf(psz, "%02d", s);
}
void getTime(char *psz, bool f = true)
// Code for reading clock time
{
  time_t now = time(nullptr);
  struct tm* p_tm = localtime(&now);
      h = p_tm->tm_hour;
      m = p_tm->tm_min;
      s = p_tm->tm_sec;
  sprintf(psz, "%02d%c%02d", h, (f ? ':' : ' '), m);
}

void getDate(char *psz)
// Code for reading clock date
{
  time_t now = time(nullptr);
  struct tm* p_tm = localtime(&now);
      day = p_tm->tm_mday;
      month = p_tm->tm_mon + 1;
      year = p_tm->tm_year + 1900;
  sprintf(psz, "%d %s %04d", day, months[month], (p_tm->tm_year + 1900));
}
void getDow()
// Code for reading clock date
{
  time_t now = time(nullptr);
  struct tm* p_tm = localtime(&now);
      dow = p_tm->tm_wday;
    Message = dofw[dow];
    sprintf(szMesg, "%s", Message.c_str());
}
void getHumidit()
// Code for reading clock date
{
   hu = dht.readHumidity();
    Message = "Humidity: ";
    Message += hu;
    Message += " % RH";
    sprintf(szMesg, "%s", Message.c_str());
}
void getTemperatur()
// Code for reading clock date
{
   t = dht.readTemperature();
    Message = "Temperatur: ";
    Message += t;
    Message += " $";
    sprintf(szMesg, "%s", Message.c_str());
}
void getMesgDate()
// Code for reading clock date
{
  time_t now = time(nullptr);
  struct tm* p_tm = localtime(&now);
      day = p_tm->tm_mday;
      month = p_tm->tm_mon + 1;
      year = p_tm->tm_year + 1900;
    Message = day;
    Message += " - ";
    Message += months[month];
    Message += " - ";
    Message += year;
    sprintf(szMesg, "%s", Message.c_str());
}

void handleRoot() {
 server.send(200, "text/html", MAIN_index); //Send web page
}
void handleTM() {  
  XML_response();
  }
void handleMesge() {  
  Message_response();
  }
void handlestate() { 
  state_response();
  }
void handlestate1() {
  stat = 1; 
  handleRoot(); 
  }
void handlestate2() {
  stat = 2; 
  handleRoot(); 
  }
void handlestate3() {
  stat = 3; 
  handleRoot(); 
  }
void handleEffectL() {
  handleRoot(); 
  scrollEffect = effect[effectL];
  effectL++;
  if (effectL >= 28) {
  effectL = 0 ;
  }
    P.setTextEffect(0, scrollEffect, scrollAlign);
    P.displayReset(0);
  }
void handleEffectR() {
  handleRoot(); 
  scrollAlign = effect[effectR];
  effectR++;
  if (effectR >= 28) {
  effectR = 0 ;
  }
    P.setTextEffect(0, scrollEffect, scrollAlign);
    P.displayReset(0);
  }
void handlepTime() {
  handleRoot(); 
    scrollPause = (server.arg("pausetime").toInt()) * 1000; 
    P.displayZoneText(0, szMesg, PA_CENTER, SPEED_TIME, scrollPause, scrollEffect, scrollAlign);
    P.displayReset(0);
  }
void handleMessg() { 
    handleRoot(); 
    NewMessage = server.arg("Message");
    stat = 2; 
}
void handleSpeed() {
  handleRoot(); 
    SPEED_TIME = server.arg("Speed").toInt(); 
    P.setSpeed(SPEED_TIME);
  }
void handleMeconst() { 
    handleRoot(); 
    intensity = server.arg("constare").toInt();
}
void handleRestTime() {
    handleRoot();  
    timezone = server.arg("restmie").toInt();
    getTime();
}
void handleRest() {
    handleRoot();
      delay(4000);     
    resetFunc();
}
void setup(void)
{
  WiFi.mode(WIFI_STA); 
  WiFi.begin(ssid, password); // Connect to WPA/WPA2 network.
  while(WiFi.status() != WL_CONNECTED){
      delay(200);     
    } 
  Message = WiFi.localIP().toString().c_str();
  dht.begin();
  P.begin(3);
  P.setInvert(false);
  P.setZone(0, 0, 11);
  P.setZone(1, 12, 12);
  P.setZone(2, 13, 15);
  P.setFont(1, numeric7Seg);
  P.setFont(2, numeric7Se);
  P.displayZoneText(0, szMesg, PA_CENTER, SPEED_TIME, scrollPause, scrollEffect, scrollAlign);
  P.displayZoneText(1, szsecond, PA_LEFT, SPEED_TIME, 0, PA_PRINT, PA_NO_EFFECT);
  P.displayZoneText(2, szTime, PA_CENTER, SPEED_TIME, PAUSE_TIME, PA_PRINT, PA_NO_EFFECT);
  P.addChar('$', degC);
  getTime();  
  server.on("/", handleRoot);   
  server.on("/readtmhu", handleTM); 
  server.on("/readState", handlestate);       
  server.on("/readMesge", handleMesge);  
  server.on("/stat1", handlestate1);      
  server.on("/stat2", handlestate2);      
  server.on("/stat3", handlestate3);    
  server.on("/EffectL", handleEffectL);      
  server.on("/EffectR", handleEffectR);      
  server.on("/pTime", handlepTime);         
  server.on("/MeMessg", handleMessg);          
  server.on("/MeSpeed", handleSpeed);         
  server.on("/Meconst", handleMeconst);  
  server.on("/resttime", handleRestTime);  
  server.on("/restart", handleRest);  
  server.begin();
}

void loop(void)
{  
P.setIntensity(intensity);
P.displayAnimate();
server.handleClient(); 
  static uint32_t lastTime = 0; // millis() memory
  static uint8_t  display = 0;  // current display mode
  static bool flasher = true;  // seconds passing flasher  
  
  if (millis() - lastTime >= 1000)
  {
    lastTime = millis();
    getsec(szsecond);
    getTime(szTime, flasher);
    flasher = !flasher;

    P.displayReset(1);
    P.displayReset(2);
  } 
  if (stat == 1) {
  if (P.getZoneStatus(0))
  {
    switch (display)
    {
      case 0: // Message
    P.setTextEffect(0, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
        display++;
        sprintf(szMesg, "%s", Message.c_str());
        break;

      case 1: // day of week
    P.setTextEffect(0, scrollEffect, scrollAlign);
        display++;
        getDow();
        break;

      case 2: // Date
    P.setTextEffect(0, scrollEffect, scrollAlign);
        display++;
        getMesgDate();
        break;

      case 3: // Temperature
    P.setTextEffect(0, scrollEffect, scrollAlign);
        display++;
        getTemperatur();
        break;

      case 4: // Humidity
    P.setTextEffect(0, scrollEffect, scrollAlign);
        display = 1;
        getHumidit();
        break;
    }
    P.displayReset(0);
  }
  } else if (stat == 2) {
  if (P.getZoneStatus(0))
  {
    P.setTextEffect(0, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
        sprintf(szMesg, "%s", NewMessage.c_str());
    P.displayReset(0);
  }
  } else if (stat == 3) {
  if (P.getZoneStatus(0))
  {
    switch (display)
    {
      case 0: // day of week
    P.setTextEffect(0, scrollEffect, scrollAlign);
        display++;
        getDow();
        break;

      case 1: // Date
    P.setTextEffect(0, scrollEffect, scrollAlign);
        display++;
        getMesgDate();
        break;

      case 2: // Temperature
    P.setTextEffect(0, scrollEffect, scrollAlign);
        display++;
        getTemperatur();
        break;

      case 3: // Humidity
    P.setTextEffect(0, scrollEffect, scrollAlign);
        display++;
        getHumidit();
        break;

      default:  // NewMessage
    P.setTextEffect(0, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
        display = 0;
        sprintf(szMesg, "%s", NewMessage.c_str());
        break;
    }
    P.displayReset(0);
  }
  }
}

void getTime()
{
  configTime(timezone * 3600, dst, "pool.ntp.org", "time.nist.gov");
  while (!time(nullptr)) {
  delay(1000);
  }
}
void Message_response()
{
String content = "<?xml version = \"1.0\" ?>";
    content += "<inputs><analog>";
    content += NewMessage;
    content += "</analog></inputs>";
    server.sendHeader("Cache-Control", "no-cache");
    server.send(200, "text/xml", content); //Send web page
}
void XML_response()
{
String content = "<?xml version = \"1.0\" ?>";
    content += "<inputs><analog>";
    content += t;
    content += "</analog><analog>";
    content += hu;
    content += "</analog></inputs>";
    server.sendHeader("Cache-Control", "no-cache");
    server.send(200, "text/xml", content); //Send web page
}
void state_response()
{
String content = "<?xml version = \"1.0\" ?>";
    content += "<inputs><analog>";
    content += stat;
    content += "</analog><analog>";
    content += effectL;
    content += "</analog><analog>";
    content += effectR;
    content += "</analog></inputs>";
    server.sendHeader("Cache-Control", "no-cache");
    server.send(200, "text/xml", content); //Send web page
}
