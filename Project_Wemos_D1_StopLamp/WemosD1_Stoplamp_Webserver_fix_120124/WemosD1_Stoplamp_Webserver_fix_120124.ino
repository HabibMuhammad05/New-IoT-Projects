/*
    ___   _____    ___    ___   _        _     __  __   ___     ___   _   _   _  _   _  _   ___   _  _    ___     _____   ___  __  __  _____ 
   / __| |_   _|  / _ \  | _ \ | |      /_\   |  \/  | | _ \   | _ \ | | | | | \| | | \| | |_ _| | \| |  / __|   |_   _| | __| \ \/ / |_   _|
   \__ \   | |   | (_) | |  _/ | |__   / _ \  | |\/| | |  _/   |   / | |_| | | .` | | .` |  | |  | .` | | (_ |     | |   | _|   >  <    | |  
   |___/   |_|    \___/  |_|   |____| /_/ \_\ |_|  |_| |_|     |_|_\  \___/  |_|\_| |_|\_| |___| |_|\_|  \___|     |_|   |___| /_/\_\   |_|  

                                                                                                                                                
 "SIMPLE STOPLAMP RUNNING TEXT USING LED MATRIX WITH WEB INTERFACE" - Modified 21/10/23 by DBOSS Project
 "ADDED MODES AND SPEED CONTROL WITH OTA SOFTWARE UPDATE" - Last Modified 02/12/23 by Habib M.
  
 Based on Marco Colli MD_MAXX72XX example code
 Visit   : https://majicdesigns.github.io/MD_MAX72XX/index.html
 Support : https://www.paypal.com/paypalme/MajicDesigns/4USD

 Find DBOSS Project on YouTube
 Visit   : https://www.youtube.com/@DBOSSProject
 Support : https://saweria.co/dbossproject

 Adapted and Added OTA upload by Habib M.
 Visit   : https://www.instagram.com/hab_mz

 ==== EDIT EEPROM AND ADD AMNIMATION EEPROM ON "overwriteSetting()" and "reload_EEPROM()"=====

*/

// ================================================= Libraries ===============================
#include <MD_Parola.h>
#include "Parola_Fonts_data.h"

#include <MD_MAX72xx.h>
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>

#include <ESP8266mDNS.h>
#include <ESP8266HTTPUpdateServer.h>

// ======== Pengguna Biasa : Bebas Ubah Bagian Ini =========

const char *NAMA_WIFI     = "myStoplamp"; // Atur nama Wi-Fi stoplamp
const char *PASSWORD_WIFI = "12345678";   // Atur password yang digunakan untuk terhubung ke Wi-Fi stoplamp

// ======== Pengguna Tingkat Lanjut : Ubah Dengan Megetahui Resikonya! =========

#define DEBUG 0   

#if DEBUG
#define PRINT(s, v)   { Serial.print(F(s)); Serial.print(v); }        // Print a string followed by a value (decimal)
#define PRINTX(s, v)  { Serial.print(F(s)); Serial.print(v, HEX); }   // Print a string followed by a value (hex)
#define PRINTB(s, v)  { Serial.print(F(s)); Serial.print(v, BIN); }   // Print a string followed by a value (binary)
#define PRINTC(s, v)  { Serial.print(F(s)); Serial.print((char)v); }  // Print a string followed by a value (char)
#define PRINTS(s)     { Serial.print(F(s)); }                         // Print a string
#else
#define PRINT(s, v)   // Print a string followed by a value (decimal)
#define PRINTX(s, v)  // Print a string followed by a value (hex)
#define PRINTB(s, v)  // Print a string followed by a value (binary)
#define PRINTC(s, v)  // Print a string followed by a value (char)
#define PRINTS(s)     // Print a string
#endif

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4

//#define DATA_PIN    15  // D8
//#define CS_PIN      13  // D7
//#define CLK_PIN     12  // D6

#define DATA_PIN    13  // D7
#define CS_PIN      12  // D6
#define CLK_PIN     14  // D5

#define kanan       4  // D2 
#define kiri        5   // D1  
#define rem         2  // D4
#define led         16   // D2 

MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);
MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

textEffect_t texteffect[] =
{
  
  PA_PRINT,
  PA_SCAN_HORIZ,
  PA_SCROLL_LEFT,
  PA_WIPE,
  PA_SCROLL_UP_LEFT,
  PA_SCROLL_UP,
  PA_OPENING_CURSOR,
  PA_GROW_UP,
  PA_MESH,
  PA_SCROLL_UP_RIGHT,
  PA_BLINDS,
  PA_CLOSING,
  PA_RANDOM,
  PA_GROW_DOWN,
  PA_SCAN_VERT,
  PA_SCROLL_DOWN_LEFT,
  PA_WIPE_CURSOR,
  PA_DISSOLVE,
  PA_OPENING,
  PA_CLOSING_CURSOR,
  PA_SCROLL_DOWN_RIGHT,
  PA_SCROLL_RIGHT,
  PA_SLICE,
  PA_SCROLL_DOWN

};


// ======================================== Various Delay in miliseconds =================================

#define UNIT_DELAY      16
#define SCROLL_DELAY    (kecepatan)
#define MIDLINE_DELAY   (5 * UNIT_DELAY)
#define SCANNER_DELAY   (2 * UNIT_DELAY)
#define RANDOM_DELAY    (6 * UNIT_DELAY)
#define FADE_DELAY      (3 * UNIT_DELAY)
#define SPECTRUM_DELAY  (4 * UNIT_DELAY)
#define HEARTBEAT_DELAY (1 * UNIT_DELAY)
#define HEARTS_DELAY    (28 * UNIT_DELAY)
#define EYES_DELAY      (10 * UNIT_DELAY)
#define WIPER_DELAY     (1 * UNIT_DELAY)
#define ARROWS_DELAY    (3 * UNIT_DELAY)
#define ARROWR_DELAY    (8 * UNIT_DELAY)
#define INVADER_DELAY   (6 * UNIT_DELAY)
#define PACMAN_DELAY    (4 * UNIT_DELAY)
#define SINE_DELAY      (2 * UNIT_DELAY)

#define ROWS_DELAY      (8 * UNIT_DELAY)
#define CHKBRD_DELAY    (10 * UNIT_DELAY)
#define COLS_DELAY      (8 * UNIT_DELAY)
#define CROSS_DELAY     (2 * UNIT_DELAY)
#define BULLS_DELAY     (6 * UNIT_DELAY)
#define STRIPE_DELAY    (2 * UNIT_DELAY)
#define SPIRAL_DELAY    (2 * UNIT_DELAY)
#define BOUNCE_DELAY    (2 * UNIT_DELAY)
#define BOX_DELAY       (5 * UNIT_DELAY)
#define WAVE_DELAY      (5 * UNIT_DELAY)
#define TRIGLE_DELAY    (2 * UNIT_DELAY)
#define CRTN_DELAY      (2 * UNIT_DELAY)

#define CHAR_SPACING     1  // pixels between characters
#define BUF_SIZE        75  // character buffer size

// ============================================ General Variables ============================
uint8_t DEMO_DELAY = 8; 
bool sensorRead;
bool flag;
byte slct = 1;
byte slctSein = 1;
byte slctStop = 1;
unsigned long prevTimeAnim = 0;    // Used for remembering the millis() value in animations
unsigned long prevTimeDemo = 0;      //  Used for remembering the millis() time in demo loop
uint8_t  timeDemo = DEMO_DELAY; // number of seconds left in this demo loop

unsigned long startTime1 = 0;
unsigned long startTime2 = 0;
boolean outputActive1 = false;
boolean outputActive2 = false;

char msgtext1[]="teks1";
char msgtext2[]="teks2";
const char *msgTab[]={msgtext1, msgtext2};
String inputTEXT1;
String inputTEXT2;

const uint8_t modCount = 45;
bool manualMode[modCount];

uint8_t kecepatan = 30;
uint8_t kecerahan = MAX_INTENSITY/2;
uint8_t seinDelay = 25; 
uint8_t stopDelay = 25; 

uint8_t kecLed = map(kecerahan, 0,15, 0,255);

int ab = 0;
int bc = 0;
int cdd = 0;


const int minC = 0;
const int maxC = mx.getColumnCount() - 1;
const int minR = 0;
const int maxR = ROW_SIZE - 1;


struct Ball {
  int r;
  int c;
  int8_t dR;
  int8_t dC;
};

const int numberOfBalls = 4;  // Change this to the desired number of balls
Ball balls[numberOfBalls]; 

unsigned long lastUpdateTimeAnimation = 0;

// ======================================== Wi-Fi Configuration ==================================

ESP8266WebServer server(80);
ESP8266HTTPUpdateServer httpUpdater;

// ========================================== Graphic routines ====================================
bool scrollText(bool bInit, const char *pmsg)  //==1==
{
  static char   curMessage[BUF_SIZE];
  static char   *p = curMessage;
  static uint8_t  stateScr = 0;
  static uint8_t  curLen, showLen;
  static uint8_t  cBuf[8];
  uint8_t         colData;
  
//  myDisplay.setFont(bmz6x8);
  
//  mx.transform(MD_MAX72XX::TSD);
  // are we initializing?
  if (bInit)
  {
    PRINTS("\n--- Initializing ScrollText");
    resetMatrix();
    strcpy(curMessage, pmsg);
    stateScr = 0;
    p = curMessage;
    bInit = false;
  }

  // Is it time to scroll the text?
  if (millis()-prevTimeAnim < SCROLL_DELAY)
    return(bInit);
  prevTimeAnim = millis();        // starting point for next time

  // scroll the display
  mx.transform(MD_MAX72XX::TSL);  // scroll along

  // now run the finite stateScr machine to control what we do
  PRINT("\nScroll FSM S:", stateScr);
  switch (stateScr)
  {
    case 0: // Load the next character from the font table
      PRINTC("\nLoading ", *p);
      showLen = mx.getChar(*p++, sizeof(cBuf)/sizeof(cBuf[0]), cBuf);
      curLen = 0;
      stateScr = 1;

    // !! deliberately fall through to next stateScr to start displaying

    case 1: // display the next part of the character
      colData = cBuf[curLen++];
      mx.setColumn(0, colData);
      if (curLen == showLen)
      {
        showLen = ((*p != '\0') ? CHAR_SPACING : mx.getColumnCount()-1);
        curLen = 0;
        stateScr = 2;
      }
      break;

    case 2: // display inter-character spacing (blank column) or scroll off the display
      mx.setColumn(0, 0);
      if (++curLen == showLen)
      {
        stateScr = 0;
        bInit = (*p == '\0');
      }
      break;

    default:
      stateScr = 0;
  }
//    mx.transform(MD_MAX72XX::TSU);
  return(bInit);
}

bool graphicMidline2(bool bInit)               //==2==
{
  static uint8_t  idx = 0;      // position
  static int8_t   idOffs = 1;   // increment direction

  // are we initializing?
  if (bInit)
  {
    PRINTS("\n--- Midline2 init");
    resetMatrix();
    idx = 0;
    idOffs = 1;
    bInit = false;
  }

  // Is it time to animate?
  if (millis()-prevTimeAnim < MIDLINE_DELAY)
    return(bInit);
  prevTimeAnim = millis();    // starting point for next time

  PRINT("\nML2 R:", idx);
  PRINT(" D:", idOffs);

  // now run the animation
  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);

  // turn off the old lines
  for (uint8_t j=0; j<MAX_DEVICES; j++)
  {
    mx.setRow(j, idx, 0x00);
    mx.setRow(j, ROW_SIZE-1-idx, 0x00);
  }

  idx += idOffs;
  if ((idx == 0) || (idx == ROW_SIZE-1))
    idOffs = -idOffs;

  // turn on the new lines
  for (uint8_t j=0; j<MAX_DEVICES; j++)
  {
    mx.setRow(j, idx, 0xff);
    mx.setRow(j, ROW_SIZE-1-idx, 0xff);
  }

  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);

  return(bInit);
}

bool graphicScanner(bool bInit)                //==3==
{
  const uint8_t width = 3;      // scanning bar width
  static uint8_t  idx = 0;      // position
  static int8_t   idOffs = 1;   // increment direction

  // are we initializing?
  if (bInit)
  {
    PRINTS("\n--- Scanner init");
    resetMatrix();
    idx = 0;
    idOffs = 1;
    bInit = false;
  }

  // Is it time to animate?
  if (millis()-prevTimeAnim < SCANNER_DELAY)
    return(bInit);
  prevTimeAnim = millis();    // starting point for next time

  PRINT("\nS R:", idx);
  PRINT(" D:", idOffs);

  // now run the animation
  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);

  // turn off the old lines
  for (uint8_t i=0; i<width; i++)
    mx.setColumn(idx+i, 0);

  idx += idOffs;
  if ((idx == 0) || (idx + width == mx.getColumnCount()))
    idOffs = -idOffs;

  // turn on the new lines
  for (uint8_t i=0; i<width; i++)
   {
    mx.setColumn(idx+i, 0xff);
   }

  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);

  return(bInit);
}

bool graphicRandom(bool bInit)                 //==4==
{
  // are we initializing?
  if (bInit)
  {
    PRINTS("\n--- Random init");
    resetMatrix();
    bInit = false;
  }

  // Is it time to animate?
  if (millis()-prevTimeAnim < RANDOM_DELAY)
    return(bInit);
  prevTimeAnim = millis();    // starting point for next time
  
  // now run the animation
  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
  for (uint8_t i=0; i<mx.getColumnCount(); i++){
    mx.setColumn(i, (uint8_t)random(255));  
  }  
  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
  return(bInit);
}

bool graphicScroller(bool bInit)               //==5==
{
  const uint8_t   width = 3;     // width of the scroll bar
  const uint8_t   offset = mx.getColumnCount()/3;
  static uint8_t  idx = 0;

  // are we initializing?
  if (bInit)
  {
    PRINTS("\n--- Scroller init");
    resetMatrix();
    idx = 0;
    bInit = false;
  }

  // Is it time to animate?
  if (millis()-prevTimeAnim < SCANNER_DELAY)
    return(bInit);
  prevTimeAnim = millis();    // starting point for next time

  PRINT("\nS I:", idx);

  // now run the animation
  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);

  mx.transform(MD_MAX72XX::TSL);

  mx.setColumn(0, idx>=0 && idx<width ? 0xff : 0);
  if (++idx == offset) idx = 0;

  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);

  return(bInit);
}

bool graphicSpectrum1(bool bInit)              //==6==
{
  // are we initializing?
  if (bInit)
  {
    PRINTS("\n--- Spectrum1 init");
    resetMatrix();
    bInit = false;
  }

  // Is it time to animate?
  if (millis()-prevTimeAnim < SPECTRUM_DELAY)
    return(bInit);
  prevTimeAnim = millis();    // starting point for next time

  // now run the animation
  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
  for (uint8_t i=0; i<MAX_DEVICES; i++)
  {
    uint8_t r = random(ROW_SIZE);
    uint8_t cd = 0;

    for (uint8_t j=0; j<r; j++)
      cd |= 1<<j;
    for (uint8_t j=1; j<COL_SIZE-1; j++)
      mx.setColumn(i, j, ~cd);
     
  }
  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);

  return(bInit);
}

bool graphicSpectrum2(bool bInit)              //==7==
{
  // are we initializing?
  if (bInit)
  {
    PRINTS("\n--- Spectrum2init");
    resetMatrix();
    bInit = false;
  }

  // Is it time to animate?
  if (millis() - prevTimeAnim < SPECTRUM_DELAY)
    return(bInit);
  prevTimeAnim = millis();    // starting point for next time

  // now run the animation
  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
  for (uint8_t i = 0; i<mx.getColumnCount(); i++)
  {
    uint8_t r = random(ROW_SIZE);
    uint8_t cd = 0;

    for (uint8_t j = 0; j<r; j++)
      cd |= 1 << j;

    mx.setColumn(i, ~cd);
  }
  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);

  return(bInit);
}

