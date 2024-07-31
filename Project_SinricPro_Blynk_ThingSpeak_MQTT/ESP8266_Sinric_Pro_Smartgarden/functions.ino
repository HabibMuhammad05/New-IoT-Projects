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
  Serial.printf("Temperaturesensor turned %s (via SinricPro) \r\n", state?"on":"off");
  Serial.printf("%s: %s\r\n", deviceId.c_str(), state ? "on" : "off");
  int relayPIN = devices[deviceId].relayPIN; 
  digitalWrite(relayPIN, !state);            
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

  SinricPro.begin(APP_KEY, APP_SECRET);
  SinricPro.restoreDeviceStates(true);
}
//--------------------------------SetupSinricProtemp()--------------------------------//
void setupSinricProTemp() {
  SinricProTemperaturesensor &mySensor = SinricPro[TEMP_SENSOR_ID];
  mySensor.onPowerState(onPowerState);
  SinricPro.onConnected([](){ Serial.printf("Connected to SinricPro\r\n"); digitalWrite(wifiLed, LOW); }); 
  SinricPro.onDisconnected([](){ Serial.printf("Disconnected from SinricPro\r\n"); digitalWrite(wifiLed, HIGH); });
  SinricPro.restoreDeviceStates(true);
  SinricPro.begin(APP_KEY, APP_SECRET);  
}
//--------------------------------handleTemperaturesensor()--------------------------------//
void handleTemperaturesensor() {
  if (deviceIsOn == false) return;
  unsigned long actualMillis = millis();
  if (actualMillis - lastEvent < EVENT_WAIT_TIME) return;
  temperature = dht.readTemperature();  
  humidity = dht.readHumidity();           
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
  lastTemperature = temperature;
  lastHumidity = humidity;    
  lastEvent = actualMillis; 
}
