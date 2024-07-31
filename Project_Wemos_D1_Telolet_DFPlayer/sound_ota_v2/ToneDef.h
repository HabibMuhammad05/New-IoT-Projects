 uint8_t buzpin = 16;

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