bool graphicHeartbeat(bool bInit)              //==8==
{
  #define BASELINE_ROW  4

  static uint8_t  state;
  static uint8_t  r, c;
  static bool     bPoint;

  // are we initializing?
  if (bInit)
  {
    PRINTS("\n--- Heartbeat init");
    resetMatrix();
    state = 0;
    r = BASELINE_ROW;
    c = mx.getColumnCount()-1;
    bPoint = true;
    bInit = false;
  }

  // Is it time to animate?
  if (millis()-prevTimeAnim < HEARTBEAT_DELAY)
    return(bInit);
  prevTimeAnim = millis();    // starting point for next time

  // now run the animation
  PRINT("\nHB S:", state);
  PRINT(" R: ", r);
  PRINT(" C: ", c);
  PRINT(" P: ", bPoint);
  mx.setPoint(r, c, bPoint);

  switch (state)
  {
    case 0: // straight line from the right side
      if (c == mx.getColumnCount()/2 + COL_SIZE)
        state = 1;
      c--;
      break;

    case 1: // first stroke
      if (r != 0) { r--; c--; }
      else state = 2;
      break;

    case 2: // down stroke
      if (r != ROW_SIZE-1) { r++; c--; }
      else state = 3;
      break;

    case 3: // second up stroke
      if (r != BASELINE_ROW) { r--; c--; }
      else state = 4;
      break;

    case 4: // straight line to the left
      if (c == 0)
      {
        c = mx.getColumnCount()-1;
        bPoint = !bPoint;
        state = 0;
      }
      else c--;
      break;

    default:
      state = 0;     
  }

  return(bInit);
}

bool graphicFade(bool bInit)                   //==9==
{
  static uint8_t  intensity = 0;
  static int8_t   iOffs = 1;

  // are we initializing?
  if (bInit){
    PRINTS("\n--- Fade init");
    resetMatrix();
    mx.control(MD_MAX72XX::INTENSITY, intensity);

    // Set all LEDS on
    mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
    for (uint8_t i=0; i<mx.getColumnCount(); i++){ 
      mx.setColumn(i, 0xff);
    }
    mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);

    bInit = false;
  }

  // Is it time to animate?
  if (millis()-prevTimeAnim < FADE_DELAY)
    return(bInit);
  prevTimeAnim = millis();    // starting point for next time

  // now run the animation
  intensity += iOffs;
  PRINT("\nF I:", intensity);
  PRINT(" D:", iOffs);
  if ((intensity == 0) || (intensity == MAX_INTENSITY))
    iOffs = -iOffs;
  mx.control(MD_MAX72XX::INTENSITY, intensity);

  return(bInit);
}

bool graphicHearts(bool bInit)                 //==10==
{
#define NUM_HEARTS  ((MAX_DEVICES/2) +1)
  const uint8_t heartFull[] = { 0x1c, 0x3e, 0x7e, 0xfc };
  const uint8_t heartEmpty[] = { 0x1c, 0x22, 0x42, 0x84 };
  const uint8_t offset = mx.getColumnCount()/(NUM_HEARTS+1);
  const uint8_t dataSize = (sizeof(heartFull)/sizeof(heartFull[0]));

  static bool     bEmpty;

  // are we initializing?
  if (bInit)
  {
    PRINTS("\n--- Hearts init");
    resetMatrix();
    bEmpty = true;
    bInit = false;
  }

  // Is it time to animate?
  if (millis()-prevTimeAnim < HEARTS_DELAY)
    return(bInit);
  prevTimeAnim = millis();    // starting point for next time

  // now run the animation
  PRINT("\nH E:", bEmpty);

  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
  for (uint8_t h=1; h<=NUM_HEARTS; h++)
  {
    for (uint8_t i=0; i<dataSize; i++)
    {
      mx.setColumn((h*offset)-dataSize+i, bEmpty ? heartEmpty[i] : heartFull[i]);
      mx.setColumn((h*offset)+dataSize-i-1, bEmpty ? heartEmpty[i] : heartFull[i]);
    }
  }
  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
  bEmpty = !bEmpty;

  return(bInit);
}

bool graphicEyes(bool bInit)                   //==11==
{
#define NUM_EYES  2
  const uint8_t eyeOpen[] = { 0x18, 0x3c, 0x66, 0x66 };
  const uint8_t eyeClose[] = { 0x18, 0x3c, 0x3c, 0x3c };
  const uint8_t offset = mx.getColumnCount()/(NUM_EYES+1);
  const uint8_t dataSize = (sizeof(eyeOpen)/sizeof(eyeOpen[0]));

  bool bOpen;

  // are we initializing?
  if (bInit)
  {
    PRINTS("\n--- Eyes init");
    resetMatrix();
    bInit = false;
  }

  // Is it time to animate?
  if (millis()-prevTimeAnim < EYES_DELAY)
    return(bInit);
  prevTimeAnim = millis();    // starting point for next time

  // now run the animation
  bOpen = (random(1000) > 100);
  PRINT("\nH E:", bOpen);

  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
  for (uint8_t e=1; e<=NUM_EYES; e++)
  {
    for (uint8_t i=0; i<dataSize; i++)
    {
      mx.setColumn((e*offset)-dataSize+i, bOpen ? eyeOpen[i] : eyeClose[i]);
      mx.setColumn((e*offset)+dataSize-i-1, bOpen ? eyeOpen[i] : eyeClose[i]);
    }
  }
  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);

  return(bInit);
}

bool graphicBounceBall(bool bInit)             //==12==
{
  static uint8_t  idx = 0;      // position
  static int8_t   idOffs = 1;   // increment direction

  // are we initializing?
  if (bInit)
  {
    PRINTS("\n--- BounceBall init");
    resetMatrix();
    bInit = false;
  }

  // Is it time to animate?
  if (millis()-prevTimeAnim < SCANNER_DELAY)
    return(bInit);
  prevTimeAnim = millis();    // starting point for next time

  PRINT("\nBB R:", idx);
  PRINT(" D:", idOffs);

  // now run the animation
  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);

  // turn off the old ball
  mx.setColumn(idx, 0);
  mx.setColumn(idx+1, 0);

  idx += idOffs;
  if ((idx == 0) || (idx == mx.getColumnCount()-2))
    idOffs = -idOffs;

  // turn on the new lines
  mx.setColumn(idx, 0x18);
  mx.setColumn(idx+1, 0x18);

  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);

  return(bInit);
}

bool graphicArrowScroll(bool bInit)            //==13==
{
  const uint8_t arrow[] = { 0x3c, 0x66, 0xc3, 0x99 };
  const uint8_t dataSize = (sizeof(arrow)/sizeof(arrow[0]));

  static uint8_t  idx = 0;

  // are we initializing?
  if (bInit)
  {
    PRINTS("\n--- ArrowScroll init");
    resetMatrix();
    bInit = false;
  }

  // Is it time to animate?
  if (millis()-prevTimeAnim < ARROWS_DELAY)
    return(bInit);
  prevTimeAnim = millis();    // starting point for next time

  // now run the animation
  PRINT("\nAR I:", idx);

  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
  mx.transform(MD_MAX72XX::TSL);
  mx.setColumn(0, arrow[idx++]);
  if (idx == dataSize) idx = 0;
  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);

  return(bInit);
}

bool graphicWiper(bool bInit)                  //==14==
{
  static uint8_t  idx = 0;      // position
  static int8_t   idOffs = 1;   // increment direction

  // are we initializing?
  if (bInit)
  {
    PRINTS("\n--- Wiper init");
    resetMatrix();
    bInit = false;
  }

  // Is it time to animate?
  if (millis()-prevTimeAnim < WIPER_DELAY)
    return(bInit);
  prevTimeAnim = millis();    // starting point for next time

  PRINT("\nW R:", idx);
  PRINT(" D:", idOffs);

  // now run the animation
  mx.setColumn(idx, idOffs == 1 ? 0xff : 0);
  idx += idOffs;
  if ((idx == 0) || (idx == mx.getColumnCount()))
    idOffs = -idOffs;

  return(bInit);
}

bool graphicInvader(bool bInit)                //==15==
{
  const uint8_t invader1[] = { 0x0e, 0x98, 0x7d, 0x36, 0x3c };
  const uint8_t invader2[] = { 0x70, 0x18, 0x7d, 0xb6, 0x3c };
  const uint8_t dataSize = (sizeof(invader1)/sizeof(invader1[0]));

  static int8_t idx;
  static bool   iType;

  // are we initializing?
  if (bInit)
  {
    PRINTS("\n--- Invader init");
    resetMatrix();
    bInit = false;
    idx = -dataSize;
    iType = false;
  }

  // Is it time to animate?
  if (millis()-prevTimeAnim < INVADER_DELAY)
    return(bInit);
  prevTimeAnim = millis();    // starting point for next time

  // now run the animation
  PRINT("\nINV I:", idx);

  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
  mx.clear();
  for (uint8_t i=0; i<dataSize; i++)
  {
    mx.setColumn(idx-dataSize+i, iType ? invader1[i] : invader2[i]);
    mx.setColumn(idx+dataSize-i-1, iType ? invader1[i] : invader2[i]);
  }
  idx++;
  if (idx == mx.getColumnCount()+(dataSize*2)) bInit = true;
  iType = !iType;
  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);

  return(bInit);
}

bool graphicPacman(bool bInit)                 //==16==
{
  #define MAX_FRAMES  4   // number of animation frames
  #define PM_DATA_WIDTH  18
  const uint8_t pacman[MAX_FRAMES][PM_DATA_WIDTH] =  // ghost pursued by a pacman
  {
    { 0x3c, 0x7e, 0x7e, 0xff, 0xe7, 0xc3, 0x81, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x7b, 0xf3, 0x7f, 0xfb, 0x73, 0xfe },
    { 0x3c, 0x7e, 0xff, 0xff, 0xe7, 0xe7, 0x42, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x7b, 0xf3, 0x7f, 0xfb, 0x73, 0xfe },
    { 0x3c, 0x7e, 0xff, 0xff, 0xff, 0xe7, 0x66, 0x24, 0x00, 0x00, 0x00, 0xfe, 0x7b, 0xf3, 0x7f, 0xfb, 0x73, 0xfe },
    { 0x3c, 0x7e, 0xff, 0xff, 0xff, 0xff, 0x7e, 0x3c, 0x00, 0x00, 0x00, 0xfe, 0x7b, 0xf3, 0x7f, 0xfb, 0x73, 0xfe },
  };

  static int16_t idx;        // display index (column)
  static uint8_t frame;      // current animation frame
  static uint8_t deltaFrame; // the animation frame offset for the next frame

  // are we initializing?
  if (bInit)
  {
    PRINTS("\n--- Pacman init");
    resetMatrix();
    bInit = false;
    idx = -1; //DATA_WIDTH;
    frame = 0;
    deltaFrame = 1;
  }

  // Is it time to animate?
  if (millis() - prevTimeAnim < PACMAN_DELAY)
    return(bInit);
  prevTimeAnim = millis();    // starting point for next time

  PRINT("\nPAC I:", idx);

  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
  mx.clear();

  // clear old graphic
  for (uint8_t i = 0; i<PM_DATA_WIDTH; i++)
    mx.setColumn(idx - PM_DATA_WIDTH + i, 0);
  // move reference column and draw new graphic
  idx++;
  for (uint8_t i = 0; i<PM_DATA_WIDTH; i++)
    mx.setColumn(idx - PM_DATA_WIDTH + i, pacman[frame][i]);

  // advance the animation frame
  frame += deltaFrame;
  if (frame == 0 || frame == MAX_FRAMES - 1)
    deltaFrame = -deltaFrame;

  // check if we are completed and set initialize for next time around
  if (idx == mx.getColumnCount() + PM_DATA_WIDTH) bInit = true;

  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);

  return(bInit);
}

bool graphicArrowRotate(bool bInit)            //==17==
{
  static uint16_t idx;        // transformation index

  uint8_t arrow[COL_SIZE] =
  {
    0b00000000,
    0b00011000,
    0b00111100,
    0b01111110,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00000000
  };

  MD_MAX72XX::transformType_t  t[] =
  {
    MD_MAX72XX::TRC, MD_MAX72XX::TRC,
    MD_MAX72XX::TSR, MD_MAX72XX::TSR, MD_MAX72XX::TSR, MD_MAX72XX::TSR, MD_MAX72XX::TSR, MD_MAX72XX::TSR, MD_MAX72XX::TSR, MD_MAX72XX::TSR,
    MD_MAX72XX::TRC, MD_MAX72XX::TRC,
    MD_MAX72XX::TSL, MD_MAX72XX::TSL, MD_MAX72XX::TSL, MD_MAX72XX::TSL, MD_MAX72XX::TSL, MD_MAX72XX::TSL, MD_MAX72XX::TSL, MD_MAX72XX::TSL,
    MD_MAX72XX::TRC,
  };

  // are we initializing?
  if (bInit)
  {
    PRINTS("\n--- ArrowRotate init");
    resetMatrix();
    bInit = false;
    idx = 0;

    // use the arrow bitmap
    mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
    for (uint8_t j = 0; j<mx.getDeviceCount(); j++)
      mx.setBuffer(((j + 1)*COL_SIZE) - 1, COL_SIZE, arrow);
    mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
  }

  // Is it time to animate?
  if (millis() - prevTimeAnim < ARROWR_DELAY)
    return(bInit);
  prevTimeAnim = millis();    // starting point for next time

  mx.control(MD_MAX72XX::WRAPAROUND, MD_MAX72XX::ON);
  mx.transform(t[idx++]);
  mx.control(MD_MAX72XX::WRAPAROUND, MD_MAX72XX::OFF);

  // check if we are completed and set initialize for next time around
  if (idx == (sizeof(t) / sizeof(t[0]))) bInit = true;

  return(bInit);
}

bool graphicSinewave(bool bInit)               //==18==
{
  static uint8_t curWave = 0;
  static uint8_t idx;

  #define SW_DATA_WIDTH  11    // valid data count followed by up to 10 data points
  const uint8_t waves[][SW_DATA_WIDTH] =
  {
    {  9,   8,  6,   1,   6,  24,  96, 128,  96,  16,   0 },
    {  6,  12,  2,  12,  48,  64,  48,   0,   0,   0,   0 },
    { 10,  12,   2,   1,   2,  12,  48,  64, 128,  64, 48 },

  };
  const uint8_t WAVE_COUNT = sizeof(waves) / (SW_DATA_WIDTH * sizeof(uint8_t));

  // are we initializing?
  if (bInit)
  {
    PRINTS("\n--- Sinewave init");
    resetMatrix();
    bInit = false;
    idx = 1;
  }

  // Is it time to animate?
  if (millis() - prevTimeAnim < SINE_DELAY)
    return(bInit);
  prevTimeAnim = millis();    // starting point for next time

  mx.control(MD_MAX72XX::WRAPAROUND, MD_MAX72XX::ON);
  mx.transform(MD_MAX72XX::TSL);
  mx.setColumn(0, waves[curWave][idx++]);
  if (idx > waves[curWave][0])
  {
    curWave = random(WAVE_COUNT);
    idx = 1;
  }
  mx.control(MD_MAX72XX::WRAPAROUND, MD_MAX72XX::OFF);

  return(bInit);
}

//========================================= DONE MIGRASI INIH ==============================

bool rows(bool bInit)                          //==19==done
{
  static uint8_t currentRow = 0;

  unsigned long currentTime = millis();

  // are we initializing?
  if (bInit)
  {
    PRINTS("\n--- rows init");
    resetMatrix();
    bInit = false;
  }

  // Is it time to animate?
  if (millis() - prevTimeAnim < ROWS_DELAY){
    return(bInit);
  prevTimeAnim = millis();}    // starting point for next time
  
  if (currentTime - lastUpdateTimeAnimation >= ROWS_DELAY)
  {
    lastUpdateTimeAnimation = currentTime;

    PRINT("\nRows ", currentRow);
    mx.clear();
    mx.setRow(currentRow, 0xff);

    currentRow++;

    if (currentRow >= ROW_SIZE)
      currentRow = 0;
  }
  return(bInit);
}

bool checkboard(bool bInit)                    //==20==done
{ 
  static uint8_t pattern = 0;
  uint8_t chkCols[][2] = {{0x55, 0xaa}, {0x33, 0xcc}, {0x0f, 0xf0}, {0xff, 0x00}};
  uint8_t col = 0;
  uint8_t idx = 0;
  uint8_t rep = 1 << pattern;

  // are we initializing?
  if (bInit)
  {
    PRINTS("\n--- checkboard init");
    resetMatrix();
    bInit = false;
  }

  // Is it time to animate?
  if (millis() - prevTimeAnim < CHKBRD_DELAY){
    return(bInit);
  prevTimeAnim = millis(); }   // starting point for next time
  
  while (col < mx.getColumnCount())
  {
    for (uint8_t r = 0; r < rep; r++)
      mx.setColumn(col++, chkCols[pattern][idx]); // use odd/even column masks
    idx++;
    if (idx > 1)
      idx = 0;
  }

  // Check if it's time to switch to the next pattern
  unsigned long currentTime = millis();
  if (currentTime - lastUpdateTimeAnimation >= CHKBRD_DELAY)
  {
    lastUpdateTimeAnimation = currentTime;
    pattern = (pattern + 1) % 3; // Switch to the next pattern
  }
  return(bInit);
}

