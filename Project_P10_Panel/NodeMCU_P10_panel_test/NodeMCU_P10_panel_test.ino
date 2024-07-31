/*
 * Contoh penggunaan library DMDESP
 * 
 * email : bonny@grobak.net - www.grobak.net - www.elektronmart.com  
 * 
 * DejaVuSans9
 * DejaVuSansBold9
 * DejaVuSansItalic9
 * ElektronMart5x6
 * ElektronMart6x8
 * ElektronMart6x12
 * ElektronMart6x16
 * ElektronMartArabic3x6
 * ElektronMartArabic5x6
 * ElektronMartArabic6x16
 * EMKotak5x7
 * EMSans5x6
 * EMSans6x8
 * EMSans6x16
 * EMSans8x16
 * EMSansSP8x16
 * Mono5x7
*/

#include <DMDESP.h>
//#include <fonts/DejaVuSans9.h>
//#include <fonts/DejaVuSansBold9.h>
//#include <fonts/DejaVuSansItalic9.h>
//#include <fonts/ElektronMart5x6.h>
//#include <fonts/ElektronMart6x8.h>
//#include <fonts/ElektronMart6x12.h>
//#include <fonts/ElektronMart6x16.h>
//#include <fonts/ElektronMartArabic3x6.h>
//#include <fonts/ElektronMartArabic5x6.h>
//#include <fonts/ElektronMartArabic6x16.h>
//#include <fonts/EMKotak5x7.h>
#include <fonts/EMSans5x6.h>
//#include <fonts/EMSans6x8.h>
//#include <fonts/EMSans6x16.h>
//#include <fonts/EMSans8x16.h>
#include <fonts/EMSansSP8x16.h>
//#include <fonts/Mono5x7.h>

//SETUP DMD
#define DISPLAYS_WIDE 1 // Kolom Panel
#define DISPLAYS_HIGH 1 // Baris Panel
DMDESP Disp(DISPLAYS_WIDE, DISPLAYS_HIGH);  // Jumlah Panel P10 yang digunakan (KOLOM,BARIS)



//----------------------------------------------------------------------
// SETUP

void setup() {

  // DMDESP Setup
  Disp.start(); // Jalankan library DMDESP
  Disp.setBrightness(15); // Tingkat kecerahan
//  Disp.setFont(EMSansSP8x16); // Tentukan huruf
  
}



//----------------------------------------------------------------------
// LOOP

void loop() {
  Disp.loop(); // Jalankan Disp loop untuk refresh LED
  Disp.setFont(EMSansSP8x16); // Tentukan huruf
  TeksJalan(0, 30); // Tampilkan teks berjalan TeksJalan(posisi y, kecepatan);
//  delay(14900);
//  Disp.drawText(0,0,"          "); // Tampilkan teks
//  delay(1000);
//
//  Disp.setFont(EMSans5x6); // Tentukan huruf
//  Disp.drawText(0,0,"DMDESP"); // Tampilkan teks
//  TeksJalan(7, 50); // Tampilkan teks berjalan TeksJalan(posisi y, kecepatan);
//  delay(14900);
//  Disp.drawText(0,0,"          "); // Tampilkan teks
//  delay(1000);
}


//  Disp.drawText(0,0,"DMDESP"); // Tampilkan teks
//--------------------------
// TAMPILKAN SCROLLING TEKS

static char *teks[] = {"Teks berjalan dengan DMDESP"};

void TeksJalan(int y, uint8_t kecepatan) {

  static uint32_t pM;
  static uint32_t x;
  int width = Disp.width();
//  Disp.setFont(DejaVuSansBold9);
  int fullScroll = Disp.textWidth(teks[0]) + width;
  if((millis() - pM) > kecepatan) { 
    pM = millis();
    if (x < fullScroll) {
      ++x;
    } else {
      x = 0;
      return;
    }
    Disp.drawText(width - x, y, teks[0]);
  }  

}
