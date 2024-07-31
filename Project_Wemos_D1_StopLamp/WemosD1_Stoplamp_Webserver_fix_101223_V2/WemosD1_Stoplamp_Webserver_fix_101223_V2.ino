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

*/

// ======== Libraries =========
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

#define DATA_PIN    15  // D8
#define CS_PIN      13  // D7
#define CLK_PIN     12  // D6

#define kanan       14  // D5 
#define kiri        2  // D4 
#define rem         5   // D1 
#define led         4   // D2 

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


// ========== Various Delay in miliseconds ===========

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
#define BOUNCE_DELAY    (4 * UNIT_DELAY)

#define CHAR_SPACING     1  // pixels between characters
#define BUF_SIZE        75  // character buffer size

// ========== General Variables ===========
uint8_t DEMO_DELAY = 8; 
bool sensorRead;
bool flag;
byte slct = 1;
byte slctSein = 1;
byte slctStop = 1;
uint32_t prevTimeAnim = 0;    // Used for remembering the millis() value in animations
uint32_t prevTimeDemo = 0;      //  Used for remembering the millis() time in demo loop
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

const uint8_t modCount = 15;
bool manualMode[modCount];
uint8_t kecepatan = 30;
uint8_t kecerahan = MAX_INTENSITY/2;
uint8_t seinDelay = 25; 
uint8_t stopDelay = 25; 

uint8_t kecLed = map(kecerahan, 0,15, 0,255);

int ab = 0;
int bc = 0;
int cdd = 0;

// ========== Wi-Fi Configuration ===========

ESP8266WebServer server(80);
ESP8266HTTPUpdateServer httpUpdater;

// ========== Graphic routines ===========
bool scrollText(bool bInit, const char *pmsg)
{
  static char   curMessage[BUF_SIZE];
  static char   *p = curMessage;
  static uint8_t  state = 0;
  static uint8_t  curLen, showLen;
  static uint8_t  cBuf[8];
  uint8_t         colData;
  
  myDisplay.setFont(bmz6x8);
  
//  mx.transform(MD_MAX72XX::TSD);
  // are we initializing?
  if (bInit)
  {
    PRINTS("\n--- Initializing ScrollText");
    resetMatrix();
    strcpy(curMessage, pmsg);
    state = 0;
    p = curMessage;
    bInit = false;
  }

  // Is it time to scroll the text?
  if (millis()-prevTimeAnim < SCROLL_DELAY)
    return(bInit);

  // scroll the display
  mx.transform(MD_MAX72XX::TSL);  // scroll along
  prevTimeAnim = millis();        // starting point for next time

  // now run the finite state machine to control what we do
  PRINT("\nScroll FSM S:", state);
  switch (state)
  {
    case 0: // Load the next character from the font table
      PRINTC("\nLoading ", *p);
      showLen = mx.getChar(*p++, sizeof(cBuf)/sizeof(cBuf[0]), cBuf);
      curLen = 0;
      state = 1;

    // !! deliberately fall through to next state to start displaying

    case 1: // display the next part of the character
      colData = cBuf[curLen++];
      mx.setColumn(0, colData);
      if (curLen == showLen)
      {
        showLen = ((*p != '\0') ? CHAR_SPACING : mx.getColumnCount()-1);
        curLen = 0;
        state = 2;
      }
      break;

    case 2: // display inter-character spacing (blank column) or scroll off the display
      mx.setColumn(0, 0);
      if (++curLen == showLen)
      {
        state = 0;
        bInit = (*p == '\0');
      }
      break;

    default:
      state = 0;
  }
//    mx.transform(MD_MAX72XX::TSU);
  return(bInit);
}

bool graphicMidline2(bool bInit)
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

bool graphicScanner(bool bInit)
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

bool graphicRandom(bool bInit)
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

bool graphicScroller(bool bInit)
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

bool graphicSpectrum1(bool bInit)
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

bool graphicSpectrum2(bool bInit)
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

