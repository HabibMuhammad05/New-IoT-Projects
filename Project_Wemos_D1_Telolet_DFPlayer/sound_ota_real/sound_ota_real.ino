#include "Webpage.h"
#include "ToneDef.h"
#include "SoundLib.h"

void iaiao();
void twinkle();
void bshark();
void sumur();
void basuriV1();
void ale2 ();

void (*FuncPointer[])() = {iaiao, twinkle, bshark, sumur, basuriV1, ale2}

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>

#include <ESPAsyncTCP.h>
#include <AsyncElegantOTA.h>
#include <ESPAsyncWebServer.h>
AsyncWebServer server(80); // server port 80

void notFound(AsyncWebServerRequest *request){
  request->send(404, "text/plain", "Page Not found");
}

//-----------------------------Void Setup------------------------------//
void setup(void){
  randomSeed(A0);
  pinMode(buzpin, OUTPUT);
  Serial.begin(115200);
  
//-----------------------------WiFi Setup------------------------------//
  WiFi.softAP("NodeMcu_AP", "1qazmlp0");
  Serial.println("softap");
  Serial.println("");
  Serial.println(WiFi.softAPIP());
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  
//------------------------------MDNS Setup-----------------------------//
  if (MDNS.begin("ESP")) { //esp.local/
    Serial.println("MDNS responder started");
  }
  
//------------------------Homepage setup--------------------------------//
  server.on("/", [](AsyncWebServerRequest * request){ 
   request->send_P(200, "text/html", webpage);
  });
  
//---------------------------player setup------------------------------------//
   server.on("/player/random", HTTP_GET, [](AsyncWebServerRequest * request){ 
    long rnd = random(0, 5);
    FuncPointer[rnd+1]();
    request->send_P(200, "text/html", webpage);
  });
  
//---------------------------musik setup------------------------------------//
   server.on("/musik/1", HTTP_GET, [](AsyncWebServerRequest * request){
    FuncPointer[0](); 
    request->send_P(200, "text/html", webpage);
  });
   server.on("/musik/2", HTTP_GET, [](AsyncWebServerRequest * request){
    FuncPointer[1](); 
    request->send_P(200, "text/html", webpage);
  });
   server.on("/musik/3", HTTP_GET, [](AsyncWebServerRequest * request){ 
    FuncPointer[2]();
    request->send_P(200, "text/html", webpage);
  });
   server.on("/musik/4", HTTP_GET, [](AsyncWebServerRequest * request){
    FuncPointer[3](); 
    request->send_P(200, "text/html", webpage);
  });
   server.on("/musik/5", HTTP_GET, [](AsyncWebServerRequest * request){ 
    FuncPointer[4]();
    request->send_P(200, "text/html", webpage);
  });
   server.on("/musik/6", HTTP_GET, [](AsyncWebServerRequest * request){ 
    FuncPointer[5]();
    request->send_P(200, "text/html", webpage);
  });
  
//---------------------------manual not setup------------------------------------//
   server.on("/not/do", HTTP_GET, [](AsyncWebServerRequest * request){ 
    satu(300,0);
    request->send_P(200, "text/html", webpage);
  });
   server.on("/not/re", HTTP_GET, [](AsyncWebServerRequest * request){ 
    dua(300,0);
    request->send_P(200, "text/html", webpage);
  });
   server.on("/not/mi", HTTP_GET, [](AsyncWebServerRequest * request){ 
    tiga(300,0);
    request->send_P(200, "text/html", webpage);
  });
   server.on("/not/fa", HTTP_GET, [](AsyncWebServerRequest * request){ 
    empat(300,0);
    request->send_P(200, "text/html", webpage);
  });
   server.on("/not/sol", HTTP_GET, [](AsyncWebServerRequest * request){ 
    lima(300,0);
    request->send_P(200, "text/html", webpage);
  });
   server.on("/not/la", HTTP_GET, [](AsyncWebServerRequest * request){ 
    enam(300,0);
    request->send_P(200, "text/html", webpage);
  });
   server.on("/not/si", HTTP_GET, [](AsyncWebServerRequest * request){ 
    tujuh(300,0);
    request->send_P(200, "text/html", webpage);
  });
   server.on("/not/do2", HTTP_GET, [](AsyncWebServerRequest * request){ 
    delapan(300,0);
    request->send_P(200, "text/html", webpage);
  });
  
//-----------------------------end--------------------------------------//
  server.onNotFound(notFound);
  AsyncElegantOTA.begin(&server);    // Start AsyncElegantOTA
  server.begin();  // it will start webserver
}

void loop(void){
  AsyncElegantOTA.loop();
  MDNS.update();
}
