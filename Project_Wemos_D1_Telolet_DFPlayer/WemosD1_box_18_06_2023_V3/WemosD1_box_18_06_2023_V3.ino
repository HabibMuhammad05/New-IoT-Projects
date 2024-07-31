bool state = true;
int val;

uint8_t digCount = 0;
uint8_t res;
uint8_t firstDig;
uint8_t secDig;

//-----------------------------------------------------misc library------------------------------------------------------------------------------------------------//
#include "WebPage.h"
#include "ToneDef.h"

int thresholds[16] = {530, 461, 375, 257, 542, 475, 393, 282, 554, 488, 411, 306, 565, 502, 429, 326};
char key[16]       = {'1', '2', '3', 'A', '4', '5', '6', 'B', '7', '8', '9', 'C', '*', '0', '#', 'D'};
//------------------------------------------------------softwareserial---------------------------------------------------------------------------------------------//
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
SoftwareSerial playercomms(4, 5);
DFRobotDFPlayerMini mp3;
uint8_t volumeVal = 15;
uint8_t SongVal = 0;
const char* SLIDER_INPUT_PARAMETER = "value";
const char* SONG_INPUT_PARAMETER = "value";

//-----------------------------------------------------WiFi Library------------------------------------------------------------------------------------------------//
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <AsyncElegantOTA.h>

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
  randomSeed(A0);
  
//------------------------------------------------------Void Setup-------------------------------------------------------------------------------------------------//
  playercomms.begin(9600);
  mp3.begin(playercomms);
  mp3.volume(volumeVal);  //0-30
  
//--------------------------------------------------WiFi & MDNS Setup----------------------------------------------------------------------------------------------//
  WiFi.softAP("NodeMcu_OTA", "1qazmlp0");
  Serial.println("softap");
  Serial.println("");
  Serial.println(WiFi.softAPIP());
  if (MDNS.begin("ESP")) { Serial.println("MDNS responder started"); }

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
  server.on("/do",  HTTP_GET, [] (AsyncWebServerRequest *request) { tone(buzpin,264); request->send(200, "text/plain", "ok"); });
  server.on("/re",  HTTP_GET, [] (AsyncWebServerRequest *request) { tone(buzpin,297); request->send(200, "text/plain", "ok"); });
  server.on("/mi",  HTTP_GET, [] (AsyncWebServerRequest *request) { tone(buzpin,330); request->send(200, "text/plain", "ok"); });
  server.on("/fa",  HTTP_GET, [] (AsyncWebServerRequest *request) { tone(buzpin,352); request->send(200, "text/plain", "ok"); });
  server.on("/sol", HTTP_GET, [] (AsyncWebServerRequest *request) { tone(buzpin,396); request->send(200, "text/plain", "ok"); });
  server.on("/la",  HTTP_GET, [] (AsyncWebServerRequest *request) { tone(buzpin,440); request->send(200, "text/plain", "ok"); });
  server.on("/si",  HTTP_GET, [] (AsyncWebServerRequest *request) { tone(buzpin,495); request->send(200, "text/plain", "ok"); });
  server.on("/do2", HTTP_GET, [] (AsyncWebServerRequest *request) { tone(buzpin,528); request->send(200, "text/plain", "ok"); });
  server.on("/Noff", HTTP_GET, [] (AsyncWebServerRequest *request) { noTone(buzpin); request->send(200, "text/plain", "ok"); });
  
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
      val = 1024;
      WiFi.mode(WIFI_AP);
      WiFi.softAP("NodeMcu_OTA", "1qazmlp0");
  }else{
      digitalWrite(LED_BUILTIN, LOW); 
      WiFi.mode(WIFI_OFF);
      val = analogRead(A0);
      }
  KeypadInput();
}

void KeypadInput(){
  for (uint8_t i = 0; i < 16; i++){
    if( abs(val - thresholds[i]) < 5){
        if(i != 3 || i != 7 || i != 11 || i != 12 || i != 14 || i != 15){
          if(digCount = 0){
            digCount = 1;
            firstDig = key[i] - '0';
            res = firstDig; }
            
          if(digCount = 1){
            digCount = 0;
            secDig = key[i] - '0';
            res = (firstDig * 10) + secDig; }
         }
         if(i == 12){ mp3.play(res); } // if * pressed
         if(i == 14){ mp3.pause(); }   // if # pressed
         if(i == 15){ mp3.randomAll(); }// if D pressed
         
         if(i == 3){ mp3.volumeUp(); }  // if A pressed
         if(i == 7){ mp3.volume(15); }  // if B pressed
         if(i == 11){ mp3.volumeDown(); }// if C pressed
        
         while(analogRead(A0) < 1000) { delay(100); }
    }
  }
} 
