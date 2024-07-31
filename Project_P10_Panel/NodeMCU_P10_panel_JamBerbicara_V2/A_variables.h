//--------------------------------------------------------Wifi Setup------------------------------------//
const char* ssid     = "ZAINI MIFTAH";     
const char* password = "120812rj";   

//------------------------------------------------------DMDESP Lib--------------------------------------//
#define DISPLAYS_WIDE 1 // Kolom Panel
#define DISPLAYS_HIGH 1 // Baris Panel
DMDESP Disp(DISPLAYS_WIDE, DISPLAYS_HIGH);

//--------------------------------------------------Variable for Time-----------------------------------//
int _day, _month, _year, _hour24, _hour12, _minute, _second, _dtw;
int hr24, jam24;
String st;
char nameoftheday[7][12] = {"Ahad", "Senin", "Selasa", "Rabu", "Kamis", "Jum'at", "Sabtu"};
char month_name[12][12] = {"Jan","Feb", "Mar", "Apr", "Mei", "Jun", "Jul", "Agu", "Sep", "Okt", "Nov", "Des"};
static uint8_t ijadwal;
uint8_t tipealarm;
//------------------------------------------------Variable for Epoch time-------------------------------//
time_t requestSync(){
  Serial.write(7); 
  return 0; 
}

//------------------------------------------------Variable for NTP Clock--------------------------------//
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");
unsigned long Epoch_Time; 
uint8_t utcOffset = 7; // Time Zone setting

//------------------------------------------------Variable for prayerTimes------------------------------//
float lati = -6.5058400;
float longi = 106.8380890;
double times[sizeof(TimeName)/sizeof(char*)];
int ihti = 2;

//--------------------------------------------------Variable for Millis---------------------------------//
const long interval = 1000; 
unsigned long previousMillis = 0;
const long interval_for_date = 60; //-> For scroll speed
unsigned long previousMillis_for_date = 0;
unsigned long prevdateMillis = 0;
unsigned long previousMillisIsr = 0;

unsigned long previousPrint = 0;

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

uint8_t tmpinfo;

//--------------------------------------------------------BUZZER----------------------------------------//
const int buzzer = LED_BUILTIN;
static boolean beep;
bool setCnt = true;

//------------------------------------------Variables for Audio Clock DFplayer--------------------------//
SoftwareSerial playercomms(4, 5);
DFRobotDFPlayerMini mp3;

int previousHour = -1;
bool hourChanged = false;

#define tombol_jam A0
bool lebih, kurang, pas;

//---------------------------------------------Variables for Setup Webserver----------------------------//
String T1_SSID, T2_PASS, T3_latitude, T4_longitude;

bool norMode = true;

ESP8266WebServer server(80);
ESP8266HTTPUpdateServer httpUpdater;
