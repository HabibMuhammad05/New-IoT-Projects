//-----------------------------------------------------WiFi Library------------------------------------------------------------------------------------------------//
#include <ESP8266WiFi.h>
#include <AsyncElegantOTA.h>

const char* ssid     = "Al-Isra_Telolet";     // UBAH SSID WIFI AP ANDA
const char* password = "12345678";   // UBAH PASSWORD SSID AP ANDA

//------------------------------------------------------softwareserial---------------------------------------------------------------------------------------------//
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
SoftwareSerial playercomms(4, 5);
DFRobotDFPlayerMini mp3;
uint8_t volumeVal = 30;
uint8_t SongVal = 0;
const char* SLIDER_INPUT_PARAMETER = "value";
const char* SONG_INPUT_PARAMETER = "value";

//-----------------------------------------------------keypad Var's------------------------------------------------------------------------------------------------//
#include "WebPage.h"

bool state = true;
int val;
uint8_t res = 0;
uint16_t nada;

//int thresholds[16] = {1024, 967, 906, 730, 667, 637, 546, 513, 495, 425, 445, 410, 840, 605, 475, 393};
//char key[16]       = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '*', '#', 'A', 'B', 'C', 'D'};


//int thresholds[16] = {1024, 1006, 920, 731, 685, 645, 547, 522, 498, 429, 445, 411, 851, 609, 478, 395};
//char key[16]       = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '*', '#', 'A', 'B', 'C', 'D'};

int thresholds[16] = {1024, 990, 910, 731, 680, 645, 547, 522, 498, 428, 443, 408, 845, 609, 478, 380};
char key[16]       = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '*', '#', 'A', 'B', 'C', 'D'};

//int thresholds[16] = {1024, 1006, 920, 731, 685, 645, 547, 522, 498, 429, 447, 412, 851, 609, 478, 397};
//char key[16]       = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '*', '#', 'A', 'B', 'C', 'D'};

//---------------------------------------------------Webserver Setup-----------------------------------------------------------------------------------------------//
#include <ESPAsyncWebServer.h>
AsyncWebServer server(80); // server port 80

void notFound(AsyncWebServerRequest *request){
  request->send(404, "text/plain", "Page Not found");
}
//------------------------------------------------------Void Setup-------------------------------------------------------------------------------------------------//
void setup(void){
  Serial.begin(115200);
  pinMode(LED_BUILTIN,OUTPUT);
  pinMode(12, INPUT_PULLUP);
  pinMode(13, OUTPUT);
  randomSeed(A0);
  
//----------------------------------------------------dfPlayer Setup-------------------------------------------------------------------------------------------------//
  playercomms.begin(9600);
  mp3.begin(playercomms);
  mp3.volume(volumeVal);  //0-30
  
//------------------------------------------------------WiFi Setup--------------------------------------------------------------------------------------------------//
      WiFi.softAP("Calya_AP_Telolet", "1qazmlp0");
  
//--------------------------------------------------Slider data Recv----------------------------------------------------------------------------------------------//
  server.on("/slider", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String SliderinputMessage;
    if (request->hasParam(SLIDER_INPUT_PARAMETER)) {
        SliderinputMessage = request->getParam(SLIDER_INPUT_PARAMETER)->value();
        volumeVal = SliderinputMessage.toInt();
        mp3.volume(volumeVal);  //0-30 
    }
    });

//--------------------------------------------------Song data Recv----------------------------------------------------------------------------------------------//
  server.on("/song", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String SonginputMessage;
    if (request->hasParam(SONG_INPUT_PARAMETER)) {
        SonginputMessage = request->getParam(SONG_INPUT_PARAMETER)->value();
        SongVal = SonginputMessage.toInt();
        mp3.play(SongVal);
    }
    });
  
  server.on("/play", HTTP_GET, [] (AsyncWebServerRequest *request) { mp3.enableLoopAll(); request->send(200, "text/plain", "ok"); });
  server.on("/ran",  HTTP_GET, [] (AsyncWebServerRequest *request) { mp3.randomAll(); request->send(200, "text/plain", "ok"); });
  server.on("/stop", HTTP_GET, [] (AsyncWebServerRequest *request) { mp3.pause(); mp3.disableLoopAll(); request->send(200, "text/plain", "ok"); });
  