bool graphicHeartbeat(bool bInit)
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

bool graphicFade(bool bInit)
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

bool graphicHearts(bool bInit)
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

bool graphicEyes(bool bInit)
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

bool graphicBounceBall(bool bInit)
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

bool graphicArrowScroll(bool bInit)
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

bool graphicWiper(bool bInit)
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

bool graphicInvader(bool bInit)
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

bool graphicPacman(bool bInit)
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

bool graphicArrowRotate(bool bInit)
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

bool graphicSinewave(bool bInit)
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


bool rows(bool bInit)
{
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
  
  for (uint8_t row=0; row<ROW_SIZE; row++)
  {
  
    mx.setRow(row, 0xff);
    delay(ROWS_DELAY);
    mx.setRow(row, 0x00);
  }
  return(bInit);
}

bool checkboard(bool bInit)
{
  uint8_t chkCols[][2] = { { 0x55, 0xaa }, { 0x33, 0xcc }, { 0x0f, 0xf0 }, { 0xff, 0x00 } };

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
  
  for (uint8_t pattern = 0; pattern < 3; pattern++)
  {
    uint8_t col = 0;
    uint8_t idx = 0;
    uint8_t rep = 1 << pattern;

    while (col < mx.getColumnCount())
    {
  
      for (uint8_t r = 0; r < rep; r++)
        mx.setColumn(col++, chkCols[pattern][idx]);   // use odd/even column masks
      idx++;
      if (idx > 1) idx = 0;
    }

    delay(CHKBRD_DELAY);
  }
  return(bInit);
}

bool columnss(bool bInit)
{
  // are we initializing?
  if (bInit)
  {
    PRINTS("\n--- cols init");
    resetMatrix();
    bInit = false;
  }

  // Is it time to animate?
  if (millis() - prevTimeAnim < COLS_DELAY/MAX_DEVICES){
    return(bInit);
  prevTimeAnim = millis();}   // starting point for next time
  
  for (uint8_t col=0; col<mx.getColumnCount(); col++)
  {
    mx.setColumn(col, 0xff);
    delay(COLS_DELAY/MAX_DEVICES);
    mx.setColumn(col, 0x00);
  }
  return(bInit);
}

bool cross(bool bInit)
{
  // are we initializing?
  if (bInit)
  {
    PRINTS("\n--- cross init");
    resetMatrix();
    mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
    bInit = false;
  }

  // Is it time to animate?
  if (millis() - prevTimeAnim < CROSS_DELAY){
    return(bInit);
  prevTimeAnim = millis();}    // starting point for next time
  
  // diagonally down the display R to L
  for (uint8_t i=0; i<ROW_SIZE; i++)
  {
    for (uint8_t j=0; j<MAX_DEVICES; j++)
    {
      mx.setColumn(j, i, 0xff);
      mx.setRow(j, i, 0xff);
    }
    mx.update();
    delay(CROSS_DELAY);
    for (uint8_t j=0; j<MAX_DEVICES; j++)
    {
      mx.setColumn(j, i, 0x00);
      mx.setRow(j, i, 0x00);
    }
  }

  // moving up the display on the R
  for (int8_t i=ROW_SIZE-1; i>=0; i--)
  {
    for (uint8_t j=0; j<MAX_DEVICES; j++)
    {
      mx.setColumn(j, i, 0xff);
      mx.setRow(j, ROW_SIZE-1, 0xff);
    }
    mx.update();
    delay(CROSS_DELAY);
    for (uint8_t j=0; j<MAX_DEVICES; j++)
    {  
      mx.setColumn(j, i, 0x00);
      mx.setRow(j, ROW_SIZE-1, 0x00);
    }
  }

  // diagonally up the display L to R
  for (uint8_t i=0; i<ROW_SIZE; i++)
  {
    for (uint8_t j=0; j<MAX_DEVICES; j++)
    {
      mx.setColumn(j, i, 0xff);
      mx.setRow(j, ROW_SIZE-1-i, 0xff);
    }
    mx.update();
    delay(CROSS_DELAY);
    for (uint8_t j=0; j<MAX_DEVICES; j++)
    {
      mx.setColumn(j, i, 0x00);
      mx.setRow(j, ROW_SIZE-1-i, 0x00);
    }
  }
  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
  return(bInit);
}

