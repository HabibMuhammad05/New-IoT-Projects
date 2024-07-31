#define notsatu 264
#define notdua 297
#define nottiga 330
#define notempat 352
#define notlima 396
#define notenam 440
#define nottujuh 495
#define notdelapan 528

#include "ToneDef.h"

int lagu2[] = {notsatu, notdua, nottiga, notempat, notlima, notenam, nottujuh, notdelapan};
int tempo2[] = {200, 500, 200, 500, 200,500, 200, 500};
int notcount = 7;


bool lagu1stat = false;
bool next = 1;
uint8_t count = 0;
unsigned long pM = 0;

  void la1(){
    int cM = millis();
    if (next && count <= notcount){
      tone(buzpin, lagu2[count], tempo2[count]);
      
      if(cM - pM >= tempo2[count]){
        pM = cM;
        
        if(count <= notcount){
          count++;
          next = true;
        }
      }
    }
    else if (count >= notcount){count = 0; lagu1stat = false;}
  }
  
  void la2(){
    int cM = millis();
    if (next && count <= notcount){
      tone(buzpin, lagu2[count], tempo2[count]);
      
      if(cM - pM >= tempo2[count]){
        pM = cM;
        
        if(count <= notcount){
          count++;
          next = true;
        }
      }
    }
    else if (count >= notcount){count = 0; lagu1stat = false;}
  }




//  void la2(){
//    int cM = millis();
////    Serial.println(cM);
//    
//    if (next && count <=7){
//      tone(buzpin, lagu2[count], tempo2[count]);
//   
//    if(cM - pM >= tempo2[count]){
//      pM = cM;
//      if(count <= 7){
//      count++;
////      Serial.println(count);
//       next = true;
//      }
//      else {next = false; lagu1stat = false; count = 0;}
//    }
//    }
//  }


//  void la2(){
////    while(next){
//    int cM = millis();
////    Serial.println(cM);
//
//    if(cM - pM >= tempo2[count]){
//      pM = cM;
//    
//    if (next && count <=7){
//      tone(buzpin, lagu2[count], tempo2[count]);
//      count++;
//      next = true;
//    }
//    else{next = false;}
//    }
//    else{ noTone(buzpin);}
////  }
//}



//      if(count <= 7){
//      count++;
////      Serial.println(count);
//       next = true;
//      }
//      else {next = false;}
//    }