//------------------------------------------------------manual not--------------------------------------------------------------------------------------------------//
  server.on("/do",  HTTP_GET, [] (AsyncWebServerRequest *request) { mp3.play(35); request->send(200, "text/plain", "ok"); });
  server.on("/re",  HTTP_GET, [] (AsyncWebServerRequest *request) { mp3.play(36); request->send(200, "text/plain", "ok"); });
  server.on("/mi",  HTTP_GET, [] (AsyncWebServerRequest *request) { mp3.play(37); request->send(200, "text/plain", "ok"); });
  server.on("/fa",  HTTP_GET, [] (AsyncWebServerRequest *request) { mp3.play(38); request->send(200, "text/plain", "ok"); });
  server.on("/sol", HTTP_GET, [] (AsyncWebServerRequest *request) { mp3.play(39); request->send(200, "text/plain", "ok"); });
  server.on("/la",  HTTP_GET, [] (AsyncWebServerRequest *request) { mp3.play(40); request->send(200, "text/plain", "ok"); });
  server.on("/Noff", HTTP_GET, [] (AsyncWebServerRequest *request) {  request->send(200, "text/plain", "ok"); }); //mp3.pause();
  server.on("/Nstop", HTTP_GET, [] (AsyncWebServerRequest *request) { mp3.pause(); request->send(200, "text/plain", "ok"); }); //mp3.pause();
  
//------------------------------------------------------Servers Setup-------------------------------------------------------------------------------------------------//
  server.on("/", [](AsyncWebServerRequest * request) { request->send_P(200, "text/html", webpage); });
  server.onNotFound(notFound);
  AsyncElegantOTA.begin(&server);   
  server.begin(); 
}

//------------------------------------------------------Loop routine--------------------------------------------------------------------------------------------------//
void loop(void){
    if(digitalRead(12) == HIGH){
      digitalWrite(LED_BUILTIN, HIGH); 
      val = 70;
      WiFi.mode(WIFI_AP);
      WiFi.softAP("Calya_AP_Telolet", "1qazmlp0");
  }else{
      digitalWrite(LED_BUILTIN, LOW); 
      WiFi.mode(WIFI_OFF);
      val = analogRead(A0);
      }
            
  for (int i = 0; i < 16; i++){
    if( abs(val - thresholds[i]) < 7){
      Serial.println(key[i]);
      
//      Serial.println(key[i]);
//      if(i >= 10){ nada = 200; beep(true); }
//      else{ nada = 2320; beep(true); }
      
      if(i <= 9){ nada = 2320; beep(true); res = res * 10 + key[i] - '0'; }
      if(i == 10){ nada = 200; beep(true); mp3.play(res);  }                    // if * pressed
      if(i == 11){ nada = 200; beep(true); mp3.pause(); mp3.disableLoopAll(); } // if # pressed
      if(i == 15){ nada = 200; beep(true); mp3.randomAll(); }                   // if D pressed
         
      if(i == 12){ nada = 200; beep(true); mp3.volumeUp(); }                    // if A pressed
      if(i == 13){ nada = 200; beep(true); res = 0; }                           // if B pressed
      if(i == 14){ nada = 200; beep(true); mp3.volumeDown(); }                  // if C pressed
      
      while(analogRead(A0) > 100) {delay(150); beep(true); beep(false);}
    }
//  delay(10); 
  }
}

void beep(bool hidup){
  bool buzKondisi;
  if(hidup){
    buzKondisi = true;
    if (buzKondisi) { tone(13, nada); } 
    else { noTone(13); } 
  }
  else{ noTone(13); }
}
