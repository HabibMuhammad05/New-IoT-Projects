typedef struct {     
  int relayPIN;
  int flipSwitchPIN;
} deviceConfig_t;

std::map<String, deviceConfig_t> devices = {
    {device_ID_1, {  RelayPin1, SwitchPin1 }},
    {device_ID_2, {  RelayPin2, SwitchPin2 }},  
};

typedef struct {    
  String deviceId;
  bool lastFlipSwitchState;
  unsigned long lastFlipSwitchChange;
} flipSwitchConfig_t;

std::map<int, flipSwitchConfig_t> flipSwitches;    

//--------------------------------SetupWifi()--------------------------------//
void setupWiFi(){
  Serial.printf("\r\n[Wifi]: Connecting");
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.printf(".");
    delay(250);
  }
  digitalWrite(wifiLed, LOW);
  Serial.printf("connected!\r\n[WiFi]: IP-Address is %s\r\n", WiFi.localIP().toString().c_str());
}
//--------------------------------onpowerState()--------------------------------//                                                  
bool onPowerState(String deviceId, bool &state){
  Serial.printf("%s: %s\r\n", deviceId.c_str(), state ? "on" : "off");
  int relayPIN = devices[deviceId].relayPIN; 
  digitalWrite(relayPIN, !state);            
  return true;
}
//------------------------------DHTOnPowerState()-------------------------------//
bool DHTonPowerState(const String &DHTdeviceId, bool &DHTstate) {
  Serial.printf("Temperature sensor turned %s (via SinricPro) \r\n", DHTstate?"on":"off");
  deviceIsOn = DHTstate;
  return true; 
}
//--------------------------------SetupRelays()--------------------------------//                                                  
void setupRelays() { 
  for (auto &device : devices) {           
    int relayPIN = device.second.relayPIN; 
    pinMode(relayPIN, OUTPUT);             
    digitalWrite(relayPIN,HIGH);
  }
}
//--------------------------------SetupFlipswitches()--------------------------------//
void setupFlipSwitches() {
  for (auto &device : devices)  {                     
    flipSwitchConfig_t flipSwitchConfig;              

    flipSwitchConfig.deviceId = device.first;         
    flipSwitchConfig.lastFlipSwitchChange = 0;       
    flipSwitchConfig.lastFlipSwitchState = true;   // set lastFlipSwitchState to false (LOW)

    int flipSwitchPIN = device.second.flipSwitchPIN;  

    flipSwitches[flipSwitchPIN] = flipSwitchConfig;  
    pinMode(flipSwitchPIN, INPUT_PULLUP);                   
  }
}
//--------------------------------handleFlipSwitches()--------------------------------//
void handleFlipSwitches() {
  unsigned long actualMillis = millis();                                         
  for (auto &flipSwitch : flipSwitches) {                                         
    unsigned long lastFlipSwitchChange = flipSwitch.second.lastFlipSwitchChange;  

    if (actualMillis - lastFlipSwitchChange > DEBOUNCE_TIME) {                    

      int flipSwitchPIN = flipSwitch.first;                                      
      bool lastFlipSwitchState = flipSwitch.second.lastFlipSwitchState;           
      bool flipSwitchState = digitalRead(flipSwitchPIN);                          
      if (flipSwitchState != lastFlipSwitchState) {                               
#ifdef TACTILE_BUTTON
        if (flipSwitchState) {                                                   
#endif      
          flipSwitch.second.lastFlipSwitchChange = actualMillis;                  
          String deviceId = flipSwitch.second.deviceId;                           
          int relayPIN = devices[deviceId].relayPIN;                              
          bool newRelayState = !digitalRead(relayPIN);                            
          digitalWrite(relayPIN, newRelayState);                                  

          SinricProSwitch &mySwitch = SinricPro[deviceId];                        
          mySwitch.sendPowerStateEvent(!newRelayState); 
                                     
#ifdef TACTILE_BUTTON
        }
#endif      
        flipSwitch.second.lastFlipSwitchState = flipSwitchState;                  
      }
    }
  }
}
//--------------------------------SetupSinricPro()--------------------------------//
void setupSinricPro()
{
  for (auto &device : devices)
  {
    const char *deviceId = device.first.c_str();
    SinricProSwitch &mySwitch = SinricPro[deviceId];
    mySwitch.onPowerState(onPowerState);
  }

  SinricPro.restoreDeviceStates(true);
}
//--------------------------------SetupSinricProtemp()--------------------------------//
void setupSinricProTemp() {
  SinricProTemperaturesensor &mySensor = SinricPro[TEMP_SENSOR_ID];
  mySensor.onPowerState(DHTonPowerState);
  SinricPro.onConnected([](){ Serial.printf("Connected to SinricPro\r\n"); digitalWrite(wifiLed, LOW); }); 
  SinricPro.onDisconnected([](){ Serial.printf("Disconnected from SinricPro\r\n"); digitalWrite(wifiLed, HIGH); });
  SinricPro.restoreDeviceStates(true); 
  SinricPro.begin(APP_KEY, APP_SECRET);
}
//--------------------------------handleTemperaturesensor()--------------------------------//
void handleTemperaturesensor() {
  if (deviceIsOn == false) return;
  unsigned long DHTactualMillis = millis();
  if (DHTactualMillis - lastEvent < EVENT_WAIT_TIME) return;
float  temperature = dht.readTemperature();  
float  humidity = dht.readHumidity();           
  if (isnan(temperature) || isnan(humidity)) {
    Serial.printf("DHT reading failed!\r\n"); 
    digitalWrite(wifiLed, HIGH);
    delay(50);
    digitalWrite(wifiLed, LOW);
    return;} 
  //if (temperature == lastTemperature || humidity == lastHumidity) return;
  SinricProTemperaturesensor &mySensor = SinricPro[TEMP_SENSOR_ID]; 
  bool success = mySensor.sendTemperatureEvent(temperature, humidity);
  if (success) {
    Serial.printf("Temperature: %2.1f Celsius\tHumidity: %2.1f%%\r\n", temperature, humidity);
    digitalWrite(wifiLed, HIGH);
    delay(50);
    digitalWrite(wifiLed, LOW);
    delay(100);
    digitalWrite(wifiLed, HIGH);
    delay(50);
    digitalWrite(wifiLed, LOW);}
  else { 
    Serial.printf("Something went wrong...could not send Event to server!\r\n");
    digitalWrite(wifiLed, HIGH);
    delay(500);
    digitalWrite(wifiLed, LOW);}
  lastEvent = DHTactualMillis; 
}
//--------------Soil Moisture Sensor Data Sending-----------------//
void SoilMoisture_Send(){
  float lembab = ( 100.00 - ( (analogRead(A0)/1024.00) * 100.00 ) );
  float teg = analogRead(A0);
  teg = map(teg, 0, 1024, 1024,0);
  float tegangan = ( 5.00 - ( (teg/1024.00) * 5.00 ) );
  Serial.print("Soil Moisture = "); 
  Serial.print(lembab); Serial.print("% - ");
  Serial.print(tegangan); Serial.println("V");
  
  Blynk.virtualWrite(V7, lembab);
  Blynk.virtualWrite(V8, tegangan);
}

