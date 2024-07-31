#include <ESP8266WiFi.h>

#include <NTPClient.h>
#include <WiFiUdp.h>
WiFiUDP ntp;
NTPClient timeCli(ntp, "pool.ntp.org");

#include <LiquidCrystal_I2C.h>
#include <BigNumbers_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); 
BigNumbers_I2C bigNum(&lcd);


const char *ssid     = "Sapta 27B";
const char *password = "77777777";

String hari[7]={"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jum'at", "Sabtu"};
String bulan[12]={"Jan", "Feb", "Mar", "Apr", "Mei", "Jun", "Jul", "Agt", "Sep", "Okt", "Nov", "Des"};
int detik, menit, jam;

void setup() { 
  Serial.begin(115200);
  lcd.begin(); 
  bigNum.begin(); 
  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("WiFi Check...");
  Serial.print("Connecting WiFi ");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);}
  Serial.println("");
  Serial.print("Connected: "); Serial.println(WiFi.localIP());
  lcd.setCursor(0, 0); lcd.print("WiFi OK     ");
  
  Serial.println("Getting data ...");
  timeCli.begin();
  timeCli.setTimeOffset(25200); //zona waktu=WIB=GMT+7=7*(60*60)
  Serial.println("Data loaded");
  lcd.setCursor(0, 1); lcd.print(WiFi.localIP());
  delay(2000);
  lcd.clear();
  
}

void loop() {
  timeCli.update();
  time_t epochTime = timeCli.getEpochTime(); 
  String hariseminggu = hari[timeCli.getDay()];  
  //Mendapatkan tanggal dari Epoch Time
  struct tm *ptm = gmtime ((time_t *)&epochTime); 
  int tanggal = ptm->tm_mday;
  int angkabulan = ptm->tm_mon+1;
  String bulansetahun = bulan[angkabulan-1];
  //Menampilkan 2 digit terakhir dari tahun
  int tahun = (ptm->tm_year+1900)-2000; 
  String tanggalsekarang = String(hariseminggu)+","+ String(tanggal)+ " " + String(bulansetahun)+" "+String(tahun);
 
  //Menampilkan jam sekarang
  String jamsekarang = timeCli.getFormattedTime();
  detik = timeCli.getSeconds();
  menit = timeCli.getMinutes();
  jam = timeCli.getHours();

  if (detik >20 && detik <30){
    lcd.setCursor(0, 0);
    lcd.print("    ");
    lcd.setCursor(4, 0);
    lcd.print(jamsekarang);
    lcd.setCursor(12, 0);
    lcd.print("    ");
    
    lcd.setCursor(0, 1);
    lcd.print(tanggalsekarang);
  }
  
  else{
    if (detik %2 == 0) { lcd.setCursor(6, 1); lcd.print(" "); lcd.setCursor(6, 0); lcd.print(":"); }
    else { lcd.setCursor(6, 0); lcd.print(" ");  lcd.setCursor(6, 1); lcd.print(":"); }
    
    bigNum.displayLargeInt(jam, 0, 0, 2, false);
    bigNum.displayLargeInt(menit, 7, 0, 2, false);
    lcd.setCursor(13, 1); lcd.print((detik < 10 ? "0" : "") + String(detik));
    lcd.setCursor(14, 0); lcd.print((jam < 13 ? "AM" : "PM"));
  }
}
