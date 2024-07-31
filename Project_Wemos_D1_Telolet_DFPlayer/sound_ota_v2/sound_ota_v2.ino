
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

#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>

#include <ESPAsyncTCP.h>
#include <AsyncElegantOTA.h>
#include <ESPAsyncWebServer.h>
#include <WebSocketsServer.h>
AsyncWebServer server(80); // server port 80
WebSocketsServer websockets(81);  

void notFound(AsyncWebServerRequest *request){
  request->send(404, "text/plain", "Page Not found");
}

void webSocketsEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  switch (type) {
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
    int musik_data;
    int musdata = musik_data;
    
    String player_data = doc["PLAYER"];
    String not_data = doc["NOT"];
    musik_data = doc["PLAYER"];

    if (player_data == "Prev"){}
    else if (player_data == "Random"){ long rnd = random(0, 6); FuncPointer[rnd]();}
    else if (player_data == "Next"){}


    if(not_data = "do"){satu(300,0);}
    else if(not_data = "re"){dua(300,0);}
    else if(not_data = "mi"){tiga(300,0);}
    else if(not_data = "fa"){empat(300,0);}
    else if(not_data = "sol"){lima(300,0);}
    else if(not_data = "la"){enam(300,0);}
    else if(not_data = "si"){tujuh(300,0);}
    else if(not_data = "do2"){delapan(300,0);}

    if (musik_data >= 1){ FuncPointer[musik_data]; }
  }
}

//-----------------------------Void Setup------------------------------//
void setup(void){
  randomSeed(A0);
  pinMode(buzpin, OUTPUT);
//-----------------------------WiFi Setup------------------------------//
  Serial.begin(115200);
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
//   server.on("/player/random", HTTP_GET, [](AsyncWebServerRequest * request){ 
//    request->send_P(200, "text/html", webpage);
//  });
//  
////---------------------------musik setup------------------------------------//
//   server.on("/musik/1", HTTP_GET, [](AsyncWebServerRequest * request){ 
//    request->send_P(200, "text/html", webpage);
//  });
//   server.on("/musik/2", HTTP_GET, [](AsyncWebServerRequest * request){ 
//    request->send_P(200, "text/html", webpage);
//  });
//   server.on("/musik/3", HTTP_GET, [](AsyncWebServerRequest * request){ 
//    request->send_P(200, "text/html", webpage);
//  });
//   server.on("/musik/4", HTTP_GET, [](AsyncWebServerRequest * request){ 
//    request->send_P(200, "text/html", webpage);
//  });
//   server.on("/musik/5", HTTP_GET, [](AsyncWebServerRequest * request){ 
//    request->send_P(200, "text/html", webpage);
//  });
//   server.on("/musik/6", HTTP_GET, [](AsyncWebServerRequest * request){ 
//    request->send_P(200, "text/html", webpage);
//  });
//   server.on("/musik/7", HTTP_GET, [](AsyncWebServerRequest * request){ 
//    request->send_P(200, "text/html", webpage);
//  });
//   server.on("/musik/8", HTTP_GET, [](AsyncWebServerRequest * request){ 
//    request->send_P(200, "text/html", webpage);
//  });
//   server.on("/musik/9", HTTP_GET, [](AsyncWebServerRequest * request){ 
//    request->send_P(200, "text/html", webpage);
//  });
//  
////---------------------------manual not setup------------------------------------//
//   server.on("/not/do", HTTP_GET, [](AsyncWebServerRequest * request){ 
//    satu();
//    request->send_P(200, "text/html", webpage);
//  });
//   server.on("/not/re", HTTP_GET, [](AsyncWebServerRequest * request){ 
//    dua();
//    request->send_P(200, "text/html", webpage);
//  });
//   server.on("/not/mi", HTTP_GET, [](AsyncWebServerRequest * request){ 
//    tiga();
//    request->send_P(200, "text/html", webpage);
//  });
//   server.on("/not/fa", HTTP_GET, [](AsyncWebServerRequest * request){ 
//    empat();
//    request->send_P(200, "text/html", webpage);
//  });
//   server.on("/not/sol", HTTP_GET, [](AsyncWebServerRequest * request){ 
//    lima();
//    request->send_P(200, "text/html", webpage);
//  });
//   server.on("/not/la", HTTP_GET, [](AsyncWebServerRequest * request){ 
//    enam();
//    request->send_P(200, "text/html", webpage);
//  });
//   server.on("/not/si", HTTP_GET, [](AsyncWebServerRequest * request){ 
//    tujuh();
//    request->send_P(200, "text/html", webpage);
//  });
//   server.on("/not/do2", HTTP_GET, [](AsyncWebServerRequest * request){ 
//    delapan();
//    request->send_P(200, "text/html", webpage);
//  });
  
//-----------------------------end--------------------------------------//
  server.onNotFound(notFound);
  AsyncElegantOTA.begin(&server);    // Start AsyncElegantOTA
  server.begin();  // it will start webserver
  websockets.begin();
  websockets.onEvent(webSocketsEvent);
}

void loop(void){
  AsyncElegantOTA.loop();
  MDNS.update();
}
