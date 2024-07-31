/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp-now-esp8266-nodemcu-arduino-ide/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

#include <ESP8266WiFi.h>
#include <espnow.h>

const uint8_t led[4] = {0, 5, 3, 4};

typedef struct struct_message{
  uint8_t pwmJ1Up, pwmJ1Down, pwmJ1Left, pwmJ1Right;
  uint8_t pwmJ2Up, pwmJ2Down, pwmJ2Left, pwmJ2Right;
}struct_message;
struct_message pesan;

// Callback function that will be executed when data is received
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&pesan, incomingData, sizeof(pesan));
//  Serial.print("Bytes received: ");
//  Serial.println(len);
  
}
 
void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  pinMode(led[0], OUTPUT);
  pinMode(led[1], OUTPUT);
  pinMode(led[2], OUTPUT);
  pinMode(led[3], OUTPUT);
  
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);
  
  
}

void loop() {
  
  if(pesan.pwmJ1Up > 0 || pesan.pwmJ1Down > 0 || pesan.pwmJ1Left > 0 || pesan.pwmJ1Right > 0){
    analogWrite(led[0], pesan.pwmJ1Up);
    analogWrite(led[1], pesan.pwmJ1Down);
    analogWrite(led[2], pesan.pwmJ1Right);
    analogWrite(led[3], pesan.pwmJ1Left);
  }else{
    analogWrite(led[0], pesan.pwmJ2Up);
    analogWrite(led[1], pesan.pwmJ2Down);
    analogWrite(led[2], pesan.pwmJ2Right);
    analogWrite(led[3], pesan.pwmJ2Left);
  }
  
  Serial.println("   "  + String(pesan.pwmJ1Up) +  "          "  + String(pesan.pwmJ2Up) +  "   ");
  Serial.println(String(pesan.pwmJ1Left) + " (J1) " + String(pesan.pwmJ1Right) + "   " +  String(pesan.pwmJ2Left) + " (J2) " + String(pesan.pwmJ2Right));
  Serial.println("   "  + String(pesan.pwmJ1Down) +  "          "  + String(pesan.pwmJ2Down) +  "   ");
  Serial.println();
  Serial.println();
  delay(100);
  
}
