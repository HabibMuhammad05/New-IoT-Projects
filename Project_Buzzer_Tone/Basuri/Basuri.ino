/*************************************
 * Program : Project 52. Keyboard piano
 * Input   : 8 Tombol push
 * Output  : BUZZER
 * 125 Proyek Arduino Inkubatek
 * www.tokotronik.com
 * ***********************************/
#include "ToneDef.h"
 
void setup(){
  pinMode(8,OUTPUT);
  digitalWrite(8,LOW);

  pinMode(buzpin, OUTPUT);
}

void loop(){
//  ketiga();
//  delay(2000);
//  kedua();
//  delay(2000);
  kesatu();
  delay(2000);
  
//  bshark();
//  delay(2000);
//sumur();
//delay(1000);
//basuriV1();
//delay(1000);
//ale2();
//delay(1000);
  
}
void ketiga(){
  empat(300,0);empat(300,0);satu(300,0);satu(300,0);dua(300,0);dua(300,0);satu(500,50);enam(300,0);enam(300,0);lima(300,0);lima(300,0);empat(600,0);
}

void kedua(){
  tiga(200,0);tiga(300,0);dua(200,0);dua(300,0);satu(200,0);satu(300,0);satu(200,0);satu(300,0);
  tiga(200,0);tiga(300,0);lima(200,0);enam(300,0);tiga(200,0);tiga(300,0);tiga(200,0);satu(300,0);
}

void kesatu(){
  satu(300,0);satu(300,0);lima(300,0);lima(300,0);enam(300,0);enam(300,0);lima(600,50);
  empat(300,0);empat(300,0);tiga(300,0);tiga(300,0);dua(300,0);dua(300,0);satu(600,0);
}

void bshark(){
  dua(600,0);tiga(600,10);lima(200,0); lima(300,30);lima(100,0);lima(100,20);lima(100,0);lima(200,200);
}
void sumur(){
  satu(300,0);satu(300,0);enam(300,0);lima(600,200);empat(300,50);tiga(300,50);dua(500,50);satu(1000,0);
}

void basuriV1(){
  satu(300,0);tiga(300,0);dua(300,0);tiga(300,0);lima(300,0);tiga(300,0);dua(300,0);tiga(300,0);
  satu(300,0);tiga(300,0);dua(300,0);tiga(300,0);lima(300,0);tiga(300,0);dua(300,0);tiga(300,0);
  satu(300,0);tiga(300,0);dua(300,0);tiga(300,0);lima(300,0);tiga(300,0);dua(300,0);tiga(300,0);
  
  
  satu(300,0);satu(300,0);tiga(300,0);tiga(300,0);dua(300,0);dua(300,0);tiga(300,0);tiga(300,0);
  satu(300,0);satu(300,0);tiga(300,0);tiga(300,0);dua(300,0);dua(300,0);tiga(300,0);tiga(300,0);  
}

void ale2 (){
  dua(300,0);tiga(300,0);dua(300,0);empat(300,0);dua(300,0);tiga(300,0);satu(300,0);dua(300,0);satu(300,0);tiga(300,0);
  dua(300,0);empat(300,0);dua(300,0);tiga(300,0);satu(300,0);dua(300,0);satu(300,0);tiga(300,0);dua(300,0);
  enam(150,0);lima(150,0);enam(150,0);lima(150,0);enam(150,0);lima(150,0);
  enam(150,0);lima(150,0);enam(150,0);lima(150,0);enam(150,0);lima(150,0);
  empat(300,0);tiga(300,0);satu(300,0);dua(300,0);
  empat(200,0);tiga(200,0);empat(300,0);tiga(150,0);empat(150,0);tiga(300,0);
  
  empat(150,0);tiga(150,0);empat(300,0);tiga(150,0);empat(150,0);tiga(150,0);  dua(300,0);satu(300,0);
}
