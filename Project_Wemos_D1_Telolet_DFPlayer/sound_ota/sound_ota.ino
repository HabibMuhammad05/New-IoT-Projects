#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>

#include <ESPAsyncTCP.h>
#include <AsyncElegantOTA.h>
#include <ESPAsyncWebServer.h>
AsyncWebServer server(80); // server port 80

#include "Webpage.h"

void notFound(AsyncWebServerRequest *request){
  request->send(404, "text/plain", "Page Not found");
}

//-----------------------------Void Setup------------------------------//
void setup(void){
  Serial.begin(115200);
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  
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
  
//---------------------------musik setup------------------------------------//
   server.on("/musik/1", HTTP_GET, [](AsyncWebServerRequest * request){ 
    request->send_P(200, "text/html", webpage);
  });
   server.on("/musik/2", HTTP_GET, [](AsyncWebServerRequest * request){ 
    request->send_P(200, "text/html", webpage);
  });
   server.on("/musik/3", HTTP_GET, [](AsyncWebServerRequest * request){ 
    request->send_P(200, "text/html", webpage);
  });
   server.on("/musik/4", HTTP_GET, [](AsyncWebServerRequest * request){ 
    request->send_P(200, "text/html", webpage);
  });
   server.on("/musik/5", HTTP_GET, [](AsyncWebServerRequest * request){ 
    request->send_P(200, "text/html", webpage);
  });
   server.on("/musik/6", HTTP_GET, [](AsyncWebServerRequest * request){ 
    request->send_P(200, "text/html", webpage);
  });
   server.on("/musik/7", HTTP_GET, [](AsyncWebServerRequest * request){ 
    request->send_P(200, "text/html", webpage);
  });
   server.on("/musik/8", HTTP_GET, [](AsyncWebServerRequest * request){ 
    request->send_P(200, "text/html", webpage);
  });
   server.on("/musik/9", HTTP_GET, [](AsyncWebServerRequest * request){ 
    request->send_P(200, "text/html", webpage);
  });
  
//---------------------------manual not setup------------------------------------//
   server.on("/not/do", HTTP_GET, [](AsyncWebServerRequest * request){ 
    satu();
    request->send_P(200, "text/html", webpage);
  });
   server.on("/not/re", HTTP_GET, [](AsyncWebServerRequest * request){ 
    dua();
    request->send_P(200, "text/html", webpage);
  });
   server.on("/not/mi", HTTP_GET, [](AsyncWebServerRequest * request){ 
    tiga();
    request->send_P(200, "text/html", webpage);
  });
   server.on("/not/fa", HTTP_GET, [](AsyncWebServerRequest * request){ 
    empat();
    request->send_P(200, "text/html", webpage);
  });
   server.on("/not/sol", HTTP_GET, [](AsyncWebServerRequest * request){ 
    lima();
    request->send_P(200, "text/html", webpage);
  });
   server.on("/not/la", HTTP_GET, [](AsyncWebServerRequest * request){ 
    enam();
    request->send_P(200, "text/html", webpage);
  });
   server.on("/not/si", HTTP_GET, [](AsyncWebServerRequest * request){ 
    tujuh();
    request->send_P(200, "text/html", webpage);
  });
   server.on("/not/do2", HTTP_GET, [](AsyncWebServerRequest * request){ 
    delapan();
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