bool bullseye(bool bInit)                      //==21==done
{
  // are we initializing?
  if (bInit)
  {
    PRINTS("\n--- bullsye init");
    resetMatrix();
    mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
    bInit = false;
  }
  
  // Is it time to animate?
  if (millis() - prevTimeAnim < BULLS_DELAY){
    return(bInit);
  prevTimeAnim = millis();}    // starting point for next time
  
  PRINTS("\nBullseye");
  mx.clear();
  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);

  uint32_t previousMillis = 0;

    byte b = 0xff;
    int i = 0;

    while (b != 0x00)
    {
      if (millis() - previousMillis >= BULLS_DELAY)
      {
        for (uint8_t j = 0; j < MAX_DEVICES + 1; j++)
        {
          mx.setRow(j, i, b);
          mx.setColumn(j, i, b);
          mx.setRow(j, ROW_SIZE - 1 - i, b);
          mx.setColumn(j, COL_SIZE - 1 - i, b);
        }
        mx.update();

        for (uint8_t j = 0; j < MAX_DEVICES + 1; j++)
        {
          mx.setRow(j, i, 0);
          mx.setColumn(j, i, 0);
          mx.setRow(j, ROW_SIZE - 1 - i, 0);
          mx.setColumn(j, COL_SIZE - 1 - i, 0);
        }

        bitClear(b, i);
        bitClear(b, 7 - i);
        i++;
        previousMillis = millis();
      }
    }

    while (b != 0xff)
    {
      if (millis() - previousMillis >= BULLS_DELAY)
      {
        for (uint8_t j = 0; j < MAX_DEVICES + 1; j++)
        {
          mx.setRow(j, i, b);
          mx.setColumn(j, i, b);
          mx.setRow(j, ROW_SIZE - 1 - i, b);
          mx.setColumn(j, COL_SIZE - 1 - i, b);
        }
        mx.update();

        for (uint8_t j = 0; j < MAX_DEVICES + 1; j++)
        {
          mx.setRow(j, i, 0);
          mx.setColumn(j, i, 0);
          mx.setRow(j, ROW_SIZE - 1 - i, 0);
          mx.setColumn(j, COL_SIZE - 1 - i, 0);
        }

        i--;
        bitSet(b, i);
        bitSet(b, 7 - i);
        previousMillis = millis();
      }
    }

  return(bInit);
  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
}

bool stripe(bool bInit)                        //==22==done
{
  // are we initializing?
  if (bInit)
  {
    PRINTS("\n--- stripe init");
    resetMatrix();
    bInit = false;
  }

  // Is it time to animate?
  if (millis() - prevTimeAnim < STRIPE_DELAY){
    return(bInit);
  prevTimeAnim = millis();}    // starting point for next time
  
  const uint16_t maxCol = MAX_DEVICES * ROW_SIZE;
  const uint8_t stripeWidth = 10;
  PRINTS("\nEach individually by row then col");
  mx.clear();

  unsigned long lastUpdateTime = millis();

  for (uint16_t col = 0; col < maxCol + ROW_SIZE + stripeWidth;)
  {
    unsigned long currentTime = millis();

    // Check if enough time has passed since the last update
    if (currentTime - lastUpdateTime >= STRIPE_DELAY)
    {
      for (uint8_t row = 0; row < ROW_SIZE; row++)
      {
        mx.setPoint(row, col - row, true);
        mx.setPoint(row, col - row - stripeWidth, false);
      }

      col++;
      lastUpdateTime = currentTime; // Update the last update time
    }
  }
  return(bInit);
}

bool StripeTriangle(bool bInit)                //==23==done
{
  const uint16_t maxCol = MAX_DEVICES * (ROW_SIZE+3);
  const uint8_t stripeWidth = 5;
  
  // are we initializing?
  if (bInit)
  {
    PRINTS("\nEach individually by row then col Stripe");
    resetMatrix();
    bInit = false;
  }

  // Is it time to animate?
  if (millis() - prevTimeAnim < STRIPE_DELAY){
    return(bInit);
  prevTimeAnim = millis();}    // starting point for next time
  
  mx.clear();

  unsigned long lastUpdateTime = millis();
  int8_t direction = 1; // 1 for moving to the right, -1 for moving to the left

  for (uint16_t col = 0; col < maxCol + ROW_SIZE + stripeWidth;)
  {
    unsigned long currentTime = millis();

    // Check if enough time has passed since the last update
    if (currentTime - lastUpdateTime >= STRIPE_DELAY)
    {
      // Clear both the old and new stripe positions
      for (uint8_t row = 0; row < ROW_SIZE; row++)
      {
        mx.setPoint(row, col - row, false);
        mx.setPoint(row, col - row - stripeWidth, false);
      }

      // Draw the new stripe position
      for (uint8_t row = 0; row < ROW_SIZE; row++)
      {
        mx.setPoint(row, col - row, true);
      }

      if (direction == -1){
        for (uint8_t row = 0; row < ROW_SIZE; row++)
        {
          mx.setPoint(row, col + row, false);
//          mx.setPoint(row, col - row + stripeWidth, false);
        }
      }

      col += direction;

      // Change direction when reaching the edge
      if (col <= 0 || col >= maxCol)
      {
        direction *= -1;
        col += 2 * direction; // Move two steps to ensure a smooth transition
      }

      lastUpdateTime = currentTime; // Update the last update time
    }
  }
  return(bInit);
}

bool stripeBounce(bool bInit) {
  static int positions[8] = {0, 1, 2, 3, 4, 5, 6, 7};
  static int ROW_POSITIONS[8] = {0, 1, 2, 3, 4, 5, 6, 7};
  static int directions[8] = {1, 1, 1, 1, 1, 1, 1, 1};
  static uint32_t lastUpdateTime = 0;
  const int ballLength = 7;  // Set the length of the ball

  // are we initializing?
  if (bInit) {
    PRINTS("\nEach individually by row then col Stripe bouncing");
    resetMatrix();
    bInit = false;
  }

  // Is it time to animate?
  if (millis() - prevTimeAnim < STRIPE_DELAY) {
    return bInit;
  }
  prevTimeAnim = millis(); // starting point for the next time

  uint32_t currentTime = millis();

  if (currentTime - lastUpdateTime >= STRIPE_DELAY) {
    lastUpdateTime = currentTime;

    // Clear the matrix
    mx.clear();

    // Draw each ball as a line segment at its current position
    for (int ball = 0; ball < 8; ++ball) {
      for (int i = 0; i < ballLength; ++i) {
        int col = positions[ball] + i;
        if (col >= 0 && col < MAX_DEVICES * ROW_SIZE) {
          mx.setPoint(ROW_POSITIONS[ball], col, true);
        }

        col = (positions[ball] + i) + 16;
        if (col >= 0 && col < MAX_DEVICES * ROW_SIZE) {
          mx.setPoint(ROW_POSITIONS[ball], col, true);
        }
      }
    }

    // Update the matrix
    mx.update();
    
    // Update the positions based on the bounce logic for each ball
    for (int ball = 0; ball < 8; ++ball) {
      positions[ball] += directions[ball];

      // Change direction for each ball if it reaches the edges
      if (positions[ball] == 0 || positions[ball] == 16 - ballLength) {
        directions[ball] = -directions[ball];
      }
    }
  }

  return bInit;
}



bool spiral(bool bInit)                        //==25==done
{
  // are we initializing?
  if (bInit)
  {
    PRINTS("\n--- spiral init");
    resetMatrix();
    bInit = false;
  }
  
  // Is it time to animate?
  if (millis() - prevTimeAnim < SPIRAL_DELAY/MAX_DEVICES){
    return(bInit);
  prevTimeAnim = millis();}    // starting point for next time
  
  PRINTS("\nSpiral in");
  int  rmin = 0, rmax = ROW_SIZE - 1;
  int  cmin = 0, cmax = (COL_SIZE * MAX_DEVICES) - 1;

  mx.clear();

  unsigned long lastUpdateTime = millis();

  while ((rmax > rmin) && (cmax > cmin))
  {
    unsigned long currentTime = millis();

    // do row
    if (currentTime - lastUpdateTime >= SPIRAL_DELAY)
    {
      for (int i = cmin; i <= cmax; i++)
      {
        mx.setPoint(rmin, i, true);
        lastUpdateTime = currentTime;
      }
      rmin++;

      // do column
      for (uint8_t i = rmin; i <= rmax; i++)
      {
        mx.setPoint(i, cmax, true);
        lastUpdateTime = currentTime;
      }
      cmax--;

      // do row
      for (int i = cmax; i >= cmin; i--)
      {
        mx.setPoint(rmax, i, true);
        lastUpdateTime = currentTime;
      }
      rmax--;

      // do column
      for (uint8_t i = rmax; i >= rmin; i--)
      {
        mx.setPoint(i, cmin, true);
        lastUpdateTime = currentTime;
      }
      cmin++;
    }
  }
  return(bInit);
}

void setupBalls()                              //==26==DONT USE, JUST SETUP
{
  for (int i = 0; i < numberOfBalls; ++i) {
    balls[i].r = i == 3 ? maxR : random(minR, maxR);
    balls[i].c = random(minC, maxC);
    balls[i].dR = (random(0, 2) == 0) ? 1 : -1;
    balls[i].dC = (random(0, 2) == 0) ? 1 : -1;
  }
}

bool bounce3(bool bInit)                       //==27==DONE
{

  // are we initializing?
  if (bInit)
  {
    PRINTS("\n--- bounce init");
    resetMatrix();
    bInit = false;
  }

  // Is it time to animate?
  if (millis() - prevTimeAnim < BOUNCE_DELAY){
    return(bInit);
  prevTimeAnim = millis();}    // starting point for next time

  if (millis() - lastUpdateTimeAnimation >= BOUNCE_DELAY) {
    mx.clear();

    for (int i = 0; i < numberOfBalls; ++i) {
      mx.setPoint(balls[i].r, balls[i].c, true);

      balls[i].r += balls[i].dR;
      balls[i].c += balls[i].dC;

      // Check and invert direction when hitting boundaries
      if (balls[i].r == minR || balls[i].r == maxR) {
        balls[i].dR = -balls[i].dR;
      }
      if (balls[i].c == minC || balls[i].c == maxC) {
        balls[i].dC = -balls[i].dC;
      }

      balls[i].r = constrain(balls[i].r, minR, maxR); // Ensure within bounds
      balls[i].c = constrain(balls[i].c, minC, maxC);

      mx.setPoint(balls[i].r, balls[i].c, true);
    }

    lastUpdateTimeAnimation = millis(); // Update the last update time
  }
  return(bInit);
}

bool moveTwoOutlineBoxes(bool bInit)           //==28==DONE
{
  const int rectWidth = 6;
  const int rectHeight = 4;

  const int minC = 0;
  const int maxC = mx.getColumnCount() - 1 - rectWidth;
  const int minR = 0;
  const int maxR = ROW_SIZE - rectHeight;

  static int nCounter = 0;
  static int r1 = minR, c1 = minC;
  static int r2 = maxR - rectHeight + 1, c2 = maxC - rectWidth + 1;
  static int8_t dR1 = 1, dC1 = 1; // delta row and column for box 1
  static int8_t dR2 = -1, dC2 = -1; // delta row and column for box 2

  static unsigned long previousMillis = 0;

  // are we initializing?
  if (bInit)
  {
  PRINTS("\nMoving Two Outline Boxes");
    resetMatrix();
    bInit = false;
  }

  // Is it time to animate?
  if (millis() - prevTimeAnim < BOX_DELAY){
    return(bInit);
  prevTimeAnim = millis();}    // starting point for next time
  

  unsigned long currentMillis = millis();

  // Check if enough time has passed since the last movement
  if (currentMillis - previousMillis >= BOX_DELAY)
  {
    // Move the boxes
    r1 += dR1;
    c1 += dC1;

    r2 += dR2;
    c2 += dC2;

    // Ensure the boxes stay within bounds
    r1 = constrain(r1, minR, maxR);
    c1 = constrain(c1, minC, maxC);

    r2 = constrain(r2, minR, maxR);
    c2 = constrain(c2, minC, maxC);

    // Clear the entire matrix
    mx.clear();

    // Draw the outline of the boxes at the new positions
    for (int i = r1; i < r1 + rectHeight; i++)
    {
      mx.setPoint(i, c1, true);
      mx.setPoint(i, c1 + rectWidth - 1, true);
    }

    for (int j = c1; j < c1 + rectWidth; j++)
    {
      mx.setPoint(r1, j, true);
      mx.setPoint(r1 + rectHeight - 1, j, true);
    }

    for (int i = r2; i < r2 + rectHeight; i++)
    {
      mx.setPoint(i, c2, true);
      mx.setPoint(i, c2 + rectWidth - 1, true);
    }

    for (int j = c2; j < c2 + rectWidth; j++)
    {
      mx.setPoint(r2, j, true);
      mx.setPoint(r2 + rectHeight - 1, j, true);
    }

    // Reset the timer
    previousMillis = currentMillis;

    // Check for boundaries and change direction if needed
    if ((r1 == minR) || (r1 == maxR))
      dR1 = -dR1;
    if ((c1 == minC) || (c1 == maxC))
      dC1 = -dC1;

    if ((r2 == minR) || (r2 == maxR))
      dR2 = -dR2;
    if ((c2 == minC) || (c2 == maxC))
      dC2 = -dC2;

    // Increase counter and reset if necessary
    if (++nCounter >= 50)
    {
      nCounter = 0;
      r1 = minR;
      c1 = minC;
      r2 = maxR - rectHeight + 1;
      c2 = maxC - rectWidth + 1;
    }
  }

  // Update the display
  mx.update();
  return(bInit);
}

bool waveBounce2(bool bInit)                   //==29==DONE upgrade
{
  const int chainLength = 10; // Adjust the length of the chain to fit inside the matrix
  static int nCounter = 0;
  static int r = 0, c = 1;
  static int8_t dR = 1, dC = 1; // delta row and column

  // Buffer to store the LED states before updating
  static bool displayBuffer[ROW_SIZE][MAX_DEVICES * COL_SIZE];

  // are we initializing?
  if (bInit)
  {
    PRINTS("\nWave Bounce");
    resetMatrix();
    bInit = false;
  }

  // Is it time to animate?
  if (millis() - prevTimeAnim < WAVE_DELAY)
  {
    return (bInit);
    prevTimeAnim = millis();
  } // starting point for next time

  unsigned long currentTime = millis();

  // Clear the buffer
  memset(displayBuffer, 0, sizeof(displayBuffer));

  // Draw the chain links at the new position in the buffer
  for (int i = 0; i < chainLength; i++)
  {
    int row = r + i;
    int col = c + i;

    if (row >= 0 && row < ROW_SIZE)
      displayBuffer[row][col] = true;

    if (row >= 0 && row < ROW_SIZE && COL_SIZE * MAX_DEVICES - 1 - col >= 0 && COL_SIZE * MAX_DEVICES - 1 - col < COL_SIZE * MAX_DEVICES)
      displayBuffer[row][COL_SIZE * MAX_DEVICES - 1 - col] = true;
  }

  // Gradually turn off the previously lit LEDs
  for (int row = 0; row < ROW_SIZE; row++)
  {
    for (int col = 0; col < MAX_DEVICES * COL_SIZE; col++)
    {
      if (!displayBuffer[row][col])
      {
        mx.setPoint(row, col, false);
      }
    }
  }

  // Copy the buffer to the display
  for (int row = 0; row < ROW_SIZE; row++)
  {
    for (int col = 0; col < MAX_DEVICES * COL_SIZE; col++)
    {
      if (displayBuffer[row][col])
      {
        mx.setPoint(row, col, true);
      }
    }
  }

  // Update the display
  mx.update();

  // Move the chain
  if (currentTime - lastUpdateTimeAnimation >= WAVE_DELAY)
  {
    r += dR;
    c += dC;

    // Check for boundaries and change direction if needed
    if ((r <= 0) || (r >= ROW_SIZE - chainLength))
      dR = -dR;
    if ((c <= 0) || (c >= COL_SIZE * MAX_DEVICES - 1 - chainLength))
      dC = -dC;

    nCounter++;

    if (nCounter >= 43)
    {
      // Reset the counter and initial position after 50 iterations
      nCounter = 0;
      r = 0;
      c = 1;
    }

    lastUpdateTimeAnimation = currentTime; // Update the last update time
  }

  return (bInit);
}