bool bullseye(bool bInit)
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
  
  for (uint8_t n=0; n<3; n++)
  {
    byte  b = 0xff;
    int   i = 0;

    while (b != 0x00)
    {
      for (uint8_t j=0; j<MAX_DEVICES+1; j++)
      {
  
        mx.setRow(j, i, b);
        mx.setColumn(j, i, b);
        mx.setRow(j, ROW_SIZE-1-i, b);
        mx.setColumn(j, COL_SIZE-1-i, b);
      }
      mx.update();
      delay(BULLS_DELAY);
      for (uint8_t j=0; j<MAX_DEVICES+1; j++)
      {
        mx.setRow(j, i, 0);
        mx.setColumn(j, i, 0);
        mx.setRow(j, ROW_SIZE-1-i, 0);
        mx.setColumn(j, COL_SIZE-1-i, 0);
      }

      bitClear(b, i);
      bitClear(b, 7-i);
      i++;
    }

    while (b != 0xff)
    {
      for (uint8_t j=0; j<MAX_DEVICES+1; j++)
      {
        mx.setRow(j, i, b);
        mx.setColumn(j, i, b);
        mx.setRow(j, ROW_SIZE-1-i, b);
        mx.setColumn(j, COL_SIZE-1-i, b);
      }
      mx.update();
      delay(BULLS_DELAY);
      for (uint8_t j=0; j<MAX_DEVICES+1; j++)
      {
        mx.setRow(j, i, 0);
        mx.setColumn(j, i, 0);
        mx.setRow(j, ROW_SIZE-1-i, 0);
        mx.setColumn(j, COL_SIZE-1-i, 0);
      }

      i--;
      bitSet(b, i);
      bitSet(b, 7-i);
    }
  }

  mx.control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
  return(bInit);
}

bool stripe(bool bInit)
{
  const uint16_t maxCol = MAX_DEVICES*ROW_SIZE;
  const uint8_t stripeWidth = 10;

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
  
  for (uint16_t col=0; col<maxCol + ROW_SIZE + stripeWidth; col++)
  {
    for (uint8_t row=0; row < ROW_SIZE; row++)
    {
      mx.setPoint(row, col-row, true);
      mx.setPoint(row, col-row - stripeWidth, false);
    }
    delay(STRIPE_DELAY);
  }
  return(bInit);
}

bool spiral(bool bInit)
{
  int  rmin = 0, rmax = ROW_SIZE-1;
  int  cmin = 0, cmax = (COL_SIZE*MAX_DEVICES)-1;
  
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
  
  while ((rmax > rmin) && (cmax > cmin))
  {
    // do row
    for (int i=cmin; i<=cmax; i++)
    {  
      mx.setPoint(rmin, i, true);
      delay(SPIRAL_DELAY/MAX_DEVICES);
    }
    rmin++;

    // do column
    for (uint8_t i=rmin; i<=rmax; i++)
    {  
      mx.setPoint(i, cmax, true);
      delay(SPIRAL_DELAY/MAX_DEVICES);
    }
    cmax--;

    // do row
    for (int i=cmax; i>=cmin; i--)
    {  
      mx.setPoint(rmax, i, true);
      delay(SPIRAL_DELAY/MAX_DEVICES);
    }
    rmax--;

    // do column
    for (uint8_t i=rmax; i>=rmin; i--)
    {  
      mx.setPoint(i, cmin, true);
      delay(SPIRAL_DELAY/MAX_DEVICES);
    }
    cmin++;
    
  }
    mx.transform(MD_MAX72XX::TINV);
//  mx.setInvert(!mx.getInvert());
  return(bInit);
}

