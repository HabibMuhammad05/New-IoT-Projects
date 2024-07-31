//--uncomment This Section below if you use esp8266 chip----//

//#include <ESP8266WiFi.h>             
//#include <BlynkSimpleEsp8266.h>   

//---uncomment This Section below if you use esp32 chip-----//

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

//----------------------Blynk Setup-------------------------//
#define BLYNK_PRINT Serial
char auth[] = "Your-Auth-Token"; 
char ssid[] = "Your-SSID";        
char pass[] = "Your-Pass";
BlynkTimer timer2;

//-----------------------IR Sensor---------------------------//
#include <IRremote.h>
#define IR_RECV_PIN 35 // D35 (IR receiver pin)
IRrecv irrecv(IR_RECV_PIN);
decode_results results;

//-----------------------DHT Sensor--------------------------//
#include <DHT.h>  
#define DHTTYPE DHT11 
#define DHTPIN              16 //D16  pin connected with DHT
DHT dht(DHTPIN, DHTTYPE);
float temperature1 = 0;
float humidity1   = 0;

//-----------------------LDR Sensor--------------------------//
#define LDR_PIN             34 //D34  pin connected with LDR
int   ldrVal;

//-----------------------PIR Sensor+Audio--------------------//
//#include <SoftwareSerial.h>
#include "DFRobotDFPlayerMini.h"

HardwareSerial playercomms(1);
DFRobotDFPlayerMini mp3;
#define PirPin 3
//-----------------------Relay Pins--------------------------//
#define RelayPin1 23  //D23
#define RelayPin2 22  //D22
#define RelayPin3 21  //D21
#define RelayPin4 19  //D19
#define RelayPin5 18  //D18
#define RelayPin6 5   //D5
#define RelayPin7 25  //D25
#define RelayPin8 26  //D26

//-----------------------Switch Pins--------------------------//
#define SwitchPin1 13  //D13
#define SwitchPin2 12  //D12
#define SwitchPin3 14  //D14
#define SwitchPin4 27  //D27
#define SwitchPin5 33  //D33
#define SwitchPin6 32  //D32
#define SwitchPin7 15  //D15
#define SwitchPin8 4   //D4

//-----------------------WifiLed Pin-------------------------//
#define wifiLed    2   //D2

//----------------Blynk Switch Virtual Pin-------------------//
#define VPIN_BUTTON_1    V1 
#define VPIN_BUTTON_2    V2
#define VPIN_BUTTON_3    V3 
#define VPIN_BUTTON_4    V4
#define VPIN_BUTTON_5    V5 
#define VPIN_BUTTON_6    V6
#define VPIN_BUTTON_7    V7 
#define VPIN_BUTTON_8    V8

//----------------Blynk Other Virtual Pin-------------------//
#define VPIN_BUTTON_C    V9
#define VPIN_TEMPERATURE V10
#define VPIN_HUMIDITY    V11
#define VPIN_LDR         V12

//---------------Relay State Storing Var(s)------------------//
bool toggleState_1 = LOW; 
bool toggleState_2 = LOW;
bool toggleState_3 = LOW;
bool toggleState_4 = LOW;
bool toggleState_5 = LOW; 
bool toggleState_6 = LOW; 
bool toggleState_7 = LOW; 
bool toggleState_8 = LOW; 

//---------------Switch State Storing Var(s)------------------//
bool SwitchState_1 = LOW;
bool SwitchState_2 = LOW;
bool SwitchState_3 = LOW;
bool SwitchState_4 = LOW;
bool SwitchState_5 = LOW;
bool SwitchState_6 = LOW;
bool SwitchState_7 = LOW;
bool SwitchState_8 = LOW;

//----------------------------------------------------------------------------//
//-----------------------------------Void Setup-------------------------------//
//----------------------------------------------------------------------------//
void setup(){
//-----------------------------Serial comms & PIR Start-----------------------//
  Serial.begin(9600);
  playercomms.begin(9600, SERIAL_8N1, 16, 17); // Speed, Type, RX, TX
  
  pinMode(PirPin, INPUT_PULLUP);
  mp3.begin(playercomms);
  mp3.volume(30);  // Set Volume Suara 0-30
  
//------------------------------Blynk Lib Initialize--------------------------//
  Blynk.begin(auth, ssid, pass, "iot.serangkota.go.id", 8080);

//---------------------------Set All Relay Pins to OUTPUT---------------------//
  pinMode(RelayPin1, OUTPUT);
  pinMode(RelayPin2, OUTPUT);
  pinMode(RelayPin3, OUTPUT);
  pinMode(RelayPin4, OUTPUT);
  pinMode(RelayPin5, OUTPUT);
  pinMode(RelayPin6, OUTPUT);
  pinMode(RelayPin7, OUTPUT);
  pinMode(RelayPin8, OUTPUT);
  
//------------------------------Set WifiLed to OUTPUT-------------------------//
  pinMode(wifiLed, OUTPUT);

//------------------Set All Switch Pins to input and on PullUp State----------//
  pinMode(SwitchPin1, INPUT_PULLUP);
  pinMode(SwitchPin2, INPUT_PULLUP);
  pinMode(SwitchPin3, INPUT_PULLUP);
  pinMode(SwitchPin4, INPUT_PULLUP);
  pinMode(SwitchPin5, INPUT_PULLUP);
  pinMode(SwitchPin6, INPUT_PULLUP);
  pinMode(SwitchPin7, INPUT_PULLUP);
  pinMode(SwitchPin8, INPUT_PULLUP);
  
//-------------------------Set All Relays to OFF------------------------------//
  digitalWrite(RelayPin1, HIGH);
  digitalWrite(RelayPin2, HIGH);
  digitalWrite(RelayPin3, HIGH);
  digitalWrite(RelayPin4, HIGH);
  digitalWrite(RelayPin5, HIGH);
  digitalWrite(RelayPin6, HIGH);
  digitalWrite(RelayPin7, HIGH);
  digitalWrite(RelayPin8, HIGH);

//----------------------------Enable IR Sensor--------------------------------//
  irrecv.enableIRIn(); 
  
//-------------------------Initialize DHT Sensor------------------------------//
  dht.begin();
  
//----------------------Set Sensor Datastream Rate----------------------------// 
  timer2.setInterval(2000L, sendSensor);
}

//----------------------------------------------------------------------------//
//-----------------------------------Void Loop--------------------------------//
//----------------------------------------------------------------------------//
void loop() {
    Blynk.run();
    manual_control(); 
    ir_remote();
    Pir_Start();
    timer2.run();
}