bool DoubleRows(bool bInit)                    //==30==DONE
{
const uint8_t ROW_WAVE_HEIGHT_UPPER = 5; // Adjust as needed
const uint8_t ROW_WAVE_HEIGHT_LOWER = 3; // Adjust as needed
  static int8_t upperRow = 0;
  static int8_t lowerRow = ROW_SIZE - 1;
  static bool upperDirectionUp = true;
  static bool lowerDirectionUp = false;

  unsigned long currentTime = millis();

  // are we initializing?
  if (bInit)
  {
    PRINTS("\n--- Double rows init");
    resetMatrix();
    bInit = false;
  }

  // Is it time to animate?
  if (millis() - prevTimeAnim < ROWS_DELAY){
    return(bInit);
  prevTimeAnim = millis();}    // starting point for next time
  
  if (currentTime - lastUpdateTimeAnimation >= ROWS_DELAY)
  {
    lastUpdateTimeAnimation = currentTime;

    // Upper row
    PRINT("\nRows ", upperRow);
    mx.clear();
    mx.setRow(upperRow, 0xff);

    if (upperDirectionUp)
    {
      upperRow++;
      if (upperRow >= ROW_SIZE - ROW_WAVE_HEIGHT_UPPER)
      {
        upperDirectionUp = false;
      }
    }
    else
    {
      upperRow--;
      if (upperRow <= 0)
      {
        upperDirectionUp = true;
      }
    }

    // Lower row
    PRINT("\nRows ", lowerRow);
    mx.setRow(lowerRow, 0xff);

    if (lowerDirectionUp)
    {
      lowerRow--;
      if (lowerRow <= ROW_WAVE_HEIGHT_LOWER)
      {
        lowerDirectionUp = false;
      }
    }
    else
    {
      lowerRow++;
      if (lowerRow >= ROW_SIZE - 1)
      {
        lowerDirectionUp = true;
      }
    }
  }
  return(bInit);
}

bool animateTriangle(bool bInit)               //==31==  upgrade
{
  const int centerColStart = 15; // adjusted center column start
  const int centerColEnd = 16; // adjusted center column end
  const int centerRowStart = 3; // adjusted center row start
  const int centerRowEnd = 6; // adjusted center row end
  const int maxRadius = 17; // adjust for desired animation size

  static int radius = 1;
  static bool expanding = true;

  // Buffer to store the LED states before updating
  static bool displayBuffer[ROW_SIZE][MAX_DEVICES * ROW_SIZE];

  // are we initializing?
  if (bInit)
  {
    PRINTS("\n--- Double rows init");
    resetMatrix();
    bInit = false;
  }

  // Is it time to animate?
  if (millis() - prevTimeAnim < TRIGLE_DELAY){
    return(bInit);
  prevTimeAnim = millis();}    // starting point for next time
  
    unsigned long currentTime = millis();

    if (currentTime - lastUpdateTimeAnimation >= TRIGLE_DELAY) {
      if (expanding) {
        radius++;
      } else {
        radius--;
      }

      if (radius == maxRadius) {
        expanding = false;
      } else if (radius == 1) {
        expanding = true;
      }

      // Clear the buffer
      memset(displayBuffer, 0, sizeof(displayBuffer));

      for (int row = 0; row < ROW_SIZE; row++) {
        int deltaRow = abs(row - centerRowStart);
        if (deltaRow > radius) {
          continue; // skip rows outside triangle
        }

        for (int col = centerColStart - radius; col <= centerColEnd + radius; col++) {
          int deltaCol = abs(col - centerColStart);
          if (deltaCol > radius) {
            continue; // skip columns outside triangle
          }

          // check if point is within triangle based on both deltas
          if (deltaRow <= radius - deltaCol || deltaCol <= radius - deltaRow) {
            displayBuffer[row][col] = true; // set point within triangle
          }
        }
      }

      // Gradually turn off the previously lit LEDs
      for (int row = 0; row < ROW_SIZE; row++) {
        for (int col = 0; col < MAX_DEVICES * ROW_SIZE; col++) {
          if (!displayBuffer[row][col]) {
            mx.setPoint(row, col, false);
          }
        }
      }

      // Copy the buffer to the display
      for (int row = 0; row < ROW_SIZE; row++) {
        for (int col = 0; col < MAX_DEVICES * ROW_SIZE; col++) {
          if (displayBuffer[row][col]) {
            mx.setPoint(row, col, true);
          }
        }
      }

      lastUpdateTimeAnimation = currentTime;
    }
  return(bInit);
}

bool curtainAnim(bool bInit)                   //==32==DONE
{
  const int maxCol = (mx.getColumnCount() / 2) - 1; // center of matrix columns
  const int maxRadius = 17; // adjust for desired animation size

  static int radius = 1;
  static bool expanding = true;

  // are we initializing?
  if (bInit)
  {
    PRINTS("\n--- Double rows init");
    resetMatrix();
    bInit = false;
  }

  // Is it time to animate?
  if (millis() - prevTimeAnim < CRTN_DELAY){
    return(bInit);
  prevTimeAnim = millis();}    // starting point for next time
  
    unsigned long currentTime = millis();

    if (currentTime - lastUpdateTimeAnimation >= CRTN_DELAY) {
      if (expanding) {
        radius++;
      } else {
        radius--;
      }

      if (radius == maxRadius) {
        expanding = false;
      } else if (radius == 1) {
        expanding = true;
      }

      for (int row = 0; row < ROW_SIZE; row++) {
        for (int col = maxCol - radius; col <= maxCol + radius; col++) {
          int distance = abs(col - maxCol);
          bool isOn = distance <= radius && distance >= radius - 1;
          mx.setPoint(row, col, isOn);
        }
      }

      lastUpdateTimeAnimation = currentTime;
    }
  return(bInit);
}

bool boxAnim(bool bInit)                       //==33==DONE
{
    byte BOX1[8] = {
        B00111111,
        B00100001,
        B11111101,
        B10100101,
        B10100101,
        B10111111,
        B10000100,
        B11111100
    };
    byte BOX2[8] = {
        B01111110,
        B01000010,
        B01111110,
        B01000010,
        B01000010,
        B01111110,
        B01000010,
        B01111110
    };
    byte BOX3[8] = {
        B11111100,
        B10000100,
        B10111111,
        B10100101,
        B10100101,
        B11111101,
        B00100001,
        B00111111
    };
    byte BOX4[8] = {
        B00000000,
        B11111111,
        B10100101,
        B10100101,
        B10100101,
        B10100101,
        B11111111,
        B00000000
    };
    byte HEART[8] = {
        B00011000,
        B00111100,
        B01100110,
        B10000001,
        B10000001,
        B10011001,
        B11111111,
        B01100110
    };

    byte* box[4] = {BOX1, BOX2, BOX3, BOX4};
    static unsigned long lastUpdateTime = 0;
    static int currentBox = 0;

    // are we initializing?
    if (bInit)
    {
    PRINTS("\nMoving Two Outline Boxes");
      resetMatrix();
      bInit = false;
    }
  
    // Is it time to animate?
    if (millis() - prevTimeAnim < BOX_DELAY){
      return(bInit);
    prevTimeAnim = millis();}    // starting point for next time
    
    if (millis() - lastUpdateTime >= BOX_DELAY)
    {
        for (int y = 7; y >= 0; y--)
        {
            for (int x = 0; x <= 7; x++)
            {
                if (box[currentBox][(7 - y)] & (B10000000 >> x))
                {
                    mx.setPoint(y, x, true);
                    mx.setPoint(y, x + 8, true);
                    mx.setPoint(y, x + 16, true);
                    mx.setPoint(y, x + 24, true);
                }
                else
                {
                    mx.setPoint(y, x, false);
                    mx.setPoint(y, x + 8, false);
                    mx.setPoint(y, x + 16, false);
                    mx.setPoint(y, x + 24, false);
                }
            }
        }

        mx.update(); // Update the display
        lastUpdateTime = millis();

        currentBox++;
        if (currentBox >= 4)
        {
            currentBox = 0;
        }
    }
  return(bInit);
}

bool animateTriangle2(bool bInit, uint8_t mo) //==33==DONE upgrade
{
  uint8_t centerColStart = 15, centerColEnd = 16, centerRow, maxRadius, delayTime;
  centerRow = 3;
  maxRadius = 10;
  delayTime = 30;

  static int radius = 1;
  static bool expanding = true;
  static bool expandingHorizontally = true;
  static bool expandingVertically = true;

  // Buffer to store the LED states before updating
  static bool displayBuffer[ROW_SIZE][MAX_DEVICES * ROW_SIZE];

  // are we initializing?
  if (bInit)
  {
    PRINTS("\nMoving Two ROWS");
    resetMatrix();
    bInit = false;
  }

  // Is it time to animate?
  if (millis() - prevTimeAnim < TRIGLE_DELAY)
  {
    return bInit;
  }
  prevTimeAnim = millis(); // starting point for the next time

  unsigned long currentTime = millis();

  if (currentTime - lastUpdateTimeAnimation >= TRIGLE_DELAY)
  {
    // Clear the buffer
    memset(displayBuffer, 0, sizeof(displayBuffer));

    // update radius based on expansion/contraction
    if (expanding)
    {
      radius++;
    }
    else
    {
      radius--;
    }

    // check if radius reached limits
    if (radius == maxRadius)
    {
      expanding = false;
    }
    else if (radius == 1)
    {
      expanding = true;
    }

    // update direction for horizontal expansion/contraction at edges
    if (expandingHorizontally)
    {
      if (centerColStart + radius >= mx.getColumnCount() - 1)
      {
        expandingHorizontally = false;
      }
    }
    else
    {
      if (centerColStart - radius <= 0)
      {
        expandingHorizontally = true;
      }
    }

    // update direction for vertical expansion/contraction at edges
    if (expandingVertically)
    {
      if (centerRow + radius >= ROW_SIZE - 1)
      {
        expandingVertically = false;
      }
    }
    else
    {
      if (centerRow - radius <= 0)
      {
        expandingVertically = true;
      }
    }

    // set points within the new triangle area with a width of 2 pixels for centerRow
    for (int row = centerRow - radius; row <= centerRow + radius; row++)
    {
      int deltaRow = abs(centerRow - row);
      int colStart = centerColStart - radius + deltaRow;
      int colEnd = centerColEnd + radius - deltaRow;

      // Ensure that only 2 pixels width is set for centerRow
      if (row == centerRow + radius || row == centerRow - radius)
      {
        colEnd = min(colEnd, colStart + 1);
      }

      for (int col = colStart; col <= colEnd; col++)
      {
        displayBuffer[row][col] = true;
      }
    }

    // Gradually turn off the previously lit LEDs
    for (int row = 0; row < ROW_SIZE; row++)
    {
      for (int col = 0; col < MAX_DEVICES * ROW_SIZE; col++)
      {
        if (!displayBuffer[row][col])
        {
          mx.setPoint(row, col, false);
        }
      }
    }

    // Copy the buffer to the display
    for (int row = 0; row < ROW_SIZE; row++)
    {
      for (int col = 0; col < MAX_DEVICES * ROW_SIZE; col++)
      {
        if (displayBuffer[row][col])
        {
          mx.setPoint(row, col, true);
        }
      }
    }

    // Update the LED matrix
    mx.update();

    lastUpdateTimeAnimation = currentTime;
  }
  return bInit;
}


bool bounce1(bool bInit)                       //==37==DONE
{
  // are we initializing?
  if (bInit)
  {
    PRINTS("\n--- bounce init");
    resetMatrix();
    bInit = false;
  }

  // Is it time to animate?
  if (millis() - prevTimeAnim < BOUNCE_DELAY){
    return(bInit);
  prevTimeAnim = millis();}    // starting point for next time
  
  const int minC = 0;
  const int maxC = mx.getColumnCount() - 1;
  const int minR = 0;
  const int maxR = ROW_SIZE - 1;

  static int nCounter = 0; // static variable to retain its value between function calls
  static int r = 0, c = 2;
  static int8_t dR = 1, dC = 1; // delta row and column
  static unsigned long lastUpdateTime = 0;

  unsigned long currentTime = millis();

  // Check if enough time has passed since the last update
  if (currentTime - lastUpdateTime >= BOUNCE_DELAY)
  {
    mx.setPoint(r, c, false);
    r += dR;
    c += dC;

    // Ensure the ball stays within bounds
    r = constrain(r, minR, maxR);
    c = constrain(c, minC, maxC);

    mx.setPoint(r, c, true);

    lastUpdateTime = currentTime; // Update the last update time

    if ((r == minR) || (r == maxR))
      dR = -dR;
    if ((c == minC) || (c == maxC))
      dC = -dC;

    nCounter++;

    if (nCounter >= 57)
    {
      // Reset the animation after 50 iterations
      nCounter = 0;
      r = 0;
      c = 2;
      dR = 1;
      dC = 1;
      mx.clear();
    }
  }
  return(bInit);
}


bool animateCross(bool bInit)
{
  const uint8_t propellerSize = 5;         // Adjust the size of the propeller
  const uint8_t minSpeed = 30;             // Minimum speed in milliseconds
  const uint8_t maxSpeed = 100;            // Maximum speed in milliseconds
  const uint8_t speedChangeInterval = 100; // Interval to change speed

  static unsigned long lastUpdateTime = 0;
  static unsigned long lastSpeedChangeTime = 0;
  static unsigned long currentSpeed = minSpeed;
  static int rotationIndex = 0;

  // Buffer to store the LED states before updating
  static bool displayBuffer[ROW_SIZE][MAX_DEVICES * COL_SIZE];

  // are we initializing?
  if (bInit)
  {
    PRINTS("\n--- Cross init");
    resetMatrix();
    lastUpdateTime = 0;
    lastSpeedChangeTime = 0;
    currentSpeed = minSpeed;
    rotationIndex = 0;
    bInit = false;
  }

  // Is it time to animate?
  if (millis() - prevTimeAnim < CROSS_DELAY)
  {
    return bInit;
  }
  prevTimeAnim = millis(); // starting point for the next time

  PRINT("\nCross Rotation Index:", rotationIndex);

  unsigned long currentTime = millis();

  // Clear the buffer
  memset(displayBuffer, 0, sizeof(displayBuffer));

  if (currentTime - lastUpdateTime >= currentSpeed)
  {
    // Draw the spinning propeller in the buffer
    for (int i = 0; i < propellerSize; ++i)
    {
      int horizontalBlade = (rotationIndex + i) % COL_SIZE;
      int verticalBlade = (rotationIndex + i) % ROW_SIZE;

      displayBuffer[2][horizontalBlade] = true;        // Horizontal blade
      displayBuffer[5][horizontalBlade] = true;        // Horizontal blade
      displayBuffer[verticalBlade][2] = true;          // Vertical blade
      displayBuffer[verticalBlade][5] = true;          // Vertical blade

      displayBuffer[2][horizontalBlade + 8] = true;    // Horizontal blade
      displayBuffer[5][horizontalBlade + 8] = true;    // Horizontal blade
      displayBuffer[verticalBlade][10] = true;         // Vertical blade
      displayBuffer[verticalBlade][13] = true;         // Vertical blade

      displayBuffer[2][horizontalBlade + 16] = true;   // Horizontal blade
      displayBuffer[5][horizontalBlade + 16] = true;   // Horizontal blade
      displayBuffer[verticalBlade][18] = true;         // Vertical blade
      displayBuffer[verticalBlade][21] = true;         // Vertical blade

      displayBuffer[2][horizontalBlade + 24] = true;   // Horizontal blade
      displayBuffer[5][horizontalBlade + 24] = true;   // Horizontal blade
      displayBuffer[verticalBlade][26] = true;         // Vertical blade
      displayBuffer[verticalBlade][29] = true;         // Vertical blade
    }

    // Gradually turn off the previously lit LEDs
    for (int row = 0; row < ROW_SIZE; row++)
    {
      for (int col = 0; col < MAX_DEVICES * COL_SIZE; col++)
      {
        if (!displayBuffer[row][col])
        {
          mx.setPoint(row, col, false);
        }
      }
    }

    // Copy the buffer to the display
    for (int row = 0; row < ROW_SIZE; row++)
    {
      for (int col = 0; col < MAX_DEVICES * COL_SIZE; col++)
      {
        if (displayBuffer[row][col])
        {
          mx.setPoint(row, col, true);
        }
      }
    }

    // Update the LED matrix
    mx.update();

    // Increment the rotation index for the next frame
    rotationIndex++;

    // Check if it's time to change the speed
    if (currentTime - lastSpeedChangeTime >= speedChangeInterval)
    {
      // Use a sinusoidal function to smoothly vary the speed
      currentSpeed = minSpeed + ((maxSpeed - minSpeed) / 2) * (1 + sin(2 * PI * currentTime / 10000.0));

      lastSpeedChangeTime = currentTime;
    }

    lastUpdateTime = currentTime;
  }
  return bInit;
}




