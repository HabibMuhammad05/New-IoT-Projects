#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>

#include <WebSocketsServer.h>
#include <ArduinoJson.h>

#include <ESPAsyncTCP.h>
#include <AsyncElegantOTA.h>
#include <ESPAsyncWebServer.h>
AsyncWebServer server(80); // server port 80
WebSocketsServer websockets(81);


#include "Webpage.h"
#include "toneDef.h"
#include "SoundLib.h"

void notFound(AsyncWebServerRequest *request){
  request->send(404, "text/plain", "Page Not found");
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {

  switch (type) 
  {
    case WStype_DISCONNECTED:
      Serial.printf("[%u] Disconnected!\n", num);
      break;
    case WStype_CONNECTED: {
        IPAddress ip = websockets.remoteIP(num);
        Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);

        // send message to client
        websockets.sendTXT(num, "Connected from server");
      }
      break;
    case WStype_TEXT:
      Serial.printf("[%u] get Text: %s\n", num, payload);
      String message = String((char*)( payload));
      Serial.println(message);

      
     DynamicJsonDocument doc(200);
    // deserialize the data
    DeserializationError error = deserializeJson(doc, message);
    // parse the parameters we expect to receive (TO-DO: error handling)
      // Test if parsing succeeds.
  if (error) {
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.c_str());
    return;
  }

//  int LED1_status = doc["LED1"];
//  int LED2_status = doc["LED2"];
//  digitalWrite(LED1,LED1_status);
//  digitalWrite(LED2,LED2_status);
  }
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
    WiFi.mode(WIFI_OFF);
    int randomVal = random(0,5);
    functionPtr[randomVal]();
    Serial.println("Player - Random - " + String(randomVal));
    request->send_P(200, "text/html", webpage);
    WiFi.softAP("NodeMcu_AP", "1qazmlp0");
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
  websockets.begin();
  websockets.onEvent(webSocketEvent);
}

void loop(void){
  websockets.loop();
  AsyncElegantOTA.loop();
  MDNS.update();
}