//----------------------DHT11 Data Sending------------------------//
void DHT11_Send(){
   temp = dht.readTemperature();
   humid = dht.readHumidity();
  
   if (isnan(temp) || isnan(humid)) {
     Serial.println("Pembacaan DHT error!");
     return; }
     
  Serial.print("--------DHT11 = "); 
  Serial.print(temp); Serial.print("°c - ");
  Serial.print(humid); Serial.println("%");
  
  Blynk.virtualWrite(V5, temp);
  Blynk.virtualWrite(V6, humid);
} 

void ardudataRead(){
  dataIn = arduinoConnect.readString();
  dataIn.trim();
  Serial.println(dataIn); 
  int hasildata = dataIn.toInt();

  if (hasildata >= 2000 && hasildata <= 3023){
    int VoltDataIn = hasildata;
    VoltDataIn = VoltDataIn - 2000;
    Serial.print("Volt in = "); Serial.println(VoltDataIn);
     
    float voltage = VoltDataIn * (6.13/880);
    Serial.print("volt= "); Serial.println(voltage);
    
    Blynk.virtualWrite(V10, voltage);
  }

  if (hasildata >= 4000 && hasildata <= 5023){
    int LightDataIn = hasildata;
    LightDataIn = LightDataIn - 4000;
    Serial.print("llght in = "); Serial.println(LightDataIn);
     
    int LightDataCalc = map(LightDataIn, 130, 950, 0, 1023);
    Serial.print("light= "); Serial.println(LightDataCalc);
        
    Blynk.virtualWrite(V11, LightDataCalc);
  }
}
