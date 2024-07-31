//master
#include<esp_now.h>
#include<WiFi.h>

uint8_t pb[4]={13, 25, 33, 32};
//bool r[4]={false,false,false,false}; 
uint8_t broadcastAddress[]={0xCC,0x50,0xE3,0xF0,0x1E,0x36};

uint8_t LED2=27;
uint8_t LED3=14;
uint8_t LED4=26;

typedef struct Pesan{
  bool e = false;
  bool f = true;
  bool g = false;
  bool h = true;
//  bool rs[4];
}Pesan;

Pesan pesan;

esp_now_peer_info_t slave;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status){
  Serial.print("\r\nStatus terakhir:\t");
  Serial.println(status==ESP_NOW_SEND_SUCCESS?"Terkirim":"Gagal");
}

void setup(){
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  
  for(int i=0; i<4; i++) pinMode(pb[i],INPUT_PULLUP);
  WiFi.mode(WIFI_STA);
  if(esp_now_init()!=ESP_OK){
    Serial.println("ESPNow Gagal!");
    return;
  }
  esp_now_register_send_cb(OnDataSent);
  memcpy(slave.peer_addr, broadcastAddress, 6);
  slave.channel = 0;  
  slave.encrypt = false;       
  if(esp_now_add_peer(&slave) != ESP_OK){
    Serial.println("Gagal menambahkan slave!");
    return;
  }
}

void loop(){
  cekButton();
}

void cekButton(){
  for(int i=0; i<4; i++){
    if((!digitalRead(pb[i]))){
      while(!digitalRead(pb[i]));
      delay(100);
//      r[i]=!r[i];
      
      pesan.e = !pesan.e;
      digitalWrite(LED2, pesan.e);
      
      pesan.f = !pesan.f;
      digitalWrite(LED3, pesan.f);
      
      pesan.g = !pesan.g;
      digitalWrite(LED_BUILTIN, pesan.g);
      
      pesan.h = !pesan.h;
      digitalWrite(LED4, pesan.h);
      
      esp_err_t result=esp_now_send(broadcastAddress,(uint8_t *)&pesan,sizeof(pesan));
    }
  }
}