bool bounce(bool bInit)
{
  const int minC = 0;
  const int maxC = mx.getColumnCount()-1;
  const int minR = 0;
  const int maxR = ROW_SIZE-1;

  int  nCounter = 0;

  int  r = 0, c = 2;
  int8_t dR = 1, dC = 1;  // delta row and column

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
  
  while (nCounter++ < 60)
  {
  
    mx.setPoint(r, c, false);
    r += dR;
    c += dC;
    mx.setPoint(r, c, true);
    delay(BOUNCE_DELAY);

    if ((r == minR) || (r == maxR))
      dR = -dR;
    if ((c == minC) || (c == maxC))
      dC = -dC;
  }
  return(bInit);
}

// ========== Control routines ===========

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
    if (--timeDemo <= 0 && !bRestart){
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
      case  1: bRestart = graphicMidline2(bRestart);           break;
      case  2: bRestart = graphicRandom(bRestart);             break;
      case  3: bRestart = graphicScanner(bRestart);            break;
      case  4: bRestart = graphicSpectrum1(bRestart);          break;
      case  5: bRestart = graphicSinewave(bRestart);           break;
      case  6: bRestart = graphicBounceBall(bRestart);         break;
      case  7: bRestart = graphicHearts(bRestart);             break;
      case  8: bRestart = graphicPacman(bRestart);             break;
      case  9: bRestart = graphicHeartbeat(bRestart);          break;
      case 10: bRestart = graphicWiper(bRestart);              break;
      case 11: bRestart = graphicInvader(bRestart);            break;
      case 12: bRestart = graphicEyes(bRestart);               break;
      case 13: bRestart = graphicSpectrum2(bRestart);          break;
      case 14: bRestart = graphicFade(bRestart);               break;
      case 15: bRestart = graphicScroller(bRestart);           break;
      case 16: bRestart = rows(bRestart);                      break;
      case 17: bRestart = checkboard(bRestart);                break;
      case 18: bRestart = columnss(bRestart);                  break;
      case 19: bRestart = cross(bRestart);                     break;
      case 20: bRestart = bullseye(bRestart);                  break;
      case 21: bRestart = stripe(bRestart);                    break;
      case 22: bRestart = spiral(bRestart);                    break;
      case 23: bRestart = bounce(bRestart);                    break;
//      case 16: bRestart = graphicArrowRotate(bRestart);      break;
//      case 17: bRestart = graphicArrowScroll(bRestart);      break;
      default: state = 1; 
    }
  }
  if (slct == 3){
    switch(state){
      case  0: bInMessages = true; 
               bRestart = scrollText(bRestart, msgTab[mesg]);  break;
      case  1: bRestart = graphicMidline2(bRestart);           break;
      case  2: bRestart = graphicRandom(bRestart);             break;
      case  3: bRestart = graphicScanner(bRestart);            break;
      case  4: bRestart = graphicSpectrum1(bRestart);          break;
      case  5: bRestart = graphicSinewave(bRestart);           break;
      case  6: bRestart = graphicBounceBall(bRestart);         break;
      case  7: bRestart = graphicHearts(bRestart);             break;
      case  8: bRestart = graphicPacman(bRestart);             break;
      case  9: bRestart = graphicHeartbeat(bRestart);          break;
      case 10: bRestart = graphicWiper(bRestart);              break;
      case 11: bRestart = graphicInvader(bRestart);            break;
      case 12: bRestart = graphicEyes(bRestart);               break;
      case 13: bRestart = graphicSpectrum2(bRestart);          break;
      case 14: bRestart = graphicFade(bRestart);               break;
      case 15: bRestart = graphicScroller(bRestart);           break;
      case 16: bRestart = rows(bRestart);                      break;
      case 17: bRestart = checkboard(bRestart);                break;
      case 18: bRestart = columnss(bRestart);                  break;
      case 19: bRestart = cross(bRestart);                     break;
      case 20: bRestart = bullseye(bRestart);                  break;
      case 21: bRestart = stripe(bRestart);                    break;
      case 22: bRestart = spiral(bRestart);                    break;
      case 23: bRestart = bounce(bRestart);                    break;
//      case 16: bRestart = graphicArrowRotate(bRestart);      break;
//      case 17: bRestart = graphicArrowScroll(bRestart);      break;
      default: state = 0;
    }
  }
