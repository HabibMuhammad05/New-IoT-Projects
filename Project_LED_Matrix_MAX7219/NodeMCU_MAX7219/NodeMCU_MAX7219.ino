#include "Arduino.h"
#include <ESP8266WiFi.h>

#define NUM_MAX 4
#define LINE_WIDTH 16
#define ROTATE  90

#define DIN_PIN 15  // D8
#define CS_PIN  13  // D7
#define CLK_PIN 12  // D6

#include "max7219.h"
#include "fonts.h"
#include "func.h"


void setup() {
  Serial.begin(115200);
  initMAX7219();
  sendCmdAll(CMD_SHUTDOWN,1);
}

void loop(){
//   printStringWithShift("lorem ipsum dolor sit amet",20);
//   delay(1500);
//   printStringWithShift("          ",20);

    printStringWithShift("Connecting            ",15);
//   printStringWithShift("consectetur adipiscing elit            ",20);
   delay(1000);
}
