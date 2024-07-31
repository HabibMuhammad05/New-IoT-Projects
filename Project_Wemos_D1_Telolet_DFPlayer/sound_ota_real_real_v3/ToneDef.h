
uint8_t buzpin = D0;

void iaiao();
void twinkle();
void bshark();
void sumur();
void basuriV1();
void ale2 ();
void (*functionPtr[])() = { iaiao, twinkle, bshark, sumur, basuriV1, ale2};
//void (*FuncPointer[])() = {iaiao, twinkle, bshark, sumur, basuriV1, ale2};

void satu(int ontime, int off){ 
  tone(buzpin,264,ontime);
  delay(ontime);
  noTone(buzpin);
  delay(off);}
  
void dua(int ontime, int off){ 
  tone(buzpin,297,ontime);
  delay(ontime);
  noTone(buzpin);
  delay(off);}  //Re 
  
void tiga(int ontime, int off){ 
  tone(buzpin,330,ontime);
  delay(ontime);
  noTone(buzpin);
  delay(off);}  //Mi 
  
void empat(int ontime, int off){ 
  tone(buzpin,352,ontime);
  delay(ontime);
  noTone(buzpin);
  delay(off);}  //Fa
  
void lima(int ontime, int off){ 
  tone(buzpin,396,ontime);
  delay(ontime);
  noTone(buzpin);
  delay(off);} //Sol 
  
void enam(int ontime, int off){ 
  tone(buzpin,440,ontime);
  delay(ontime);
  noTone(buzpin);
  delay(off);}  //La
  
void tujuh(int ontime, int off){ 
  tone(buzpin,495,ontime);
  delay(ontime);
  noTone(buzpin);
  delay(off);}  //Si
  
void delapan(int ontime, int off){ 
  tone(buzpin,528,ontime);
  delay(ontime);
  noTone(buzpin);
  delay(off);} //12
  
void notone() { noTone(buzpin); }