//      (!manualMode[0]) ? (state = 1) : ;   resetMatrix(); break;
  if (slct == 4){
    switch(state){
      case  0: if (!manualMode[0]){ state = state + 1; }
               else { bInMessages = true; bRestart = scrollText(bRestart, msgTab[mesg]); }      break;
      case  1: (!manualMode[1]) ? (state = 2) :  (bRestart = graphicMidline2(bRestart));        break;
      case  2: (!manualMode[2]) ? (state = 3) :  (bRestart = graphicRandom(bRestart));          break;
      case  3: (!manualMode[3]) ? (state = 4) :  (bRestart = graphicScanner(bRestart));         break;
      case  4: (!manualMode[4]) ? (state = 5) :  (bRestart = graphicSpectrum1(bRestart));       break;
      case  5: (!manualMode[5]) ? (state = 6) :  (bRestart = graphicSinewave(bRestart));        break;
      case  6: (!manualMode[6]) ? (state = 7) :  (bRestart = graphicBounceBall(bRestart));      break;
      case  7: (!manualMode[7]) ? (state = 8) :  (bRestart = graphicHearts(bRestart));          break;
      case  8: (!manualMode[8]) ? (state = 9) :  (bRestart = graphicPacman(bRestart));          break;
      case  9: (!manualMode[9]) ? (state = 10) : (bRestart = graphicHeartbeat(bRestart));       break;
      case 10: (!manualMode[10]) ? (state = 11) :(bRestart = graphicWiper(bRestart));           break;
      case 11: (!manualMode[11]) ? (state = 12) :(bRestart = graphicInvader(bRestart));         break;
      case 12: (!manualMode[12]) ? (state = 13) :(bRestart = graphicEyes(bRestart));            break;
      case 13: (!manualMode[13]) ? (state = 14) :(bRestart = graphicSpectrum2(bRestart));       break;
      case 14: (!manualMode[14]) ? (state = 15) :(bRestart = graphicFade(bRestart));            break;
      case 15: (!manualMode[15]) ? (state = 0) : (bRestart = graphicScroller(bRestart));        break;
//      case 16: bRestart = graphicArrowRotate(bRestart);      break;
//      case 17: bRestart = graphicArrowScroll(bRestart);      break;
      default: state = 0;
    }
  }
}

