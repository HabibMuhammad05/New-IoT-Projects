/*----------------MD_MAX7219 Demo Run-------------------*/
/*-------------Source Code by Roboratory ---------------*/
/*-------Modified & Adapted by Habib.m @Hab_mz----------*/
/*-----------------------V1.0---------------------------*/

//-----------------------------------------------------WiFi Library------------------------------------------------------------------------------------------------//
#include <ESP8266WiFi.h>
#include <AsyncElegantOTA.h>

char* ssid     = "Al-Isra_Telolet";     // UBAH SSID WIFI AP ANDA
char* password = "12345678";   // UBAH PASSWORD SSID AP ANDA


//---------------------------------------------------Webserver Setup-----------------------------------------------------------------------------------------------//
#include "WebPage.h"

const char* SLIDER_INPUT_PARAMETER = "value";
const char* SONG_INPUT_PARAMETER = "value";

#include <ESPAsyncWebServer.h>
AsyncWebServer server(80); // server port 

void notFound(AsyncWebServerRequest *request){
  request->send(404, "text/plain", "Page Not found");
}

//---------------------------------------------------MAX7219 Setup-----------------------------------------------------------------------------------------------//
#include <MD_MAX72xx.h>
#include <SPI.h>

#define RUN_DEMO  1
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CLK_PIN   14  // or SCK
#define DATA_PIN  13  // or MOSI
#define CS_PIN    12  // or SS
MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);  

#include "Functions.h"

// ========== Control routines ===========
//
void runMatrixAnimation(void)
{
  static  uint8_t state = 0;
  static  uint8_t mesg = 0;
  static  boolean bRestart = true;
	static boolean	bInMessages = false;
  boolean changeState = false;

  if (millis()-prevTimeDemo >= 1000)
  {
    prevTimeDemo = millis();
    if (--timeDemo == 0)
    {
      timeDemo = DEMO_DELAY;
      changeState = true;
    }
  }
  if (changeState)
  {
    if (bInMessages) // the message display state
    {
      mesg++;
      if (mesg >= sizeof(msgTab)/sizeof(msgTab[0]))
      {
        mesg = 0;
    	bInMessages = false;
        state++;
      }
    }
    else
      state++;

    bRestart = true;
  };

  switch(state)
  {
    case  0: bInMessages = true; bRestart = scrollText(bRestart, msgTab[mesg]); break;
    case  1: bRestart = graphicMidline1(bRestart);       break;
    case  2: bRestart = graphicMidline2(bRestart);       break;
    case  3: bRestart = graphicScanner(bRestart);        break;
    case  4: bRestart = graphicRandom(bRestart);         break;
    case  5: bRestart = graphicFade(bRestart);           break;
    case  6: bRestart = graphicSpectrum1(bRestart);      break;
    case  7: bRestart = graphicHeartbeat(bRestart);      break;
    case  8: bRestart = graphicHearts(bRestart);         break;
    case  9: bRestart = graphicEyes(bRestart);           break;
    case 10: bRestart = graphicBounceBall(bRestart);     break;
    case 11: bRestart = graphicArrowScroll(bRestart);    break;
    case 12: bRestart = graphicScroller(bRestart);       break;
    case 13: bRestart = graphicWiper(bRestart);          break;
    case 14: bRestart = graphicInvader(bRestart);        break;
    case 15: bRestart = graphicPacman(bRestart);         break;
    case 16: bRestart = graphicArrowRotate(bRestart);    break;
    case 17: bRestart = graphicSpectrum2(bRestart);      break;
    case 18: bRestart = graphicSinewave(bRestart);       break;

    default: state = 0;
  }
}

void setup()
{
//----------------------------------------------------MAX7219 Begin--------------------------------------------------------------------------------------------------//
  mx.begin();
  prevTimeAnim = millis();
  prevTimeDemo = millis();
  Serial.begin(57600);
  
//------------------------------------------------------WiFi Setup--------------------------------------------------------------------------------------------------//
  WiFi.softAP(ssid, password);
  
//--------------------------------------------------Slider data Recv----------------------------------------------------------------------------------------------//
  server.on("/slider", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String SliderinputMessage;
    if (request->hasParam(SLIDER_INPUT_PARAMETER)) {
        SliderinputMessage = request->getParam(SLIDER_INPUT_PARAMETER)->value();
        volumeVal = SliderinputMessage.toInt();
        mp3.volume(volumeVal);  //0-30 
    }
    });
}

void loop()
{
  
  runMatrixAnimation();
}
