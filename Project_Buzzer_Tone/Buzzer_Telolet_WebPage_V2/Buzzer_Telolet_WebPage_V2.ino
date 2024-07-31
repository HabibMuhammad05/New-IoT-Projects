//-----------------------------------------------------misc library-----------------------------------------------------------------------------------------------//
//#include "player.h"
#include "WebPage.h"
#include "SoundLib.h"

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
  
//--------------------------------------------------WiFi & MDNS Setup----------------------------------------------------------------------------------------------//
  WiFi.softAP("NodeMcu_OTA", "1qazmlp0");
  Serial.println("softap");
  Serial.println("");
  Serial.println(WiFi.softAPIP());
  if (MDNS.begin("ESP")) { Serial.println("MDNS responder started"); }

//-------------------------------------------------------player-----------------------------------------------------------------------------------------------------//
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
  
//------------------------------------------------------Servers Setup-------------------------------------------------------------------------------------------------//
  server.on("/", [](AsyncWebServerRequest * request) { request->send_P(200, "text/html", webpage); });
  server.onNotFound(notFound);
  AsyncElegantOTA.begin(&server);   
  server.begin(); 
}

//------------------------------------------------------Loop routine--------------------------------------------------------------------------------------------------//
void loop(void){
  if (modeplay){ playAll(); modeplay = false; }
  if (moderan){ playRan(); moderan = false; }
  if (modestop){ playStop(); modestop = false; }
  
  if (la1){ la1 = false; laguNo[0](); }
  if (la2){ la2 = false; laguNo[1](); }
  if (la3){ la3 = false; laguNo[2](); }
  if (la4){ la4 = false; laguNo[3](); }
  if (la5){ la5 = false; laguNo[4](); }
  if (la6){ la6 = false; laguNo[5](); }
}
