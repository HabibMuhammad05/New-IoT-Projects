#include <LiquidCrystal_I2C.h> 
#include <BigNumbers_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4); 
BigNumbers_I2C bigNum(&lcd);

unsigned long waktu1=0;
bool dig = true;
void setup()
{
  lcd.begin(); 
  bigNum.begin(); 
  lcd.clear();
}

void loop()
{
  if(millis()-waktu1>= 1000){ dig = !dig; waktu1=millis(); }
  if(dig){  lcd.setCursor(6, 1); lcd.print(" "); lcd.setCursor(6, 0); lcd.print(":"); }
  else{ lcd.setCursor(6, 0); lcd.print(" ");  lcd.setCursor(6, 1); lcd.print(":");}

  
  bigNum.displayLargeInt(26, 0, 0, 2, false);
  bigNum.displayLargeInt(26, 7, 0, 2, false);
  lcd.setCursor(13, 1); lcd.print("26");
  lcd.setCursor(14, 0); lcd.print("PM");
}