bool ShiftAnimation(bool bInit) {
  static unsigned long previousMillis = 0;
  static unsigned long interval = CROSS_DELAY;
  static int speed = 15;

  byte propellerPattern[] = {
      B00011000,
      B00111100,
      B01111110,
      B11111111,
      B11111111,
      B01111110,
      B00111100,
      B00011000
  };
  int numFrames = sizeof(propellerPattern) / sizeof(propellerPattern[0]);

  // are we initializing?
  if (bInit) {
    PRINTS("\n--- shift init");
    resetMatrix();
    previousMillis = 0;
    interval = CROSS_DELAY;
    speed = 15;
    bInit = false;
  }

  // Is it time to animate?
  if (millis() - prevTimeAnim < CROSS_DELAY) {
    return bInit;
  }
  prevTimeAnim = millis();  // starting point for the next time

  PRINT("\nShift Animation Speed:", speed);

  unsigned long currentMillis = millis();

  // Check if it's time to update the animation.
  if (currentMillis - previousMillis >= interval) {
    // Update the previousMillis variable.
    previousMillis = currentMillis;

    // Increase the speed and decrease the interval for the next iteration.
    speed -= 5;
    interval -= 100;

    // Check if the speed has reached the minimum value.
    if (speed <= 0) {
      speed = 0;
    }
  }

  // Rotate pattern
  unsigned long rotateMillis = millis();
  byte temp = propellerPattern[numFrames - 1];
  for (int i = numFrames - 1; i > 0; i--) {
    propellerPattern[i] = propellerPattern[i - 1];
  }
  propellerPattern[0] = temp;

  // Display pattern
  for (int i = 0; i < numFrames; i++) {
    for (int j = 0; j < MAX_DEVICES; j++) {
      mx.setColumn(j, i, propellerPattern[i]);
    }

    // Check if enough time has passed to delay without blocking
    while (millis() - rotateMillis < speed) {
      // Other code can run here
    }
    rotateMillis = millis();
  }

  return bInit;
}



bool threeDBallAnimation(bool bInit) {
  const uint8_t ballRadius = 3;

  static int16_t ballX = ROW_SIZE / 2;
  static int16_t ballY = ROW_SIZE / 2;
  static int8_t ballXSpeed = 1;
  static int8_t ballYSpeed = 1;
  static uint32_t lastFrameTime = 0;

  // Buffer to store the LED states before updating
  static bool displayBuffer[ROW_SIZE][MAX_DEVICES * ROW_SIZE];

  bool draw;

  // are we initializing?
  if (bInit) {
    PRINTS("\n--- ball init");
    resetMatrix();
    ballX = ROW_SIZE / 2;
    ballY = ROW_SIZE / 2;
    ballXSpeed = 1;
    ballYSpeed = 1;
    lastFrameTime = 0;
    bInit = false;
  }

  // Is it time to animate?
  if (millis() - prevTimeAnim < BOUNCE_DELAY) {
    return bInit;
  }
  prevTimeAnim = millis();  // starting point for the next time

  uint32_t currentTime = millis();

  if (currentTime - lastFrameTime >= BOUNCE_DELAY) {
    // Draw the ball off-screen in the buffer
    draw = true;
    for (int16_t dx = -ballRadius; dx <= ballRadius; ++dx) {
      for (int16_t dy = -ballRadius; dy <= ballRadius; ++dy) {
        int16_t distanceSquared = dx * dx + dy * dy;
        if (distanceSquared <= ballRadius * ballRadius) {
          int16_t x = ballX + dx;
          int16_t y = ballY + dy;
          if (x >= 0 && x < MAX_DEVICES * ROW_SIZE && y >= 0 && y < ROW_SIZE) {
            displayBuffer[y][x] = draw;
          }
        }
      }
    }

    // Gradually turn off the previously lit LEDs
    for (int16_t x = 0; x < MAX_DEVICES * ROW_SIZE; ++x) {
      for (int16_t y = 0; y < ROW_SIZE; ++y) {
        if (!displayBuffer[y][x]) {
          mx.setPoint(y, x, false);
        }
      }
    }

    // Copy the buffer to the display
    for (int16_t x = 0; x < MAX_DEVICES * ROW_SIZE; ++x) {
      for (int16_t y = 0; y < ROW_SIZE; ++y) {
        if (displayBuffer[y][x]) {
          mx.setPoint(y, x, true);
        }
      }
    }

    // Clear the off-screen buffer for the next frame
    memset(displayBuffer, 0, sizeof(displayBuffer));

    // Update the last frame time
    lastFrameTime = currentTime;
  }

  return bInit;
}




bool animate3DCircle(bool bInit) {
  const int maxRadius = 3; // Maximum radius of the circle

  static unsigned long lastUpdateTime = 0;
  static int currentRadius = 1;
  static bool expanding = true;

  // are we initializing?
  if (bInit) {
    PRINTS("\n--- circle init");
    resetMatrix();
    currentRadius = 1;
    expanding = true;
    bInit = false;
  }

  // Is it time to animate?
  if (millis() - prevTimeAnim < CHKBRD_DELAY) {
    return bInit;
  }
  prevTimeAnim = millis();  // starting point for the next time

  PRINT("\n3D Circle Radius:", currentRadius);

  unsigned long currentTime = millis();

  if (currentTime - lastUpdateTime >= CHKBRD_DELAY) {
    mx.clear(); // Clear the matrix before updating for the next frame

    // Draw the circle
    drawCircle(COL_SIZE / 2, ROW_SIZE / 2, currentRadius);
    drawCircle((COL_SIZE / 2) - 1, (ROW_SIZE / 2) - 1, currentRadius);

    // Update the LED matrix
    mx.update();

    // Adjust the radius based on expansion or contraction
    if (expanding) {
      currentRadius++;
      if (currentRadius >= maxRadius) {
        expanding = false;
      }
    } else {
      currentRadius--;
      if (currentRadius <= 1) {
        expanding = true;
      }
    }

    lastUpdateTime = currentTime;
  }

  return bInit;
}

void drawCircle(int centerX, int centerY, int radius) {
  int x = radius;
  int y = 0;
  int radiusError = 1 - x;

  while (x >= y) {
    // Draw the circle points
    setCirclePoints(centerX, centerY, x, y);
    setCirclePoints(centerX + 8, centerY, x, y);
    setCirclePoints(centerX + 16, centerY, x, y);
    setCirclePoints(centerX + 24, centerY, x, y);

    y++;
    if (radiusError < 0) {
      radiusError += 2 * y + 1;
    } else {
      x--;
      radiusError += 2 * (y - x) + 1;
    }
  }
}

void setCirclePoints(int centerX, int centerY, int x, int y) {
  mx.setPoint(centerY + y, centerX + x, true);
  mx.setPoint(centerY + x, centerX + y, true);
  mx.setPoint(centerY - x, centerX + y, true);
  mx.setPoint(centerY - y, centerX + x, true);
  mx.setPoint(centerY - y, centerX - x, true);
  mx.setPoint(centerY - x, centerX - y, true);
  mx.setPoint(centerY + x, centerX - y, true);
  mx.setPoint(centerY + y, centerX - x, true);
}



bool animateBouncingLine(bool bInit, bool mode1) {
  static int column = 0;
  static int direction = 1; // 1 for right, -1 for left
  static unsigned long lastUpdateTime = 0;
  static unsigned long lastSpeedChangeTime = 0;
  static unsigned long currentSpeed = 30; // Initial speed
  const unsigned long speedChangeInterval = 50; // Interval to change speed

  // are we initializing?
  if (bInit) {
    PRINTS("\n--- bounce line init");
    resetMatrix();
    column = 0;
    direction = 1;
    lastUpdateTime = 0;
    lastSpeedChangeTime = 0;
    currentSpeed = 30;
    bInit = false;
  }

  // Is it time to animate?
  if (millis() - prevTimeAnim < BOUNCE_DELAY) {
    return bInit;
  }
  prevTimeAnim = millis();  // starting point for next time

  PRINT("\nBouncing Line Column:", column);
  PRINT(" Direction:", direction);

  unsigned long currentTime = millis();

  if (currentTime - lastUpdateTime >= currentSpeed) {
    // Clear the line for the next frame
    drawBouncingLine(column, mode1, false);

    // Move the line in the current direction
    column += direction;

    // Check for bouncing at the edges
    if (column <= 0 || column >= getMaxColumn(mode1)) {
      // Change direction for bouncing
      direction *= -1;
    }

    // Draw the line
    drawBouncingLine(column, mode1, true);

    // Update the LED matrix
    mx.update();

    lastUpdateTime = currentTime;

    // Check if it's time to change the speed
    if (currentTime - lastSpeedChangeTime >= speedChangeInterval) {
      // Use a sinusoidal function to smoothly vary the speed
      currentSpeed = 15 + 40 * (1 + sin(2 * PI * currentTime / 10000.0));

      lastSpeedChangeTime = currentTime;
    }
  }

  return bInit;
}

void drawBouncingLine(int column, bool mode1, bool mod) {
  const uint8_t lineHeight = 8;
  const uint8_t lineWidth = 2;

  int x1 = column;
  int y1 = 0;
  int x2 = column + lineWidth - 1;
  int y2 = lineHeight - 1;

  // Draw a line using setPoint
//  if (mode1) {
//    x1 += 8;
//    x2 += 8;
//  }else{
//    
//  }

  if (mod) {
    for (int x = x1; x <= x2; x++) {
      for (int y = y1; y <= y2; y++) {
        if(mode1){
        mx.setPoint(y, x+8, true);
        mx.setPoint(y, x+24, true);
        }
        mx.setPoint(y, x, true);
        mx.setPoint(y, x+16, true);
      }
    }
  } else {
    for (int x = x1; x <= x2; x++) {
      for (int y = y1; y <= y2; y++) {
        if(mode1){
        mx.setPoint(y, x+8, true);
        mx.setPoint(y, x+24, true);
        }
        mx.setPoint(y, x, true);
        mx.setPoint(y, x+16, true);
      }
    }
  }
}

uint8_t getMaxColumn(bool mode1) {
  return (mode1) ? ((MAX_DEVICES * COL_SIZE - 2) / 2) - 9 : ((MAX_DEVICES * COL_SIZE - 2) / 2) - 1;
}



bool animateSpinningCross(bool bInit, uint8_t mode1, bool mode2) {
  static float rotationAngle = 0.0;  // Angle of rotation for spinning effect
  static uint8_t crossSize = 16;     // Initial cross size
  static int8_t sizeChange = 1;      // Increment direction for cross size change

  // are we initializing?
  if (bInit) {
    PRINTS("\n--- spin init");
    resetMatrix();
    rotationAngle = 0.0;
    crossSize = 16;
    sizeChange = 1;
    bInit = false;
  }

  // Is it time to animate?
  if (millis() - prevTimeAnim < CROSS_DELAY) {
    return bInit;
  }
  prevTimeAnim = millis();  // starting point for next time

  // Print debug information
  PRINT("\nSpinning Cross Size:", crossSize);
  PRINT(" Angle:", rotationAngle);

  // Clear the matrix before updating for the next frame
  mx.clear();

      switch(mode1){
        case 1: crossSize = 16; break;
        case 2: crossSize = 8; break;
        case 3: crossSize = 8; break;
        case 4: crossSize = 4; break;
      }
  // Draw the spinning cross in the middle of the matrix
  drawAnimatedCross(crossSize, rotationAngle, mode1, mode2);

  mx.update();

  // Increment the rotation angle for spinning effect
  rotationAngle += 0.1;

  // Check if it's time to change the cross size
//  if (crossSize == 16 || crossSize == 4) {
//    sizeChange = -sizeChange;
//  }
//  crossSize += sizeChange;

  return bInit;
}

void drawAnimatedCross(uint8_t crossSize, float angle, uint8_t mode1, bool mode2) {
  // Calculate the center position for the matrix
  uint8_t centerX = COL_SIZE / 2;
  uint8_t centerY = ROW_SIZE / 2;

  // Draw the rotating lines of the cross
  if (mode2) {
    drawAnimatedLine(centerX - crossSize, centerY, centerX + crossSize, centerY, angle, mode1);
    drawAnimatedLine(centerX, centerY - crossSize, centerX, centerY + crossSize, angle, mode1);
  } else {
    drawAnimatedLine(centerX - crossSize, centerY, centerX + crossSize, centerY, angle, mode1);
  }
}

void drawAnimatedLine(int x0, int y0, int x1, int y1, float angle, uint8_t mode3) {    //BANTUAN ANIMATESPINNINGCROSS
  int steps = max(abs(x1 - x0), abs(y1 - y0));
  float xIncrement = (x1 - x0) / static_cast<float>(steps);
  float yIncrement = (y1 - y0) / static_cast<float>(steps);

  for (int i = 0; i <= steps; ++i) {
    int x = round(x0 + i * xIncrement);
    int y = round(y0 + i * yIncrement);
      float cosA = cos(angle);
    float sinA = sin(angle);
  
    int xRotated = int(cosA * (x - COL_SIZE / 2) - sinA * (y - ROW_SIZE / 2) + COL_SIZE / 2);
    
    int yRotated = int(sinA * (x - COL_SIZE / 2) + cosA * (y - ROW_SIZE / 2) + 8 / 2);
    int yRotated2 = int(sinA * (x - COL_SIZE / 2) + cosA * (y - ROW_SIZE / 2) + 24 / 2);
    int yRotated3 = int(sinA * (x - COL_SIZE / 2) + cosA * (y - ROW_SIZE / 2) +  40/ 2);
    int yRotated4 = int(sinA * (x - COL_SIZE / 2) + cosA * (y - ROW_SIZE / 2) + 56 / 2);
    
    int yRotated5 = int(sinA * (x - COL_SIZE / 2) + cosA * (y - ROW_SIZE / 2) + 32 / 2);
    
    int yRotated6 = int(sinA * (x - COL_SIZE / 2) + cosA * (y - ROW_SIZE / 2) +  16/ 2);
    int yRotated7 = int(sinA * (x - COL_SIZE / 2) + cosA * (y - ROW_SIZE / 2) + 48 / 2);
  
    // Draw the rotated point
    switch(mode3){
      case 1: 
        mx.setPoint(xRotated+1, yRotated5, true);
        mx.setPoint(xRotated, yRotated5, true);
        mx.setPoint(xRotated-1, yRotated5, true);
        break;
      case 2:
        mx.setPoint(xRotated, yRotated6, true);
        mx.setPoint(xRotated, yRotated7, true);
        break;
      case 3:
        mx.setPoint(xRotated+1, yRotated6, true);
        mx.setPoint(xRotated, yRotated6, true);
        mx.setPoint(xRotated-1, yRotated6, true);
        
        mx.setPoint(xRotated+1, yRotated7, true);
        mx.setPoint(xRotated, yRotated7, true);
        mx.setPoint(xRotated-1, yRotated7, true);
        break;
      case 4:
        mx.setPoint(xRotated, yRotated, true);
        mx.setPoint(xRotated, yRotated2, true);
        mx.setPoint(xRotated, yRotated3, true);
        mx.setPoint(xRotated, yRotated4, true);
        break;
    }
  }
}


// ========================================= Control routines =================================

void resetMatrix(void)
{
  mx.control(MD_MAX72XX::INTENSITY, kecerahan);
  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
  mx.clear();
  prevTimeAnim = 0;
}

