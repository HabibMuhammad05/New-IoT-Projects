//--------------------------------------------------Variable for MAX7219-----------------------------------//
#define NUM_MAX 4
#define LINE_WIDTH 16
#define ROTATE  90

#define DIN_PIN 15  // D8
#define CS_PIN  13  // D7
#define CLK_PIN 12  // D6

#define MAX_DIGITS 16
byte dig[MAX_DIGITS]={0};
byte digold[MAX_DIGITS]={0};
byte digtrans[MAX_DIGITS]={0};
int updCnt = 0;
int dots = 0;
long dotTime = 0;
long clkTime = 0;
int dx=0;
int dy=0;
byte del=0;
int h,m,s;
long localEpoc = 0;
long localMillisAtUpdate = 0;
//--------------------------------------------------Variable for Time-----------------------------------//
int _day, _month, _year, _hour24, _hour12, _minute, _second, _dtw;
int hr24;
String st;
char nameoftheday[7][12] = {"Ahad", "Senin", "Selasa", "Rabu", "Kamis", "Jum'at", "Sabtu"};
char month_name[12][12] = {"Jan","Feb", "Mar", "Apr", "Mei", "Jun", "Jul", "Agu", "Sep", "Okt", "Nov", "Des"};
static uint8_t ijadwal;
uint8_t tipealarm;

//--------------------------------------------------Variable for Millis---------------------------------//
const long interval = 1000; 
unsigned long previousMillis = 0;
const long interval_for_date = 60; //-> For scroll speed
unsigned long previousMillis_for_date = 0;
unsigned long prevdateMillis = 0;
unsigned long previousMillisIsr = 0;

//-----------------------------------------Variable to display hours and minutes------------------------//
char hr_24 [3];
String str_hr_24;
char mn [3];
String str_mn;
char sc [3];
String str_sc;

//----------------------------------------------Variable For Scrolling text-----------------------------//
unsigned long dotMillis=0;

int dotInt = 1000;
bool dotBool;
String teks;
bool Clr = true;
bool scrAnim  = true;

uint8_t tmpinfo = 0;

//--------------------------------------------------------BUZZER----------------------------------------//
const int buzzer = D1;
static boolean beep;
bool setCnt = true;
