#include <ESP8266WiFi.h>
//#include <ESP8266mDNS.h>

#include <ESPAsyncTCP.h>
#include <AsyncElegantOTA.h>
#include <ESPAsyncWebServer.h>
AsyncWebServer server(80); // server port 80

#include "Webpage.h"
#include "toneDef.h"
#include "SoundLib.h"

void notFound(AsyncWebServerRequest *request){
  request->send(404, "text/plain", "Page Not found");
}

//-----------------------------Void Setup------------------------------//
void setup(void){
  randomSeed(A0);
  Serial.begin(115200);
  
//-----------------------------WiFi Setup------------------------------//
  WiFi.softAP("NodeMcu_AP", "1qazmlp0");
  Serial.println("softap");
  Serial.println("");
  Serial.println(WiFi.softAPIP());
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  
//------------------------Homepage setup--------------------------------//
  server.on("/", [](AsyncWebServerRequest * request){ 
   request->send_P(200, "text/html", webpage);
  });
  
//---------------------------player setup------------------------------------//
   server.on("/player/random", HTTP_GET, [](AsyncWebServerRequest * request){ 
    int randomVal = random(0,5);
    functionPtr[randomVal]();
    Serial.println("Player - Random - " + String(randomVal));
    request->send_P(200, "text/html", webpage);
  });
  
//---------------------------musik setup------------------------------------//
   server.on("/musik/1", HTTP_GET, [](AsyncWebServerRequest * request){ 
    Serial.println("Musik - 1");
    functionPtr[0]();
    request->send_P(200, "text/html", webpage);
  });
   server.on("/musik/2", HTTP_GET, [](AsyncWebServerRequest * request){ 
    Serial.println("Musik - 2");
    functionPtr[1]();
    request->send_P(200, "text/html", webpage);
  });
   server.on("/musik/3", HTTP_GET, [](AsyncWebServerRequest * request){ 
    Serial.println("Musik - 3");
    functionPtr[2]();
    request->send_P(200, "text/html", webpage);
  });
   server.on("/musik/4", HTTP_GET, [](AsyncWebServerRequest * request){ 
    Serial.println("Musik - 4");
    functionPtr[3]();
    request->send_P(200, "text/html", webpage);
  });
   server.on("/musik/5", HTTP_GET, [](AsyncWebServerRequest * request){
    Serial.println("Musik - 5");
    functionPtr[4](); 
    request->send_P(200, "text/html", webpage);
  });
   server.on("/musik/6", HTTP_GET, [](AsyncWebServerRequest * request){
    Serial.println("Musik - 6"); 
    functionPtr[5]();
    request->send_P(200, "text/html", webpage);
  });
  
//---------------------------manual not setup------------------------------------//
   server.on("/not/do", HTTP_GET, [](AsyncWebServerRequest * request){ 
    Serial.println("not - Do");
    satu(300,0);
    request->send_P(200, "text/html", webpage);
  });
   server.on("/not/re", HTTP_GET, [](AsyncWebServerRequest * request){ 
    Serial.println("not - Re");
    dua(300,0);
    request->send_P(200, "text/html", webpage);
  });
   server.on("/not/mi", HTTP_GET, [](AsyncWebServerRequest * request){ 
    Serial.println("not - Mi");
    tiga(300,0);
    request->send_P(200, "text/html", webpage);
  });
   server.on("/not/fa", HTTP_GET, [](AsyncWebServerRequest * request){ 
    Serial.println("not - Fa");
    empat(300,0);
    request->send_P(200, "text/html", webpage);
  });
   server.on("/not/sol", HTTP_GET, [](AsyncWebServerRequest * request){ 
    Serial.println("not - Sol");
    lima(300,0);
    request->send_P(200, "text/html", webpage);
  });
   server.on("/not/la", HTTP_GET, [](AsyncWebServerRequest * request){ 
    Serial.println("not - La");
    enam(300,0);
    request->send_P(200, "text/html", webpage);
  });
   server.on("/not/si", HTTP_GET, [](AsyncWebServerRequest * request){ 
    Serial.println("not - Si");
    tujuh(300,0);
    request->send_P(200, "text/html", webpage);
  });
   server.on("/not/do2", HTTP_GET, [](AsyncWebServerRequest * request){ 
    Serial.println("not - Do2");
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
}