void runMatrixAnimation(void){
  static  uint8_t state = 0;
  static  uint8_t mesg = 0;
  static  boolean bRestart = true;
  static boolean  bInMessages = false;
  boolean changeState = false;
    
  if (millis()-prevTimeDemo >= 1000){
    prevTimeDemo = millis();
//    timeDemo--;
    if (--timeDemo <= 0 && !bRestart){
      timeDemo = DEMO_DELAY;
      lastUpdateTimeAnimation = 0;
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
    }else{
      state++;
      bRestart = true;
    }
  }

  if (slct == 1){
    switch(state)  { 
      case 0 : bInMessages = true; 
               bRestart = scrollText(bRestart, msgTab[mesg]); 
               break;
      default : state = 0;             
    }
  }
  if (slct == 2){
    switch(state){
      case  1: bRestart = graphicMidline2(bRestart);                break;//mid
      case  2: bRestart = graphicRandom(bRestart);                  break;//ran
      case  3: bRestart = animateSpinningCross(bRestart, false, 2); break;//tanbag 
      case  4: bRestart = graphicScanner(bRestart);                 break;//scan
      case  5: bRestart = graphicSpectrum1(bRestart);               break;//
      case  6: bRestart = animateBouncingLine(bRestart, true);      break;//tanbag
      case  7: bRestart = graphicSinewave(bRestart);                break;//
      case  8: bRestart = graphicBounceBall(bRestart);              break;//
      case  9: bRestart = graphicHearts(bRestart);                  break;//
      case 10: bRestart = graphicPacman(bRestart);                  break;//
      case 11: bRestart = animateSpinningCross(bRestart, true, 4);  break;//tanbag 
      case 12: bRestart = graphicHeartbeat(bRestart);               break;//
      case 13: bRestart = graphicWiper(bRestart);                   break;///
      case 14: bRestart = graphicInvader(bRestart);                 break;//
      case 15: bRestart = animateBouncingLine(bRestart, false);     break;//tanbag   
      case 16: bRestart = rows(bRestart);                           break;//
      case 17: bRestart = graphicSpectrum2(bRestart);               break;//
      case 18: bRestart = graphicFade(bRestart);                    break;//
      case 19: bRestart = graphicScroller(bRestart);                break;// 
      case 20: bRestart = graphicEyes(bRestart);                    break; //
      case 21: bRestart = animateSpinningCross(bRestart, false, 4); break;//tanbag 
      case 22: bRestart = checkboard(bRestart);                     break;//
      case 23: bRestart = stripe(bRestart);                         break;//
      case 24: bRestart = bounce1(bRestart);                        break;//
      case 25: bRestart = bullseye(bRestart);                       break;//
      case 26: bRestart = animateCross(bRestart);                   break;//ganti
      case 27: bRestart = animateTriangle2(bRestart, 2);            break;//
      case 28: bRestart = bounce3(bRestart);                        break;  // 
      case 29: bRestart = animateSpinningCross(bRestart, false, 1); break;//tanbag 
      case 30: bRestart = spiral(bRestart);                         break; //
      case 31: bRestart = animateTriangle2(bRestart, 1);            break;//
      case 32: bRestart = moveTwoOutlineBoxes(bRestart);            break;//
      case 33: bRestart = animateSpinningCross(bRestart, true, 3);  break;//tanbag 
      case 34: bRestart = ShiftAnimation(bRestart);                 break;//gaNti
      case 35: bRestart = stripeBounce(bRestart);                   break;//
      case 36: bRestart = boxAnim(bRestart);                        break;//
      case 37: bRestart = animateSpinningCross(bRestart, true, 1);  break;//tanbag 
      case 38: bRestart = waveBounce2(bRestart);                    break;//
      case 39: bRestart = DoubleRows(bRestart);                     break;  // 
      case 40: bRestart = animateTriangle(bRestart);                break;  // 
      case 41: bRestart = curtainAnim(bRestart);                    break;//
      case 42: bRestart = threeDBallAnimation(bRestart);            break;//ganti
      case 43: bRestart = animateSpinningCross(bRestart, true, 2);  break;//tanbag 
      case 44: bRestart = animate3DCircle(bRestart);                break;//ganti
      case 45: bRestart = animateTriangle2(bRestart, 3);            break; //
      case 46: bRestart = animateSpinningCross(bRestart, false, 3); break;//tanbag 
      default: state = 1; //
    }
  }
  if (slct == 3){
    switch(state){
      case  0: bInMessages = true; 
               bRestart = scrollText(bRestart, msgTab[mesg]);  break;
      case  1: bRestart = graphicMidline2(bRestart);                break;//mid
      case  2: bRestart = graphicRandom(bRestart);                  break;//ran
      case  3: bRestart = animateSpinningCross(bRestart, 2, false); break;//tanbag 
      case  4: bRestart = graphicScanner(bRestart);                 break;//scan
      case  5: bRestart = graphicSpectrum1(bRestart);               break;//
      case  6: bRestart = animateBouncingLine(bRestart, true);      break;//tanbag
      case  7: bRestart = graphicSinewave(bRestart);                break;//
      case  8: bRestart = graphicBounceBall(bRestart);              break;//
      case  9: bRestart = graphicHearts(bRestart);                  break;//
      case 10: bRestart = graphicPacman(bRestart);                  break;//
      case 11: bRestart = animateSpinningCross(bRestart, 4, true);  break;//tanbag 
      case 12: bRestart = graphicHeartbeat(bRestart);               break;//
      case 13: bRestart = graphicWiper(bRestart);                   break;///
      case 14: bRestart = graphicInvader(bRestart);                 break;//
      case 15: bRestart = animateBouncingLine(bRestart, false);     break;//tanbag   
      case 16: bRestart = rows(bRestart);                           break;//
      case 17: bRestart = graphicSpectrum2(bRestart);               break;//
      case 18: bRestart = graphicFade(bRestart);                    break;//
      case 19: bRestart = graphicScroller(bRestart);                break;// 
      case 20: bRestart = graphicEyes(bRestart);                    break; //
      case 21: bRestart = animateSpinningCross(bRestart, 4, false); break;//tanbag 
      case 22: bRestart = checkboard(bRestart);                     break;//
      case 23: bRestart = stripe(bRestart);                         break;//
      case 24: bRestart = bounce1(bRestart);                        break;//
      case 25: bRestart = bullseye(bRestart);                       break;//
      case 26: bRestart = animateCross(bRestart);                   break;//ganti
      case 27: bRestart = animateTriangle2(bRestart, 2);            break;//
      case 28: bRestart = bounce3(bRestart);                        break;  // 
      case 29: bRestart = animateSpinningCross(bRestart, 1, false); break;//tanbag 
      case 30: bRestart = spiral(bRestart);                         break; //
      case 31: bRestart = animateTriangle2(bRestart, 1);            break;//
      case 32: bRestart = moveTwoOutlineBoxes(bRestart);            break;//
      case 33: bRestart = animateSpinningCross(bRestart, 3, true);  break;//tanbag 
      case 34: bRestart = ShiftAnimation(bRestart);                 break;//gaNti
      case 35: bRestart = stripeBounce(bRestart);                   break;//
      case 36: bRestart = boxAnim(bRestart);                        break;//
      case 37: bRestart = animateSpinningCross(bRestart, 1, true);  break;//tanbag 
      case 38: bRestart = waveBounce2(bRestart);                    break;//
      case 39: bRestart = DoubleRows(bRestart);                     break;  // 
      case 40: bRestart = animateTriangle(bRestart);                break;  // 
      case 41: bRestart = curtainAnim(bRestart);                    break;//
      case 42: bRestart = threeDBallAnimation(bRestart);            break;//ganti
      case 43: bRestart = animateSpinningCross(bRestart, 2, true);  break;//tanbag 
      case 44: bRestart = animate3DCircle(bRestart);                break;//ganti
      case 45: bRestart = animateTriangle2(bRestart, 3);            break; //
      case 46: bRestart = animateSpinningCross(bRestart, 3, false); break;//tanbag 
      default: state = 0;
    }
  }
//      (!manualMode[0]) ? (state = 1) : ;   resetMatrix(); break;
  if (slct == 4){
    switch(state){
      case  0: if (!manualMode[state]){ state++; }
               else { bInMessages = true; bRestart = scrollText(bRestart, msgTab[mesg]); }                 break;

      case  1: (!manualMode[state]) ? (state++) :    bRestart = graphicMidline2(bRestart);                 break;
      case  2: (!manualMode[state]) ? (state++) :    bRestart = graphicRandom(bRestart);                   break;//ran
      case  3: (!manualMode[state]) ? (state++) :     bRestart = animateSpinningCross(bRestart, false, 2); break;//tanbag 
      case  4: (!manualMode[state]) ? (state++) :     bRestart = graphicScanner(bRestart);                 break;//scan
      case  5: (!manualMode[state]) ? (state++) :     bRestart = graphicSpectrum1(bRestart);               break;//
      case  6: (!manualMode[state]) ? (state++) :     bRestart = animateBouncingLine(bRestart, true);      break;//tanbag
      case  7: (!manualMode[state]) ? (state++) :     bRestart = graphicSinewave(bRestart);                break;//
      case  8: (!manualMode[state]) ? (state++) :     bRestart = graphicBounceBall(bRestart);              break;//
      case  9: (!manualMode[state]) ? (state++) :     bRestart = graphicHearts(bRestart);                  break;//
      case 10: (!manualMode[state]) ? (state++) :     bRestart = graphicPacman(bRestart);                  break;//
      case 11: (!manualMode[state]) ? (state++) :     bRestart = animateSpinningCross(bRestart, true, 4);  break;//tanbag 
      case 12: (!manualMode[state]) ? (state++) :     bRestart = graphicHeartbeat(bRestart);               break;//
      case 13: (!manualMode[state]) ? (state++) :     bRestart = graphicWiper(bRestart);                   break;///
      case 14: (!manualMode[state]) ? (state++) :     bRestart = graphicInvader(bRestart);                 break;//
      case 15: (!manualMode[state]) ? (state++) :     bRestart = animateBouncingLine(bRestart, false);     break;//tanbag   
      case 16: (!manualMode[state]) ? (state++) :     bRestart = rows(bRestart);                           break;//
      case 17: (!manualMode[state]) ? (state++) :     bRestart = graphicSpectrum2(bRestart);               break;//
      case 18: (!manualMode[state]) ? (state++) :     bRestart = graphicFade(bRestart);                    break;//
      case 19: (!manualMode[state]) ? (state++) :     bRestart = graphicScroller(bRestart);                break;// 
      case 20: (!manualMode[state]) ? (state++) :     bRestart = graphicEyes(bRestart);                    break; //
      case 21: (!manualMode[state]) ? (state++) :     bRestart = animateSpinningCross(bRestart, false, 4); break;//tanbag 
      case 22: (!manualMode[state]) ? (state++) :     bRestart = checkboard(bRestart);                     break;//
      case 23: (!manualMode[state]) ? (state++) :     bRestart = stripe(bRestart);                         break;//
      case 24: (!manualMode[state]) ? (state++) :     bRestart = bounce1(bRestart);                        break;//
      case 25: (!manualMode[state]) ? (state++) :     bRestart = bullseye(bRestart);                       break;//
      case 26: (!manualMode[state]) ? (state++) :     bRestart = animateCross(bRestart);                   break;//ganti
      case 27: (!manualMode[state]) ? (state++) :     bRestart = animateTriangle2(bRestart, 2);            break;//
      case 28: (!manualMode[state]) ? (state++) :     bRestart = bounce3(bRestart);                        break;  // 
      case 29: (!manualMode[state]) ? (state++) :     bRestart = animateSpinningCross(bRestart, false, 1); break;//tanbag 
      case 30: (!manualMode[state]) ? (state++) :     bRestart = spiral(bRestart);                         break; //
      case 31: (!manualMode[state]) ? (state++) :     bRestart = animateTriangle2(bRestart, 1);            break;//
      case 32: (!manualMode[state]) ? (state++) :     bRestart = moveTwoOutlineBoxes(bRestart);            break;//
      case 33: (!manualMode[state]) ? (state++) :     bRestart = animateSpinningCross(bRestart, true, 3);  break;//tanbag 
      case 34: (!manualMode[state]) ? (state++) :     bRestart = ShiftAnimation(bRestart);                 break;//gaNti
      case 35: (!manualMode[state]) ? (state++) :     bRestart = stripeBounce(bRestart);                   break;//
      case 36: (!manualMode[state]) ? (state++) :     bRestart = boxAnim(bRestart);                        break;//
      case 37: (!manualMode[state]) ? (state++) :     bRestart = animateSpinningCross(bRestart, true, 1);  break;//tanbag 
      case 38: (!manualMode[state]) ? (state++) :     bRestart = waveBounce2(bRestart);                    break;//
      case 39: (!manualMode[state]) ? (state++) :     bRestart = DoubleRows(bRestart);                     break;  // 
      case 40: (!manualMode[state]) ? (state++) :     bRestart = animateSpinningCross(bRestart, false, 3); break;  // 
      case 41: (!manualMode[state]) ? (state++) :     bRestart = curtainAnim(bRestart);                    break;//
      case 42: (!manualMode[state]) ? (state++) :     bRestart = threeDBallAnimation(bRestart);            break;//ganti
      case 43: (!manualMode[state]) ? (state++) :     bRestart = animateSpinningCross(bRestart, true, 2);  break;//tanbag 
      case 44: (!manualMode[state]) ? (state++) :     bRestart = animate3DCircle(bRestart);                break;//ganti
      case 45: (!manualMode[state]) ? (state++) :     bRestart = animateTriangle2(bRestart, 3);            break; //
      default: state = 0;
    }
  }
}

