#include <SPI.h>
#include <DMD.h>
#include <TimerOne.h>
#include "Arial_black_16.h"
#include "Arial_Black_16_ISO_8859_1.h"
#include "Arial14.h"
#include "SystemFont5x7.h"

#define DISPLAYS_ACROSS 1 //-> Number of P10 panels used, side to side.
#define DISPLAYS_DOWN 1
DMD dmd(DISPLAYS_ACROSS, DISPLAYS_DOWN);

char *Text = "";

void ScanDMD() {
  dmd.scanDisplayBySPI();
}

void setup() {
  Timer1.initialize(1000);
  Timer1.attachInterrupt(ScanDMD);
  dmd.clearScreen(true);

}

void loop() {
  //    dmd.selectFont(Arial_14);
  //    dmd.selectFont(SystemFont5x7);
//  dmd.selectFont(Arial_Black_16);
  //    dmd.selectFont(Arial_Black_16_ISO_8859_1);
  //  dmd.drawString(2,0, "hello!", 5, GRAPHICS_NORMAL);
  //  dmd.drawString(1,9, "11:15", 5, GRAPHICS_NORMAL);
  //  delay(1000);
//  for (int i = 0; i <= 4; i++) {
//    dmd.drawString(0, 0, "lorem", 5, GRAPHICS_TOGGLE);
//    delay(500);
//  }
//  gambar_masjid();
//  delay(2000);
//dmd.drawLine(31, 1, 31, 14, GRAPHICS_INVERSE);
//dmd.drawLine(0, 0, 31, 0, GRAPHICS_INVERSE);
//dmd.drawLine(0, 15, 31, 15, GRAPHICS_INVERSE);
dmd.clearScreen(true);
dmd.drawBox(0, 0, 31, 15, GRAPHICS_NORMAL);
dmd.drawBox(2, 2, 29, 13, GRAPHICS_NORMAL);
dmd.drawBox(4, 4, 27, 11, GRAPHICS_NORMAL);
dmd.drawBox(6, 6, 25, 9, GRAPHICS_NORMAL);
delay(200);
dmd.clearScreen(true);
dmd.drawBox(1, 1, 30, 14, GRAPHICS_NORMAL);
dmd.drawBox(3, 3, 28, 12, GRAPHICS_NORMAL);
dmd.drawBox(5, 5, 26, 10, GRAPHICS_NORMAL);
dmd.drawBox(7, 7, 24, 8, GRAPHICS_NORMAL);
delay(150);
//dmd.drawBox(1, 1, 30, 14, GRAPHICS_NOR);
//dmd.drawBox(3, 3, 28, 12, GRAPHICS_NOR);
//dmd.drawBox(5, 5, 26, 10, GRAPHICS_NOR);
//dmd.drawBox(7, 7, 24, 8, GRAPHICS_NOR);
//delay(1000);



//dmd.drawBox(4, 4, 27, 11, GRAPHICS_NOR);
}

void gambar_masjid() {
  int GRAPHICS_ON = GRAPHICS_NORMAL;
  dmd.clearScreen(true);
  //dmd.drawBox(32,0,63,15,GRAPHICS_ON);
  //gambar masjid
  //kiri
  dmd.drawLine(0, 6, 0, 6, GRAPHICS_NORMAL);
  dmd.drawLine(1, 5, 1, 15, GRAPHICS_ON);
  dmd.drawLine(2, 0, 2, 13, GRAPHICS_ON);
  dmd.drawLine(3, 5, 3, 15, GRAPHICS_ON);
  dmd.drawLine(4, 6, 4, 6, GRAPHICS_ON);
  //tengah

  dmd.drawLine(15, 0, 15, 0, GRAPHICS_ON);
  dmd.drawLine(14, 1, 16, 1, GRAPHICS_ON);
  dmd.drawLine(13, 2, 17, 2, GRAPHICS_ON);
  dmd.drawLine(12, 3, 18, 3, GRAPHICS_ON);
  dmd.drawLine(11, 4, 19, 4, GRAPHICS_ON);
  dmd.drawLine(11, 5, 19, 5, GRAPHICS_ON);
  dmd.drawLine(12, 6, 18, 6, GRAPHICS_ON);
  dmd.drawLine(13, 7, 17, 7, GRAPHICS_ON);
  dmd.drawLine(5, 8, 25, 8, GRAPHICS_ON);
  dmd.drawLine(5, 10, 25, 10, GRAPHICS_ON);
  dmd.drawLine(5, 11, 7, 11, GRAPHICS_ON); dmd.drawLine(9, 11, 14, 11, GRAPHICS_ON); dmd.drawLine(16, 11, 21, 11, GRAPHICS_ON); dmd.drawLine(23, 11, 25, 11, GRAPHICS_ON);
  dmd.drawLine(5, 12, 6, 12, GRAPHICS_ON); dmd.drawLine(10, 12, 13, 12, GRAPHICS_ON); dmd.drawLine(17, 12, 20, 12, GRAPHICS_ON); dmd.drawLine(24, 12, 25, 12, GRAPHICS_ON);
  dmd.drawLine(5, 13, 6, 13, GRAPHICS_ON); dmd.drawLine(10, 13, 13, 13, GRAPHICS_ON); dmd.drawLine(17, 13, 20, 13, GRAPHICS_ON); dmd.drawLine(24, 13, 25, 13, GRAPHICS_ON);
  dmd.drawLine(5, 14, 6, 14, GRAPHICS_ON); dmd.drawLine(10, 14, 13, 14, GRAPHICS_ON); dmd.drawLine(17, 14, 20, 14, GRAPHICS_ON); dmd.drawLine(24, 14, 25, 14, GRAPHICS_ON);
  dmd.drawLine(5, 15, 25, 15, GRAPHICS_ON);
  //kanan
  dmd.drawLine(26, 6, 26, 6, GRAPHICS_ON);
  dmd.drawLine(27, 5, 27, 15, GRAPHICS_ON);
  dmd.drawLine(28, 0, 28, 13, GRAPHICS_ON);
  dmd.drawLine(29, 5, 29, 15, GRAPHICS_ON);
  dmd.drawLine(30, 6, 30, 6, GRAPHICS_ON);
  delay(2000);
  dmd.clearScreen(true);
}
