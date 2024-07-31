#include "OneButton.h"
OneButton pb(13, true, true);
bool state = true;
int val;
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
const char* INPUT_PARAMETER = "value";
String slider_value = "0";

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
  randomSeed(A0);
  pb.attachLongPressStop(tekanLama);
  
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

//-------------------------------------------------------player-----------------------------------------------------------------------------------------------------//
    // Send a GET request to <ESP_IP>/slider?value=<inputMessage>  
//    server.on("/slider", HTTP_GET, [] (AsyncWebServerRequest *request) {
//    String message;
//    if (request->hasParam(input_parameter)) {
//      message = request->getParam(input_parameter)->value();
//      slider_value = message;
////      analogWrite(led_pin,slider_value.toInt());
//        mp3.volume(slider_value.toInt());  //0-30
//    }
//    else {
//      message = "No message sent";
//    }
//    Serial.println(message);
//    request->send(200, "text/plain", "OK"); });

  server.on("/slider", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage;
    if (request->hasParam(INPUT_PARAMETER)) {
        inputMessage = request->getParam(INPUT_PARAMETER)->value();
        volumeVal = inputMessage.toInt();
        mp3.volume(volumeVal);  //0-30
    }
  });
  
  server.on("/play", HTTP_GET, [] (AsyncWebServerRequest *request) { digitalWrite(LED_BUILTIN, LOW); modeplay = true; request->send(200, "text/plain", "ok"); });
  server.on("/ran",  HTTP_GET, [] (AsyncWebServerRequest *request) { digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN)); moderan = true; request->send(200, "text/plain", "ok"); });
  server.on("/stop", HTTP_GET, [] (AsyncWebServerRequest *request) { digitalWrite(LED_BUILTIN, HIGH); modestop = true; request->send(200, "text/plain", "ok"); });
  
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
  
//------------------------------------------------------song select-------------------------------------------------------------------------------------------------//
  server.on("/1", HTTP_GET, [] (AsyncWebServerRequest *request) { la1 = true; request->send(200, "text/plain", "ok"); });
  server.on("/2", HTTP_GET, [] (AsyncWebServerRequest *request) { la2 = true; request->send(200, "text/plain", "ok"); });
  server.on("/3", HTTP_GET, [] (AsyncWebServerRequest *request) { la3 = true; request->send(200, "text/plain", "ok"); });
  server.on("/4", HTTP_GET, [] (AsyncWebServerRequest *request) { la4 = true; request->send(200, "text/plain", "ok"); });
  server.on("/5", HTTP_GET, [] (AsyncWebServerRequest *request) { la5 = true; request->send(200, "text/plain", "ok"); });
  server.on("/6", HTTP_GET, [] (AsyncWebServerRequest *request) { la6 = true; request->send(200, "text/plain", "ok"); });
  server.on("/7", HTTP_GET, [] (AsyncWebServerRequest *request) { la7 = true; request->send(200, "text/plain", "ok"); });
  server.on("/8", HTTP_GET, [] (AsyncWebServerRequest *request) { la8 = true; request->send(200, "text/plain", "ok"); });
  server.on("/9", HTTP_GET, [] (AsyncWebServerRequest *request) { la9 = true; request->send(200, "text/plain", "ok"); });
  server.on("/10", HTTP_GET, [] (AsyncWebServerRequest *request) { la10 = true; request->send(200, "text/plain", "ok"); });
  server.on("/11", HTTP_GET, [] (AsyncWebServerRequest *request) { la11 = true; request->send(200, "text/plain", "ok"); });
  server.on("/12", HTTP_GET, [] (AsyncWebServerRequest *request) { la12 = true; request->send(200, "text/plain", "ok"); });
  server.on("/13", HTTP_GET, [] (AsyncWebServerRequest *request) { la13 = true; request->send(200, "text/plain", "ok"); });
  
//------------------------------------------------------Servers Setup-------------------------------------------------------------------------------------------------//
  server.on("/", [](AsyncWebServerRequest * request) { request->send_P(200, "text/html", webpage); });
  server.onNotFound(notFound);
  AsyncElegantOTA.begin(&server);   
  server.begin(); 
  pb.attachLongPressStop(tekanLama);
}

//------------------------------------------------------Loop routine--------------------------------------------------------------------------------------------------//
void loop(void){
  pb.tick();
  
  if(state){
      val = 1024;
//      Serial.println("truw");
      WiFi.mode(WIFI_AP);
      WiFi.softAP("NodeMcu_OTA", "1qazmlp0");
  }else{
      WiFi.mode(WIFI_OFF);
////      Serial.println("not truw");
      val = analogRead(A0);
      }

  for (uint8_t i = 0; i < 16; i++){
    if( abs(val - thresholds[i]) < 5){
//      Serial.println(i);
      if(i == 12){tekanLama();}
//      Serial.println(key[i]);
      uint8_t num = i + 1;
      mp3.play(num);
      pb.tick();
      while(analogRead(A0) < 1000) {
        delay(100); }
    }
  }

  if (modeplay){ playAll(); modeplay = false; }
  if (moderan){ playRan(); moderan = false; }
  if (modestop){ playStop(); modestop = false; }
  
  if (la1) { la1 = false; mp3.play(1); }
  if (la2) { la2 = false; mp3.play(2); }
  if (la3) { la3 = false; mp3.play(3); }
  if (la4) { la4 = false; mp3.play(4); }
  if (la5) { la5 = false; mp3.play(5); }
  if (la6) { la6 = false; mp3.play(6); }
  if (la7) { la7 = false; mp3.play(7); }
  if (la8) { la8 = false; mp3.play(8); }
  if (la9) { la9 = false; mp3.play(9); }
  if (la10){ la10 = false; mp3.play(10); }
  if (la11){ la11 = false; mp3.play(11); }
  if (la12){ la12 = false; mp3.play(13); }
  if (la13){ la13 = false; mp3.play(14); }
    
}

void tekanLama(){
//  Serial.println("Single Press Detected!");
  state = !state;
  mp3.play(12);
} 


void playRan(){ int randomval = random(1,14); mp3.play(randomval); }

void playAll(){}
void playStop(){}