// ========================================== WEB Interface ==================================
void handleRoot() {
  String T1=inputTEXT1.substring(0, 13);
  String T2=inputTEXT2.substring(0, 13);
  uint8_t mod=slct;
  uint8_t cepat=kecepatan;
  uint8_t bright=kecerahan;
  uint8_t waktuAnim=DEMO_DELAY;
  uint8_t waktuSein=seinDelay;
  uint8_t waktuStop=stopDelay;

  String m1 = (slct == 1) ? "checked" : "";
  String m2 = (slct == 2) ? "checked" : "";
  String m3 = (slct == 3) ? "checked" : "";
  String m4 = (slct == 4) ? "checked" : "";

  
  String r1 = (slctSein == 1) ? "checked" : "";
  String r2 = (slctSein == 2) ? "checked" : "";
  String r3 = (slctSein == 3) ? "checked" : "";
  
  String s1 = (slctStop == 1) ? "checked" : "";
  String s2 = (slctStop == 2) ? "checked" : "";
  String s3 = (slctStop == 3) ? "checked" : "";

  String html="<!DOCTYPE html>";
  html=html+"<html lang='en'>";
  html=html+"<head>";
  html=html+"<meta charset='UTF-8'>";
  html=html+"<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  html=html+"<title>STOPLAMP SETTING PAGE</title>";
  html=html+"<style>";
  html=html+"body {";
  html=html+"    font-family: Arial, sans-serif;";
  html=html+"    background-color: lightslategray;";
  html=html+"    display: flex;";
  html=html+"    justify-content: center;";
  html=html+"    align-items: center;";
  html=html+"    height: 170vh;";
  html=html+"    margin: 0;";
  html=html+"}";
  html=html+".container {";
  html=html+"    background-color: gray;";
  html=html+"    padding: 20px;";
  html=html+"    border-radius: 10px;";
  html=html+"    box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);";
  html=html+"    max-width: 600px;";
  html=html+"    width: 900%;";
  html=html+"}";
  html=html+"h1, h2 {";
  html=html+"    color: #333;";
  html=html+"    text-align: center;";
  html=html+"}";
  html=html+"table {";
  html=html+"    width: 100%;";
  html=html+"    border-collapse: collapse;";
  html=html+"    margin-top: 20px;";
  html=html+"}";
  html=html+"table, th, td {";
  html=html+"    border: 1px solid #ccc;";
  html=html+"}";
  html=html+"th, td {";
  html=html+"    padding: 10px;";
  html=html+"    text-align: center;";
  html=html+"}";
  html=html+"input[type='text'] {";
  html=html+"    width: 100%;";
  html=html+"    padding: 8px;";
  html=html+"    margin-bottom: 10px;";
  html=html+"    border: 1px solid #ccc;";
  html=html+"    border-radius: 4px;";
  html=html+"    box-sizing: border-box;";
  html=html+"}";
  html=html+"input[type='radio'] {";
  html=html+"    margin-right: 5px;";
  html=html+"}";
  html=html+"input[type='submit'] {";
  html=html+"    background-color: #4CAF50;";
  html=html+"    color: #fff;";
  html=html+"    padding: 10px 20px;";
  html=html+"    border: none;";
  html=html+"    border-radius: 4px;";
  html=html+"    cursor: pointer;";
  html=html+"    font-size: 16px;";
  html=html+"    width: 100%;";
  html=html+"}";
  html=html+"input[type='submit']:hover {";
  html=html+"    background-color: #45a049;";
  html=html+"}";
  html=html+"h5 a {";
  html=html+"    color: #007BFF;";
  html=html+"    text-decoration: none;";
  html=html+"    display: block;";
  html=html+"    text-align: center;";
  html=html+"}";
  html=html+"</style>";
  html=html+"</head>";
  html=html+"<body>";
  html=html+"<div class='container'>";    
  html=html+"    <h1>SETTING MENU</h1>"; 
  html=html+"    <h2>STOPLAMP RUNNING TEXT VARIO</h3>"; 
  html=html+"    <form action='/overwriteSettings' method='get'>"; 
  html=html+"        <table>";
  html=html+"                <td colspan='2'>"; 
  html=html+"                    <label>Pilih Mode :</label>"; 
  html=html+"                    <br><br>"; 
  html=html+"                    <label><input type='radio' id='slc1' name='selection' value='1' "+m1+"> Running Teks </label>"; 
  html=html+"                    <label><input type='radio' id='slc2' name='selection' value='2' "+m2+"> Animasi </label>"; 
  html=html+"                    <label><input type='radio' id='slc3' name='selection' value='3' "+m3+"> Kombinasi </label>"; 
  html=html+"                    <label><input type='radio' id='slc4' name='selection' value='4' "+m4+"> Manual </label>"; 
  html=html+"                </td>"; 
  html=html+"            <tr>"; 
  html=html+"                <td style='width:25%' ><b>Teks 1</b></td>"; 
  html=html+"                <td style='width:75%' ><input type='text' name='text1' value='"+T1+"' maxlength='50'></td>"; 
  html=html+"            </tr>"; 
  html=html+"            <tr>"; 
  html=html+"                <td style='width:25%' ><b>Teks 2</b></td>"; 
  html=html+"                <td style='width:75%' ><input type='text' name='text2' value='"+T2+"' maxlength='50'></td>"; 
  html=html+"            </tr>"; 
  html=html+"            <tr>"; 
  html=html+"                <td colspan='2'>"; 
  html=html+"                    <label>Kecepatan Teks Sekarang : "+cepat+"mS</label>"; 
  html=html+"                    <br><br>"; 
  html=html+"                    <input type='range' style='width:500px' id='RangeCepat' name='kecepatan' value='"+cepat+"' min='10' max='100' oninput='this.nextElementSibling.value = this.value'>"; 
  html=html+"                    <output>"+cepat+"</output>mS";
  html=html+"                </td>"; 
  html=html+"            </tr>"; 
  html=html+"        </table>";
  html=html+"        <table>";
  html=html+"            <tr><td colspan='5'><label>Animasi (Pilih Mode Manual): </label></td></tr>"; 
  html=html+"            <tr>"; 
  html=html+"                <td style='width:20%'>"; 
  html=html+"                   <label><input type='checkbox' id='man1' name='man1' value='1'> 1</label>";
  html=html+"                   <br>";  
  html=html+"                   <label><input type='checkbox' id='man2' name='man2' value='1'> 2</label>"; 
  html=html+"                   <br>";  
  html=html+"                   <label><input type='checkbox' id='man3' name='man3' value='1'> 3</label>"; 
  html=html+"                   <br>";  
  html=html+"                   <label><input type='checkbox' id='man4' name='man4' value='1'> 4</label>"; 
  html=html+"                   <br>";  
  html=html+"                   <label><input type='checkbox' id='man5' name='man5' value='1'> 5</label>"; 
  html=html+"                   <br>";  
  html=html+"                   <label><input type='checkbox' id='man6' name='man6' value='1'> 6</label>"; 
  html=html+"                   <br>";  
  html=html+"                   <label><input type='checkbox' id='man7' name='man7' value='1'> 7</label>"; 
  html=html+"                   <br>";  
  html=html+"                   <label><input type='checkbox' id='man8' name='man8' value='1'> 8</label>"; 
  html=html+"                   <br>";  
  html=html+"                   <label><input type='checkbox' id='man9' name='man9' value='1'> 9</label>";  
  html=html+"                   <br>";  
  html=html+"                   <label><input type='checkbox' id='man10' name='man10' value='1'> 10</label>"; 
  html=html+"                </td>"; 
  html=html+"                <td style='width:20%'>"; 
  html=html+"                   <label><input type='checkbox' id='man11' name='man11' value='1'> 11</label>";
  html=html+"                   <br>";  
  html=html+"                   <label><input type='checkbox' id='man12' name='man12' value='1'> 12</label>"; 
  html=html+"                   <br>";  
  html=html+"                   <label><input type='checkbox' id='man13' name='man13' value='1'> 13</label>"; 
  html=html+"                   <br>";  
  html=html+"                   <label><input type='checkbox' id='man14' name='man14' value='1'> 14</label>"; 
  html=html+"                   <br>";  
  html=html+"                   <label><input type='checkbox' id='man15' name='man15' value='1'> 15</label>"; 
  html=html+"                   <br>";  
  html=html+"                   <label><input type='checkbox' id='man16' name='man16' value='1'> 16</label>"; 
  html=html+"                   <br>";  
  html=html+"                   <label><input type='checkbox' id='man17' name='man17' value='1'> 17</label>"; 
  html=html+"                   <br>";  
  html=html+"                   <label><input type='checkbox' id='man18' name='man18' value='1'> 18</label>"; 
  html=html+"                   <br>";   
  html=html+"                   <label><input type='checkbox' id='man19' name='man19' value='1'> 19</label>"; 
  html=html+"                   <br>";  
  html=html+"                   <label><input type='checkbox' id='man20' name='man20' value='1'> 20</label>"; 
  html=html+"                </td>"; 
  html=html+"                <td style='width:20%'>"; 
  html=html+"                   <label><input type='checkbox' id='man21' name='man21' value='1'> 21</label>";
  html=html+"                   <br>";  
  html=html+"                   <label><input type='checkbox' id='man22' name='man22' value='1'> 22</label>"; 
  html=html+"                   <br>";  
  html=html+"                   <label><input type='checkbox' id='man23' name='man23' value='1'> 23</label>"; 
  html=html+"                   <br>";  
  html=html+"                   <label><input type='checkbox' id='man24' name='man24' value='1'> 24</label>"; 
  html=html+"                   <br>";  
  html=html+"                   <label><input type='checkbox' id='man25' name='man25' value='1'> 25</label>"; 
  html=html+"                   <br>";  
  html=html+"                   <label><input type='checkbox' id='man26' name='man26' value='1'> 26</label>"; 
  html=html+"                   <br>";  
  html=html+"                   <label><input type='checkbox' id='man27' name='man27' value='1'> 27</label>";  
  html=html+"                   <br>";  
  html=html+"                   <label><input type='checkbox' id='man28' name='man28' value='1'> 28</label>"; 
  html=html+"                   <br>";   
  html=html+"                   <label><input type='checkbox' id='man29' name='man29' value='1'> 29</label>"; 
  html=html+"                   <br>";  
  html=html+"                   <label><input type='checkbox' id='man30' name='man30' value='1'> 30</label>"; 
  html=html+"                </td>"; 
  html=html+"                <td style='width:20%'>"; 
  html=html+"                   <label><input type='checkbox' id='man31' name='man31' value='1'> 31</label>";
  html=html+"                   <br>";  
  html=html+"                   <label><input type='checkbox' id='man33' name='man33' value='1'> 32</label>"; 
  html=html+"                   <br>";  
  html=html+"                   <label><input type='checkbox' id='man33' name='man33' value='1'> 33</label>"; 
  html=html+"                   <br>";  
  html=html+"                   <label><input type='checkbox' id='man34' name='man34' value='1'> 34</label>"; 
  html=html+"                   <br>";  
  html=html+"                   <label><input type='checkbox' id='man35' name='man35' value='1'> 35</label>"; 
  html=html+"                   <br>";  
  html=html+"                   <label><input type='checkbox' id='man36' name='man36' value='1'> 36</label>"; 
  html=html+"                   <br>";  
  html=html+"                   <label><input type='checkbox' id='man37' name='man37' value='1'> 37</label>"; 
  html=html+"                   <br>";  
  html=html+"                   <label><input type='checkbox' id='man38' name='man38' value='1'> 38</label>"; 
  html=html+"                   <br>";   
  html=html+"                   <label><input type='checkbox' id='man39' name='man39' value='1'> 39</label>"; 
  html=html+"                   <br>";    
  html=html+"                   <label><input type='checkbox' id='man40' name='man40' value='1'> 40</label>";
  html=html+"                </td>";
  html=html+"            </tr>";
  html=html+"        <table>"; 
  html=html+"            <tr><td colspan='2'>Atur Variabel Panel :</td></tr>"; 
  html=html+"            <td colspan='2'>"; 
  html=html+"                <label>Kecerahan Sekarang : "+bright+"</label>"; 
  html=html+"                <br><br>"; 
  html=html+"                <input type='range' style='width: 500px' id='RangeCerah' name='Kecerahan' value='"+bright+"' min='1' max='15' oninput='this.nextElementSibling.value = this.value'>";
  html=html+"                <output>"+bright+"</output>"; 
  html=html+"                <br><br>"; 
  html=html+"                <label>Lama Tiap Animasi Sekarang : "+waktuAnim+"S</label>"; 
  html=html+"                <br><br>"; 
  html=html+"                <input type='range' style='width: 500px' id='rangeEfek' name='Efek' value='"+waktuAnim+"' min='1' max='20' oninput='this.nextElementSibling.value = this.value'>";
  html=html+"                <output>"+waktuAnim+"</output>S"; 
  html=html+"            </td>"; 
  html=html+"        </table>";
  html=html+"        <table>";
  html=html+"            <tr><td colspan='2'>Atur Mode Sein-Stop :</td></tr>";
  html=html+"            <tr>";
  html=html+"                <td colspan='2'>";
  html=html+"                    <br>";
  html=html+"                    <label>Kecepatan Sein Sekarang : "+waktuSein+"mS</label>"; 
  html=html+"                    <br><br>"; 
  html=html+"                    <input type='range' style='width: 500px' id='rangeSein' name='Sein' value='"+waktuSein+"' min='2' max='50' oninput='this.nextElementSibling.value = this.value'>";
  html=html+"                    <output>"+waktuSein+"</output>mS"; 
  html=html+"                    <label>Mode Sein :   </label>";
  html=html+"                    <label><input type='radio' id='slc1' name='slctSein' value='1' "+r1+"> 1</label>";
  html=html+"                    <label><input type='radio' id='slc2' name='slctSein' value='2' "+r2+"> 2</label>";
  html=html+"                    <label><input type='radio' id='slc3' name='slctSein' value='3' "+r3+"> 3</label>";
  html=html+"                    <br><br><br>";
  html=html+"                    <label>Kecepatan Stop Sekarang : "+waktuStop+"mS</label>"; 
  html=html+"                    <br><br>"; 
  html=html+"                    <input type='range' style='width: 500px' id='rangeStop' name='Stop' value='"+waktuStop+"' min='2' max='50' oninput='this.nextElementSibling.value = this.value'>";
  html=html+"                    <output>"+waktuStop+"</output>mS"; 
  html=html+"                    <br><br>";
  html=html+"                    <label>Mode Stop :   </label>";
  html=html+"                    <label><input type='radio' id='slc1' name='slctStop' value='1' "+s1+"> 1</label>";
  html=html+"                    <label><input type='radio' id='slc2' name='slctStop' value='2' "+s2+"> 2</label>";
  html=html+"                    <label><input type='radio' id='slc3' name='slctStop' value='3' "+s3+"> 3</label>";
  html=html+"                </td>";
  html=html+"           </tr>";
  html=html+"            <tr>";
  html=html+"                <td>";
  html=html+"                   <input type='submit' name='Save' value='Submit'>";
  html=html+"                   <h5><a href='http://192.168.4.1/update'>© 2023 vario Stoplamp</a></h5>";
  html=html+"                   <h5>";
  html=html+"                     <a href='https://www.youtube.com/@DBOSSProject'>@DBOSSProject</a> x <a href='https://www.instagram.com/Hab_mz'>@Hab_mz</a>";
  html=html+"                   </h5>";
  html=html+"                </td>";
  html=html+"            </tr>";
  html=html+"        </table>";
  html=html+"    </form>";
  html=html+"</div>";
  html=html+"</body>";
  html=html+"</html>";
  server.send(200,"html",html);
}

void overwriteSettings(){
  //============= MAIN VAR =============
  String text1 = server.arg("text1");
  write_EEPROM(101, 200, text1);
  
  String text2 = server.arg("text2");
  write_EEPROM(201, 300, text2);
  
  String selection = server.arg("selection");
  write_EEPROM(301, 302, selection);  
  

  //============ GLOBAL VAR =============
  String spd = server.arg("kecepatan");
  write_EEPROM(303, 305, spd);
  
  String brig = server.arg("Kecerahan");
  write_EEPROM(306, 308, brig);
  
  String anim = server.arg("Efek");
  write_EEPROM(309, 311, anim);
  
  String Sein = server.arg("Sein");
  write_EEPROM(459, 461, Sein);
  
  String Stop = server.arg("Stop");
  write_EEPROM(462, 464, Stop);
  
  String selSein = server.arg("slctSein");
  write_EEPROM(455, 456, selSein);  
  String selSetop = server.arg("slctStop");
  write_EEPROM(457, 458, selSetop);  
  
  static String mod;
  if(selection == "1"){
    mod = "Hanya Teks";
  }else if(selection == "2"){
    mod = "Hanya Animasi";
  }else if(selection == "3"){
    mod = "Teks dan Animasi";
  }else{
    mod = "Mode Manual";
  }
  
  String html="<!DOCTYPE html>";
  html=html+"<html lang='en'>";
  html=html+"<head>";
  html=html+"<meta charset='UTF-8'>";
  html=html+"<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  html=html+"<title>Setting Berhasil!</title>";
  html=html+"<style>";
  html=html+"body {";
  html=html+"    font-family: Arial, sans-serif;";
  html=html+"    text-align: center;";
  html=html+"    background-color: #f4f4f4;";
  html=html+"    display: flex;";
  html=html+"    justify-content: center;";
  html=html+"    align-items: center;";
  html=html+"    height: 100vh;";
  html=html+"    margin: 0;";
  html=html+"}";
  html=html+".container {";
  html=html+"    background-color: #fff;";
  html=html+"    padding: 20px;";
  html=html+"    border-radius: 10px;";
  html=html+"    box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);";
  html=html+"    max-width: 600px;";
  html=html+"    width: 100%;";
  html=html+"}";
  html=html+"h1, h2 {";
  html=html+"    color: #333;";
  html=html+"}";
  html=html+"</style>";
  html=html+"</head>";
  html=html+"<body>";
  html=html+"<div class='container'>";
  html=html+"    <h1>Done gak? Done bang</h1>";
  html=html+"    <h2>Teks 1 : "+text1+"</h2>";
  html=html+"    <h2>Teks 2 : "+text2+"</h2>";
  html=html+"    <h2>Mode Tampilan : "+mod+"</h2>";
  html=html+"    <h4>Lama Tiap Efek : "+anim+" S</h2>";
  html=html+"    <h4>Kecerahan Panel : "+brig+"</h2>";
  html=html+"    <h4>Kecepatan Teks : "+spd+" mS</h2>";
  html=html+"    <h4>Kecepatan Sein : "+Sein+" mS</h2>";
  html=html+"    <h4>Kecepatan Rem : "+Stop+" mS</h2>";
  html=html+"    <h3><a href='http://192.168.4.1'>Balik Pencet Sini Bos</a></h3>";
  html=html+"</div>";
  html=html+"</body>";
  html=html+"</html>";
  server.send(200, "text/html", html);  

  //============ MANUAL =============
  String MAN1 =  (server.arg("man1") == "1") ? "1" : "0";   write_EEPROM(312, 313, MAN1);
  String MAN2 =  (server.arg("man2") == "1") ? "1" : "0";   write_EEPROM(314, 315, MAN2);
  String MAN3 =  (server.arg("man3") == "1") ? "1" : "0";   write_EEPROM(316, 317, MAN3);
  String MAN4 =  (server.arg("man4") == "1") ? "1" : "0";   write_EEPROM(318, 319, MAN4); 
  String MAN5 =  (server.arg("man5") == "1") ? "1" : "0";   write_EEPROM(320, 321, MAN5);
  String MAN6 =  (server.arg("man6") == "1") ? "1" : "0";   write_EEPROM(322, 323, MAN6);
  String MAN7 =  (server.arg("man7") == "1") ? "1" : "0";   write_EEPROM(324, 325, MAN7);
  String MAN8 =  (server.arg("man8") == "1") ? "1" : "0";   write_EEPROM(326, 327, MAN8);
  String MAN9 =  (server.arg("man9") == "1") ? "1" : "0";   write_EEPROM(328, 329, MAN9); 
  String MAN10 = (server.arg("man10") == "1") ? "1" : "0";  write_EEPROM(330, 331, MAN10);
  String MAN11 = (server.arg("man11") == "1") ? "1" : "0";  write_EEPROM(332, 333, MAN11);
  String MAN12 = (server.arg("man12") == "1") ? "1" : "0";  write_EEPROM(334, 335, MAN12);
  String MAN13 = (server.arg("man13") == "1") ? "1" : "0";  write_EEPROM(336, 337, MAN13);
  String MAN14 = (server.arg("man14") == "1") ? "1" : "0";  write_EEPROM(338, 339, MAN14); 
  String MAN15 = (server.arg("man15") == "1") ? "1" : "0";  write_EEPROM(340, 341, MAN15);
  String MAN16 = (server.arg("man16") == "1") ? "1" : "0";  write_EEPROM(342, 343, MAN16);
  String MAN17 = (server.arg("man17") == "1") ? "1" : "0";  write_EEPROM(344, 345, MAN17);
  String MAN18 = (server.arg("man18") == "1") ? "1" : "0";  write_EEPROM(346, 347, MAN18);
  String MAN19 = (server.arg("man19") == "1") ? "1" : "0";  write_EEPROM(348, 349, MAN19); 
  String MAN20 = (server.arg("man20") == "1") ? "1" : "0";  write_EEPROM(350, 351, MAN20);
  String MAN21 = (server.arg("man21") == "1") ? "1" : "0";  write_EEPROM(352, 353, MAN21);
  String MAN22 = (server.arg("man22") == "1") ? "1" : "0";  write_EEPROM(354, 355, MAN22);
  String MAN23 = (server.arg("man23") == "1") ? "1" : "0";  write_EEPROM(356, 357, MAN23);
  String MAN24 = (server.arg("man24") == "1") ? "1" : "0";  write_EEPROM(358, 359, MAN24); 
  String MAN25 = (server.arg("man25") == "1") ? "1" : "0";  write_EEPROM(360, 361, MAN25);
  String MAN26 = (server.arg("man26") == "1") ? "1" : "0";  write_EEPROM(362, 363, MAN26);
  String MAN27 = (server.arg("man27") == "1") ? "1" : "0";  write_EEPROM(364, 365, MAN27);
  String MAN28 = (server.arg("man28") == "1") ? "1" : "0";  write_EEPROM(366, 367, MAN28);
  String MAN29 = (server.arg("man29") == "1") ? "1" : "0";  write_EEPROM(368, 369, MAN29); 
  String MAN30 = (server.arg("man30") == "1") ? "1" : "0";  write_EEPROM(370, 371, MAN30);
  String MAN31 = (server.arg("man31") == "1") ? "1" : "0";  write_EEPROM(372, 373, MAN31);
  String MAN32 = (server.arg("man32") == "1") ? "1" : "0";  write_EEPROM(374, 375, MAN32);
  String MAN33 = (server.arg("man33") == "1") ? "1" : "0";  write_EEPROM(376, 377, MAN33);
  String MAN34 = (server.arg("man34") == "1") ? "1" : "0";  write_EEPROM(378, 379, MAN34); 
  String MAN35 = (server.arg("man35") == "1") ? "1" : "0";  write_EEPROM(380, 381, MAN35); 
  String MAN36 = (server.arg("man36") == "1") ? "1" : "0";  write_EEPROM(382, 383, MAN36); 
  String MAN37 = (server.arg("man37") == "1") ? "1" : "0";  write_EEPROM(384, 385, MAN27);
  String MAN38 = (server.arg("man38") == "1") ? "1" : "0";  write_EEPROM(386, 387, MAN28);
  String MAN39 = (server.arg("man39") == "1") ? "1" : "0";  write_EEPROM(388, 389, MAN29); 
  String MAN40 = (server.arg("man40") == "1") ? "1" : "0";  write_EEPROM(390, 391, MAN30);
  String MAN41 = (server.arg("man41") == "1") ? "1" : "0";  write_EEPROM(392, 393, MAN31);
  String MAN42 = (server.arg("man42") == "1") ? "1" : "0";  write_EEPROM(394, 395, MAN32);
  String MAN43 = (server.arg("man43") == "1") ? "1" : "0";  write_EEPROM(396, 397, MAN33);
  String MAN44 = (server.arg("man44") == "1") ? "1" : "0";  write_EEPROM(398, 399, MAN34); 
  String MAN45 = (server.arg("man45") == "1") ? "1" : "0";  write_EEPROM(400, 401, MAN35);   
  reload_EEPROM();
//  bInMessages = true;
}

