#include "ToneDef.h"
 
void setup(){
  pinMode(8,OUTPUT);
  digitalWrite(8,LOW);

  pinMode(buzpin, OUTPUT);
}

void loop(){
//  bakso();
//  delay(2000);
//  iaiao();
//  delay(2000);
//  twinkle();
//  delay(2000);
//  bshark();
//  delay(2000);
//  sumur();
//  delay(1000);
//  basuriV1();
//  delay(1000);
//  mengular();
//  delay(1000);
  
}void bakso(){
  satu(250,0);satu(250,0);satu(250,0);satu(250,0);dua(350,40);tiga(350,40);tiga(250,0);tiga(250,0);tiga(250,0);tiga(250,0);dua(350,20);satu(350,100); 
  satu(350,20); satu(350,40); satu(350,20); tiga(400,40); satu(400,40); dua(400,0); 
}

void iaiao(){
  empat(300,0);empat(300,0);satu(300,0);satu(300,0);dua(300,0);dua(300,0);satu(500,50);enam(300,0);enam(300,0);lima(300,0);lima(300,0);empat(600,0);
}

void twinkle(){
  dua(300,0);dua(300,0);enam(300,0);enam(300,0);tujuh(300,0);tujuh(300,0);enam(600,30);
  lima(300,0);lima(300,0);empat(300,0);empat(300,0);tiga(300,0);tiga(300,0);dua(600,30);
  enam(300,0);enam(300,0);lima(300,0);lima(300,0);empat(300,0);empat(300,0);tiga(600,30);
  enam(300,0);enam(300,0);lima(300,0);lima(300,0);empat(300,0);empat(300,0);tiga(600,30);
  dua(300,0);dua(300,0);enam(300,0);enam(300,0);tujuh(300,0);tujuh(300,0);enam(600,30);
  lima(300,0);lima(300,0);empat(300,0);empat(300,0);tiga(300,0);tiga(300,0);dua(600,30);
  }

void bshark(){
  dua(500,0);tiga(500,0);lima(250,0); lima(250,0);lima(250,0);lima(125,0);lima(250,0);lima(125,0);lima(250,0);
  dua(250,0);tiga(250,0); lima(250,0);lima(250,0);lima(250,0);lima(125,0);lima(250,0);lima(125,0);lima(250,0);
  dua(250,0);tiga(250,0); lima(250,0);lima(250,0);lima(250,0);lima(125,0);lima(250,0);lima(125,0);lima(250,0);
  lima(250,0);lima(250,0);enam(125,0);
}
void sumur(){
  satu(300,0);satu(300,0);enam(300,0);lima(600,40);empat(300,0);tiga(350,20);dua(400,0);satu(1000,0);
}

void basuriV1(){
  satu(300,0);tiga(300,0);dua(300,0);tiga(300,0);lima(300,0);tiga(300,0);dua(300,0);tiga(300,0);
  satu(300,0);tiga(300,0);dua(300,0);tiga(300,0);lima(300,0);tiga(300,0);dua(300,0);tiga(300,0);
  satu(300,0);tiga(300,0);dua(300,0);tiga(300,0);lima(300,0);tiga(300,0);dua(300,0);tiga(300,0);
  
  
  satu(300,0);satu(300,0);tiga(300,0);tiga(300,0);dua(300,0);dua(300,0);tiga(300,0);tiga(300,0);
  satu(300,0);satu(300,0);tiga(300,0);tiga(300,0);dua(300,0);dua(300,0);tiga(300,0);tiga(300,0);  
}

void mengular (){
  dua(300,0);tiga(300,0);dua(300,0);empat(300,0);dua(300,0);tiga(300,0);satu(300,0);dua(300,0);satu(300,0);tiga(300,0);
  dua(300,0);empat(300,0);dua(300,0);tiga(300,0);satu(300,0);dua(300,0);satu(300,0);tiga(300,0);dua(300,0);
  enam(150,0);lima(150,0);enam(150,0);lima(150,0);enam(150,0);lima(150,0);
  enam(150,0);lima(150,0);enam(150,0);lima(150,0);enam(150,0);lima(150,0);
  empat(300,0);tiga(300,0);satu(300,0);dua(300,0);
  empat(200,0);tiga(200,0);empat(300,0);tiga(150,0);empat(150,0);tiga(300,0);
  
  empat(150,0);tiga(150,0);empat(300,0);tiga(150,0);empat(150,0);tiga(150,0);  dua(300,0);satu(300,0);
}
