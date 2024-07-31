#include <ESP8266WiFi.h>

#include <NTPClient.h>
#include <WiFiUdp.h>

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");
unsigned long Epoch_Time; 

WiFiClient client;
String date;

#include <LiquidCrystal_I2C.h>
#include <BigNumbers_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); 
BigNumbers_I2C bigNum(&lcd);


const char *ssid     = "Sapta 27B";
const char *password = "77777777";
float utcOffset = 7; // Time Zone setting

String hari[7]={"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jum'at", "Sabtu"};
String bulan[12]={"Jan", "Feb", "Mar", "Apr", "Mei", "Jun", "Jul", "Agt", "Sep", "Okt", "Nov", "Des"};
int detik, menit, jam;
int updCnt = 0;
long clkTime = 0;
int h,m,s;
long localEpoc = 0;
long localMillisAtUpdate = 0;

void setup() { 
  Serial.begin(115200);
  timeClient.begin();
  lcd.begin(); 
  bigNum.begin(); 
  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("WiFi Check...");
  
  Serial.print("Connecting WiFi ");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { Serial.print("."); delay(500);}
  
  Serial.println("");
  Serial.print("Connected: "); Serial.println(WiFi.localIP());
  lcd.setCursor(0, 0); lcd.print("WiFi OK     ");
  delay(500);
  lcd.clear();
  
  if(updCnt<=0) {
    updCnt = 10;
    Serial.println("Getting data ...");
    lcd.setCursor(0, 0); lcd.print("Getting Data     ");
    getTime();
    Serial.println("Data loaded");
    lcd.setCursor(0, 1); lcd.print("Data OK       ");
    clkTime = millis();
  }
  
  delay(2000);
//  WiFi.disconnect();
  Serial.println("wifi Disconnect Success");  
}

void loop() {
//  timeCli.update();
//  time_t epochTime = timeCli.getEpochTime(); 
//  String hariseminggu = hari[timeCli.getDay()];  
//  //Mendapatkan tanggal dari Epoch Time
//  struct tm *ptm = gmtime ((time_t *)&epochTime); 
//  int tanggal = ptm->tm_mday;
//  int angkabulan = ptm->tm_mon+1;
//  String bulansetahun = bulan[angkabulan-1];
//  //Menampilkan 2 digit terakhir dari tahun
//  int tahun = (ptm->tm_year+1900)-2000; 
//  String tanggalsekarang = String(hariseminggu)+","+ String(tanggal)+ " " + String(bulansetahun)+" "+String(tahun);
 
  if (s >20 && s <30){
    lcd.setCursor(0, 0); lcd.print("    "); lcd.setCursor(4, 0); lcd.print(String(h) + ":" + String(m) + ":" + String(s));
    lcd.setCursor(12, 0); lcd.print("    "); lcd.setCursor(0, 1); lcd.print(date);
  }
  
  else{
    if (s %2 == 0) { lcd.setCursor(6, 1); lcd.print(" "); lcd.setCursor(6, 0); lcd.print(":"); }
    else { lcd.setCursor(6, 0); lcd.print(" ");  lcd.setCursor(6, 1); lcd.print(":"); }
    
    bigNum.displayLargeInt(h, 0, 0, 2, false);
    bigNum.displayLargeInt(m, 7, 0, 2, false);
    lcd.setCursor(13, 1); lcd.print((s < 10 ? "0" : "") + String(s));
    lcd.setCursor(14, 0); lcd.print((h < 13 ? "AM" : "PM"));
  }
  
  updateTime();
  if ((h = 24) && (m = 0) && (s = 0)){ ESP.restart(); }
  
}

void getTime()
{
  WiFiClient client;
  if (!client.connect("www.google.com", 80)) {
    Serial.println("connection to google failed");
    return;
  }

  client.print(String("GET / HTTP/1.1\r\n") +
               String("Host: www.google.com\r\n") +
               String("Connection: close\r\n\r\n"));
  int repeatCounter = 0;
  while (!client.available() && repeatCounter < 10) {
    delay(500);
    //Serial.println(".");
    repeatCounter++;
    
  }

  String line;
  client.setNoDelay(false);
  while(client.connected() && client.available()) {
    line = client.readStringUntil('\n');
    line.toUpperCase();
    if (line.startsWith("DATE: ")) {
      date = "     "+line.substring(6, 22);
      Serial.println(line.substring(6,36));
//      arduinoConnect.println(line.substring(6,36));
//      h = line.substring(23, 25).toInt();
//      m = line.substring(26, 28).toInt();
//      s = line.substring(29, 31).toInt();

      localMillisAtUpdate = millis();
      localEpoc = (h * 60 * 60 + m * 60 + s);
    }
    timeClient.update();
    Epoch_Time = timeClient.getEpochTime()+ 3;
    Serial.println(Epoch_Time);
//    arduinoConnect.println("T"+String(Epoch_Time));
  }
  client.stop();
}

void updateTime()
{
  long curEpoch = localEpoc + ((millis() - localMillisAtUpdate) / 1000);
  long epoch = fmod(round(curEpoch + 3600 * utcOffset + 86400L), 86400L);
//  h = ((epoch  % 86400L) / 3600) % 24;
//  m = (epoch % 3600) / 60;
//  s = epoch % 60;  

      h = timeClient.getHours();;
      m = timeClient.getMinutes();;
      s = timeClient.getSeconds();;
//  Serial.print("T"); Serial.println(localEpoc);
}