// ============================================= EEPROM ======================================
void write_EEPROM(int pos1, int pos2,String strText){
  int pj_strText=strText.length()+1;
  char stringIn[pj_strText];
  strText.toCharArray(stringIn,pj_strText);

  int j=-1;
  for(int i=pos1; i<pos2+1; i++){
    j++;
    if (i<pos1+pj_strText )  {
      EEPROM.write(i, stringIn[j]);
      EEPROM.commit();
    }else{
      EEPROM.write(i, '\0');
      EEPROM.commit();
    }
  }
}

String read_EEPROM(int pos1,int pos2){ 
  int i;
  char c;
  String temp="";
  for (i=pos1; i<pos2; i++){
    c=EEPROM.read(i);
    temp=temp+String(c);
  }
  temp=temp+'\0';
  return temp;
}

void reload_EEPROM(){
  //============= MAIN VAR =============
  inputTEXT1  = read_EEPROM(101,200);
  inputTEXT1  = inputTEXT1.substring(0, inputTEXT1.length());

  inputTEXT2  = read_EEPROM(201,300);
  inputTEXT2  = inputTEXT2.substring(0,inputTEXT2.length());

  String temp = read_EEPROM(301,302);
  temp = temp.substring(0,temp.length());
  slct = temp.toInt();
  
  //============ GLOBAL VAR =============
  String spd2 = read_EEPROM(303, 305);
  spd2 = spd2.substring(0,spd2.length());
  kecepatan = spd2.toInt();
  
  String brig2 = read_EEPROM(306, 308);
  brig2 = brig2.substring(0,brig2.length());
  kecerahan = brig2.toInt();
  
  String anim2 = read_EEPROM(309, 311);
  anim2 = anim2.substring(0,anim2.length());
  DEMO_DELAY = anim2.toInt();
  timeDemo = DEMO_DELAY;
  
  String Sein2 = read_EEPROM(459, 461);
  Sein2 = Sein2.substring(0,Sein2.length());
  seinDelay = Sein2.toInt();
  
  String Stop2 = read_EEPROM(462, 464);
  Stop2 = Stop2.substring(0,Stop2.length());
  stopDelay = Stop2.toInt();

  String tempSein = read_EEPROM(455,456);
  tempSein = tempSein.substring(0,tempSein.length());
  slctSein = tempSein.toInt();
  
  String tempStop = read_EEPROM(457,458);
  tempStop = tempStop.substring(0,tempStop.length());
  slctStop = tempStop.toInt();
  
  //============ MANUAL =============
  int startVal = 312;
  int endVal = 313;

  for (uint8_t i = 0; i < modCount; i++){
    String manMod = read_EEPROM(startVal, endVal);
    manMod = manMod.substring(0,temp.length());
    manualMode[i] = (manMod.toInt() != 0);

    startVal = startVal + 2;
    endVal = endVal + 2;
  }
}

void Stop_blink(byte sMod){                   //==38,39, 40==
  myDisplay.setTextAlignment(PA_CENTER);
  switch (sMod){
    case 1:
      myDisplay.setFont(bmz6x8);
      myDisplay.print("STOP!");
        analogWrite(led, kecLed);
      delay(stopDelay*6);
      myDisplay.print("         "); 
        analogWrite(led, 0);
      delay(stopDelay*6);
      break;
    case 2:
      myDisplay.setFont(bmz6x8);
      myDisplay.print("<<>>");
        analogWrite(led, kecLed);
      delay(stopDelay*6);
      myDisplay.print("         "); 
        analogWrite(led, 0);
      delay(stopDelay*6);
      break;
    case 3:
      myDisplay.setFont(bmz6x8);
      myDisplay.print("[[]]");
        analogWrite(led, kecLed);
      delay(stopDelay*6);
      myDisplay.print("         "); 
        analogWrite(led, 0);
      delay(stopDelay*6);
      break;
  }
}

void panah_kiri(byte sMod){                   //==41, 42, 43==                 
  myDisplay.setIntensity(kecerahan);
  myDisplay.setFont(bmz6x8);

  switch (sMod){
    case 1:
      myDisplay.setTextAlignment(PA_RIGHT);
      myDisplay.print("[");
        analogWrite(led, kecLed);
      delay(seinDelay* 5);
      myDisplay.print("[["); 
        analogWrite(led, 0);
      delay(seinDelay* 5);
      myDisplay.print("[[[");
        analogWrite(led, 0);
      delay(seinDelay* 5);
      myDisplay.print("[[[["); 
        analogWrite(led, kecLed);
      delay(seinDelay* 5);
      break;
    case 2:
      myDisplay.setTextAlignment(PA_RIGHT);
      myDisplay.print("<");
        analogWrite(led, kecLed);
      delay(seinDelay* 5);
      myDisplay.print("<<<"); 
        analogWrite(led, 0);
      delay(seinDelay* 5);
      myDisplay.print("<<<<");
        analogWrite(led, 0);
      delay(seinDelay* 5);
      myDisplay.print("<<<<<"); 
        analogWrite(led, kecLed);
      delay(seinDelay* 5);
      break;
    case 3:
        myDisplay.setTextAlignment(PA_CENTER);
        myDisplay.setPause(20);
        myDisplay.setSpeed(seinDelay);
        myDisplay.setFont(bmz6x8);
        
        if (myDisplay.displayAnimate()) {
              ab=2; 
              myDisplay.setFont(bmz6x8);
              myDisplay.displayText("[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[", myDisplay.getTextAlignment(), myDisplay.getSpeed(), myDisplay.getPause(), texteffect[ab], texteffect[ab]);
              myDisplay.displayReset();
             }
      break;
  }
}

void panah_kanan(byte sMod){                   
  myDisplay.setIntensity(kecerahan);
  myDisplay.setFont(bmz6x8);
  
  switch (sMod){
    case 1:
      myDisplay.setTextAlignment(PA_LEFT);
      myDisplay.print("]");
        analogWrite(led, kecLed);
      delay(seinDelay* 5);
      myDisplay.print("]]"); 
        analogWrite(led, 0);
      delay(seinDelay* 5);
      myDisplay.print("]]]");
        analogWrite(led, 0);
      delay(seinDelay* 5);
      myDisplay.print("]]]]"); 
        analogWrite(led, kecLed);
      delay(seinDelay* 5);
      break;
    case 2:
      myDisplay.setTextAlignment(PA_LEFT);
      myDisplay.print(">");
        analogWrite(led, kecLed);
      delay(seinDelay* 5);
      myDisplay.print(">>>"); 
        analogWrite(led, 0);
      delay(seinDelay* 5);
      myDisplay.print(">>>>");
        analogWrite(led, 0);
      delay(seinDelay* 5);
      myDisplay.print(">>>>>"); 
        analogWrite(led, kecLed);
      delay(seinDelay* 5);
      break;
    case 3:
        myDisplay.setTextAlignment(PA_CENTER);
        myDisplay.setPause(20);
        myDisplay.setSpeed(seinDelay);
        if (myDisplay.displayAnimate()) {
              ab=21; 
              myDisplay.setFont(bmz6x8);
              myDisplay.displayText("]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]", myDisplay.getTextAlignment(), myDisplay.getSpeed(), myDisplay.getPause(), texteffect[ab], texteffect[ab]);
              myDisplay.displayReset();
        }
      break;
  }
}

void Hati2_blink(byte sMod){//==41, 42, 43==             
  myDisplay.setIntensity(kecerahan);
  myDisplay.setFont(bmz6x8);

  switch (sMod){
    case 1:
      myDisplay.setTextAlignment(PA_CENTER);
      myDisplay.print("[]");
      digitalWrite(led, LOW);
      delay(seinDelay* 5);
      myDisplay.print("[  ]"); 
        analogWrite(led, kecLed);
      delay(seinDelay* 5);
      myDisplay.print("[    ]");
      digitalWrite(led, LOW);
      delay(seinDelay* 5);
      break;
    case 2:
      myDisplay.setTextAlignment(PA_CENTER);
      myDisplay.print("<>");
      digitalWrite(led, LOW);
      delay(seinDelay* 5);
      myDisplay.print("<  >"); 
        analogWrite(led, kecLed);
      delay(seinDelay* 5);
      myDisplay.print("<    >");
      digitalWrite(led, LOW);
      delay(seinDelay* 5);
      break;
    case 3:
      myDisplay.setTextAlignment(PA_CENTER);
      myDisplay.print("[]");
      digitalWrite(led, LOW);
      delay(seinDelay* 5);
      myDisplay.print("[[]]"); 
      digitalWrite(led, LOW); 
      delay(seinDelay* 5);
      myDisplay.print("[[[]]]");
        analogWrite(led, kecLed);
      delay(seinDelay* 5);
      myDisplay.print("       "); 
        analogWrite(led, kecLed);
      delay(seinDelay* 5);
      break;
  }

  
}

// ========================================= Main Program ==================================

void setup(){
  #if DEBUG
    Serial.begin(115200);
  #endif 
  EEPROM.begin(512);

  pinMode(led, OUTPUT);
  
  pinMode(kiri, INPUT_PULLUP);
  pinMode(kanan, INPUT_PULLUP);
  pinMode(rem, INPUT_PULLUP);
  
  mx.begin();  
  myDisplay.begin();
  
  myDisplay.setTextAlignment(PA_CENTER);
  myDisplay.setPause(500);
  myDisplay.setSpeed(10);
  
  prevTimeAnim = millis();
  prevTimeDemo = millis();
  
  WiFi.softAP(NAMA_WIFI, PASSWORD_WIFI);
  IPAddress myIP = WiFi.softAPIP();
  server.on("/", handleRoot);
  server.on("/overwriteSettings",overwriteSettings);
  httpUpdater.setup(&server);
  server.begin();
  
  setupBalls(); // Initialize the balls
    
  bool hasRunFlag = EEPROM.read(0);
  
  if (hasRunFlag != 1) {
    String text1 = "lorem ipsum dolor sit amet";
    write_EEPROM(101, 200, text1);
    String text2 = "stoplamp running nih bos";
    write_EEPROM(201, 300, text2);
    String selection = "3";
    write_EEPROM(301, 302, selection);
   
    EEPROM.write(0, 1);
    EEPROM.commit();
  }
  reload_EEPROM();  
}

void loop(){
  kecLed = map(kecerahan, 0,15, 0,255);
  analogWrite(led, kecLed); 
  
  String str0 = inputTEXT1; 
  int str_len0 = str0.length() + 1; 
  char msgtext01[str_len0];
  str0.toCharArray(msgtext01, str_len0);
  
  String str1 = inputTEXT2; 
  int str_len1 = str1.length() + 1; 
  char msgtext02[str_len1];
  str1.toCharArray(msgtext02, str_len1);
  
  msgTab[0]=msgtext01;
  msgTab[1]=msgtext02;
 
  server.handleClient();
  
   int tombolkiri=digitalRead(kiri);
   int tombolkanan=digitalRead(kanan);
   int tombolrem=digitalRead(rem);

  
   if (tombolrem==0){
        Stop_blink(slctStop);
  }else if (tombolkiri==0 && tombolkanan==0){  
          Hati2_blink(slctSein);
  }else if (tombolkiri==0){    
          startTime1 = millis();  // Record the start time
          outputActive1 = true;   // Set the flag to indicate output is active
   } else {
          if (outputActive1 && (millis() - startTime1 >= 1000)) {
             outputActive1 = false;  // Reset the flag
          }
   }
   if (outputActive1){
      bc++;
      if(bc==1){
         myDisplay.displayClear();
         myDisplay.print("                            ");  
      }
      panah_kiri(slctSein);
      cdd=0;
   }
     
   else if (tombolkanan==0){    
          startTime2 = millis();  // Record the start time
          outputActive2 = true;   // Set the flag to indicate output is active
   } else {
          if (outputActive2 && (millis() - startTime2 >= 1000)) {
             outputActive2 = false;  // Reset the flag
          }
   }
   if  (outputActive2){
   bc++;
   if (bc==1){
      myDisplay.displayClear();
      myDisplay.print("                            ");  
   }
   panah_kanan(slctSein);
   cdd=0;
   }
         
    if ((tombolkiri == 1) && (tombolkanan == 1) && (tombolrem == 1) && (!outputActive1) && (!outputActive2)){
      bc=0;
      cdd++;
      if(cdd==1){
         myDisplay.displayClear();
         myDisplay.print("                            ");  
      }
      if ( cdd>10) {cdd=2;}

      if (myDisplay.displayAnimate()) {
        ab=2;
      }
     runMatrixAnimation();
    }   
}