// ======== WEB Interface =========
void handleRoot() {
  String T1=inputTEXT1.substring(0, 13);
  String T2=inputTEXT2.substring(0, 13);
  uint8_t cepat=kecepatan;
  uint8_t bright=kecerahan;
  uint8_t waktuAnim=DEMO_DELAY;
  uint8_t waktuSein=seinDelay;
  uint8_t waktuStop=stopDelay;

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
  html=html+"                    <label><input type='radio' id='slc1' name='selection' value='1' > Running Teks </label>"; 
  html=html+"                    <label><input type='radio' id='slc2' name='selection' value='2'> Animasi </label>"; 
  html=html+"                    <label><input type='radio' id='slc3' name='selection' value='3'> Kombinasi </label>"; 
  html=html+"                    <label><input type='radio' id='slc4' name='selection' value='4'> Manual </label>"; 
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
  html=html+"            <tr><td colspan='4'><label>Animasi (Pilih Mode Manual): </label></td></tr>"; 
  html=html+"            <tr>"; 
  html=html+"                <td style='width:25%'>"; 
  html=html+"                   <label><input type='checkbox' id='man1' name='man1' value='1'> 1</label>";
  html=html+"                   <br>";  
  html=html+"                   <label><input type='checkbox' id='man2' name='man2' value='1'> 2</label>"; 
  html=html+"                   <br>";  
  html=html+"                   <label><input type='checkbox' id='man3' name='man3' value='1'> 3</label>"; 
  html=html+"                   <br>";  
  html=html+"                   <label><input type='checkbox' id='man4' name='man4' value='1'> 4</label>"; 
  html=html+"                   <br>";  
  html=html+"                   <label><input type='checkbox' id='man5' name='man5' value='1'> 5</label>"; 
  html=html+"                </td>"; 
  html=html+"                <td style='width:25%'>"; 
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
  html=html+"                <td style='width:25%'>"; 
  html=html+"                   <label><input type='checkbox' id='man11' name='man1' value='1'> 11</label>";
  html=html+"                   <br>";  
  html=html+"                   <label><input type='checkbox' id='man12' name='man2' value='1'> 12</label>"; 
  html=html+"                   <br>";  
  html=html+"                   <label><input type='checkbox' id='man13' name='man3' value='1'> 13</label>"; 
  html=html+"                   <br>";  
  html=html+"                   <label><input type='checkbox' id='man14' name='man4' value='1'> 14</label>"; 
  html=html+"                   <br>";  
  html=html+"                   <label><input type='checkbox' id='man15' name='man5' value='1'> 15</label>"; 
  html=html+"                </td>"; 
  html=html+"                <td style='width:25%'>"; 
  html=html+"                   <label><input type='checkbox' id='man16' name='man6' value='1'> 16</label>"; 
  html=html+"                   <br>";  
  html=html+"                   <label><input type='checkbox' id='man17' name='man7' value='1'> 17</label>"; 
  html=html+"                   <br>";  
  html=html+"                   <label><input type='checkbox' id='man18' name='man8' value='1'> 18</label>"; 
  html=html+"                   <br>";  
  html=html+"                   <label><input type='checkbox' id='man19' name='man9' value='1'> 19</label>"; 
  html=html+"                   <br>";  
  html=html+"                   <label><input type='checkbox' id='man20' name='man10' value='1'> 20</label>"; 
  html=html+"                </td>"; 
  html=html+"            </tr>"; 
  html=html+"        </table>";
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
  html=html+"                    <label><input type='radio' id='slc1' name='slctSein' value='1' checked> 1</label>";
  html=html+"                    <label><input type='radio' id='slc2' name='slctSein' value='2'> 2</label>";
  html=html+"                    <label><input type='radio' id='slc3' name='slctSein' value='3'> 3</label>";
  html=html+"                    <br><br><br>";
  html=html+"                    <label>Kecepatan Stop Sekarang : "+waktuStop+"mS</label>"; 
  html=html+"                    <br><br>"; 
  html=html+"                    <input type='range' style='width: 500px' id='rangeSein' name='Stop' value='"+waktuStop+"' min='2' max='50' oninput='this.nextElementSibling.value = this.value'>";
  html=html+"                    <output>"+waktuStop+"</output>mS"; 
  html=html+"                    <br><br>";
  html=html+"                    <label>Mode Stop :   </label>";
  html=html+"                    <label><input type='radio' id='slc1' name='slctStop' value='1' checked> 1</label>";
  html=html+"                    <label><input type='radio' id='slc2' name='slctStop' value='2'> 2</label>";
  html=html+"                    <label><input type='radio' id='slc3' name='slctStop' value='3'> 3</label>";
  html=html+"                </td>";
  html=html+"           </tr>";
  html=html+"        </table>";
  html=html+"        <table>";
  html=html+"            <tr>";
  html=html+"                <td colspan='2'>";
  html=html+"                    <input type='submit' name='Save' value='Submit'>";
  html=html+"                </td>";
  html=html+"            </tr>";
  html=html+"            <tr>";
  html=html+"                <td colspan='2'>";
  html=html+"                   <h5><a href='http://192.168.4.1/update'>© 2023 vario Stoplamp</a></h5>";
  html=html+"                   <h5>";
  html=html+"                     <a href='https://www.youtube.com/@DBOSSProject'>@DBOSSProject</a> x";
  html=html+"                     <a href='https://www.instagram.com/Hab_mz'>@Hab_mz</a>";
  html=html+"                   </h5>";
  html=html+"                </td>";
  html=html+"            </tr>";
  html=html+"        </table>";
  html=html+"    </form>";
  html=html+"</div>";
  html=html+"</body>";
  html=html+"</html>";
  server.send(200,"text/html",html);
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
  write_EEPROM(350, 352, Sein);
  
  String Stop = server.arg("Stop");
  write_EEPROM(353, 355, Stop);
  
  String selSein = server.arg("slctSein");
  write_EEPROM(356, 357, selSein);  
  String selSetop = server.arg("slctStop");
  write_EEPROM(358, 359, selSetop);  
  
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
  html=html+"    <h4>Kecepatan Sein-Rem : "+Sein+" mS</h2>";
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
  
  reload_EEPROM();
//  bInMessages = true;
}

