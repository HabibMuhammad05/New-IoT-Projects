/*
   This ESP32 code is created by esp32io.com

   This ESP32 code is released in the public domain

   For more detail (instruction and wiring diagram), visit https://esp32io.com/tutorials/esp32-joystick
*/

//master
#include<esp_now.h>
#include<WiFi.h>


#define VRX_PIN  34 // ESP32 pin GPIO36 (ADC0) connected to VRX pin
#define VRY_PIN  35 // ESP32 pin GPIO39 (ADC0) connected to VRY pin
#define VRX_PIN2  32 // ESP32 pin GPIO36 (ADC0) connected to VRX pin
#define VRY_PIN2  33 // ESP32 pin GPIO39 (ADC0) connected to VRY pin

const uint8_t channel[4] = {0, 1, 2, 3};
const uint8_t led[4] = {25, 27, 14, 26};

int valX, valY, valX2, valY2;
unsigned int AvalX, AvalY, AvalX2, AvalY2;
uint8_t j1Up, j1Down, j1Left, j1Right;
uint8_t j2Up, j2Down, j2Left, j2Right;

uint8_t broadcastAddress[]={0xCC,0x50,0xE3,0xF0,0x1E,0x36};

typedef struct Pesan{
  uint8_t pwmJ1Up, pwmJ1Down, pwmJ1Left, pwmJ1Right;
  uint8_t pwmJ2Up, pwmJ2Down, pwmJ2Left, pwmJ2Right;
}Pesan;
Pesan pesan;

esp_now_peer_info_t slave;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status){
  Serial.print("\r\nStatus terakhir:\t");
  Serial.println(status==ESP_NOW_SEND_SUCCESS?"Terkirim":"Gagal");
}

void setup() {
  Serial.begin(115200) ;
  for (int i = 0; i < 4; i++) {
    ledcSetup(channel[i], 2000, 8); //(channel, frequency, resolution)
    ledcAttachPin(led[i], channel[i]);
  }

  WiFi.mode(WIFI_STA);
  if(esp_now_init()!=ESP_OK){
    Serial.println("ESPNow Gagal!");
    return;
  }
  esp_now_register_send_cb(OnDataSent);
  memcpy(slave.peer_addr, broadcastAddress, 6);
  slave.channel = 0;  
  slave.encrypt = false;       
  if(esp_now_add_peer(&slave) != ESP_OK){
    Serial.println("Gagal menambahkan slave!");
    return;
  }
}

void loop() {
  valX = analogRead(VRX_PIN) - 720;
  valY = analogRead(VRY_PIN) - 720;
  valX2 = analogRead(VRX_PIN2) - 720;
  valY2 = analogRead(VRY_PIN2) - 720;

  AvalX = (valX < 0) ? 0 : (valX > 2200) ? 2200 : valX;
  AvalY = (valY < 0) ? 0 : (valY > 2200) ? 2200 : valY;
  AvalX2 = (valX2 < 0) ? 0 : (valX2 > 2200) ? 2200 : valX2;
  AvalY2 = (valY2 < 0) ? 0 : (valY2 > 2200) ? 2200 : valY2;

  if (AvalX <= 1000) {
    j1Up = map(AvalX, 0, 1000, 255, 0);
  }
  else if (AvalX >= 1200) {
    j1Down = map(AvalX, 1200, 2200, 0, 255);
  }
  else {
    j1Up = 0;
    j1Down = 0;
  }

  if (AvalY <= 1000) {
    j1Right = map(AvalY, 0, 1000, 255, 0);
  }
  else if (AvalY >= 1200) {
    j1Left = map(AvalY, 1200, 2200, 0, 255);
  }
  else {
    j1Left = 0;
    j1Right = 0;
  }

  if (AvalX2 <= 1000) {
    j2Up = map(AvalX2, 0, 1000, 255, 0);
  }
  else if (AvalX2 >= 1200) {
    j2Down = map(AvalX2, 1200, 2200, 0, 255);
  }
  else {
    j2Up = 0;
    j2Down = 0;
  }

  if (AvalY2 <= 1000) {
    j2Right = map(AvalY2, 0, 1000, 255, 0);
  }
  else if (AvalY2 >= 1200) {
    j2Left = map(AvalY2, 1200, 2200, 0, 255);
  }
  else {
    j2Left = 0;
    j2Right = 0;
  }


  Serial.println("   "  + String(j1Up) +  "          "  + String(j2Up) +  "   ");
  Serial.println(String(j1Left) + " (J1) " + String(j1Right) + "   " +  String(j2Left) + " (J2) " + String(j2Right));
  Serial.println("   "  + String(j1Down) +  "          "  + String(j2Down) +  "   ");
  Serial.println();
  Serial.println();

//  ledcWrite(channel[1], j1Up);
//  ledcWrite(channel[2], j1Down);
//  ledcWrite(channel[3], j1Right);
//  ledcWrite(channel[4], j1Left);

  if(j1Up > 0 || j1Down > 0 || j1Left > 0 || j1Right > 0){
    ledcWrite(channel[0], j1Up);
    ledcWrite(channel[1], j1Down);
    ledcWrite(channel[2], j1Right);
    ledcWrite(channel[3], j1Left);
  }else{
    ledcWrite(channel[0], j2Up);
    ledcWrite(channel[1], j2Down);
    ledcWrite(channel[2], j2Right);
    ledcWrite(channel[3], j2Left);
  }

  pesan.pwmJ1Up = j1Up;
  pesan.pwmJ1Down = j1Down;
  pesan.pwmJ1Left = j1Left;
  pesan.pwmJ1Right = j1Right;
  
  pesan.pwmJ2Up = j2Up;
  pesan.pwmJ2Down = j2Down;
  pesan.pwmJ2Left = j2Left;
  pesan.pwmJ2Right = j2Right;
  
  esp_err_t result=esp_now_send(broadcastAddress,(uint8_t *)&pesan,sizeof(pesan));
  
  delay(100);
}

//  Serial.print("x1 = ");
//  Serial.print(valX);
//  Serial.print(", y1 = ");
//  Serial.print(valY);
//  Serial.print("   x2 = ");
//  Serial.print(valX2);
//  Serial.print(", y2 = ");
//  Serial.print(valY2);
//  Serial.print("    PROC : x1 = ");
//  Serial.print(AvalX);
//  Serial.print(", y1 = ");
//  Serial.print(AvalY);
//  Serial.print("   x2 = ");
//  Serial.print(AvalX2);
//  Serial.print(", y2 = ");
//  Serial.print(AvalY2);
//
//
//  Serial.print("     j1Up = ");
//  Serial.print(j1Up);
//  Serial.print(" j1Down = ");
//  Serial.print(j1Down);
//  Serial.print(" j1Left = ");
//  Serial.print(j1Left);
//  Serial.print(" j1Right = ");
//  Serial.print(j1Right);
//
//  Serial.print("     j2Up = ");
//  Serial.print(j2Up);
//  Serial.print(" j2Down = ");
//  Serial.print(j2Down);
//  Serial.print(" j2Left = ");
//  Serial.print(j2Left);
//  Serial.print(" j2Right = ");
//  Serial.println(j2Right);