// ======== EEPROM =========
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
  
  String Sein2 = read_EEPROM(350, 352);
  Sein2 = Sein2.substring(0,Sein2.length());
  seinDelay = Sein2.toInt();
  
  String Stop2 = read_EEPROM(353, 355);
  Stop2 = Stop2.substring(0,Stop2.length());
  stopDelay = Stop2.toInt();

  String tempSein = read_EEPROM(356,357);
  tempSein = tempSein.substring(0,tempSein.length());
  slctSein = tempSein.toInt();
  String tempStop = read_EEPROM(358,359);
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

void panah_kiri(byte sMod){
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
//        scrollingText("[[[[[");
//        myDisplay.displayClear();
//        myDisplay.print("                            ");  
//        if (myDisplay.displayAnimate()) {
//              uint8_t ab=2; 
//              myDisplay.setFont(bmz6x8);
//              myDisplay.displayText("[[[[[", myDisplay.getTextAlignment(), myDisplay.getSpeed(), myDisplay.getPause(), texteffect[ab], texteffect[ab]);
//              myDisplay.displayReset();
//             }
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

void Stop_blink(byte sMod){
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
      myDisplay.print("======");
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

void Hati2_blink(){
  myDisplay.setTextAlignment(PA_CENTER);
  myDisplay.setFont(bmz6x8);
  myDisplay.print("[]");
  digitalWrite(led, LOW);
  delay(stopDelay* 5);
  myDisplay.print("[[]]"); 
  digitalWrite(led, LOW); 
  delay(stopDelay* 5);
  myDisplay.print("[[[]]]");
    analogWrite(led, kecLed);
  delay(stopDelay* 5);
  myDisplay.print("       "); 
    analogWrite(led, kecLed);
  delay(stopDelay* 5);
}

// ======== Main Program =========

void setup(){
  #if DEBUG
    Serial.begin(115200);
  #endif 
  EEPROM.begin(512);

  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);
  
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
      }  
    
   else if (tombolkiri==0){    
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

//   if (tombolrem==0){ Stop_blink(slctStop); }  
//    
//   else if (tombolkiri==0){    
//       startTime1 = millis();  // Record the start time
//       outputActive1 = true;   // Set the flag to indicate output is active
//   } 
//   else if (tombolkanan==0){    
//      startTime2 = millis();  // Record the start time
//      outputActive2 = true;   // Set the flag to indicate output is active
//   }
//   
//   if (outputActive1 && (millis() - startTime1 >= 1500)) { outputActive1 = false; }
//   if (outputActive1){ panah_kiri(slctSein); }
//   
//   if (outputActive2 && (millis() - startTime2 >= 1500)) { outputActive2 = false; }
//   if (outputActive2){ panah_kanan(slctSein); }
//   
//   if ((tombolkiri == 1) && (tombolkanan == 1) && (tombolrem == 1) && (!outputActive1) && (!outputActive2)){
//     runMatrixAnimation();
//   }
   
}
