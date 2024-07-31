void WiFiConfig(){
    if ( digitalRead(WiFiPB) == LOW){
    WiFiManager wm;    
    wm.setConfigPortalTimeout(120);
      if (!wm.startConfigPortal("ESP8266_WiFi_Config")) {
        Serial.println("failed to connect and hit timeout");
        delay(3000);
        ESP.restart();
        delay(5000);}
    Serial.println("WiFi Connected");}
}
bool onPowerState(const String &deviceId, bool &state) {
  Serial.printf("Temperaturesensor turned %s (via SinricPro) \r\n", state?"on":"off");
  deviceIsOn = state;
  return true; 
}
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
    digitalWrite(wifiLed, LOW);
    sended++;
    Serial.print("Total Package Sent="); Serial.println(sended);} 
  else { 
    Serial.printf("Something went wrong...could not send Event to server!\r\n");
    digitalWrite(wifiLed, HIGH);
    delay(500);
    digitalWrite(wifiLed, LOW);
    error++;
    Serial.print("Total Package Error="); Serial.println(error);}
  lastTemperature = temperature;
  lastHumidity = humidity;    
  lastEvent = actualMillis; 
}
void setupWiFi() {
  Serial.printf("\r\n[Wifi]: Connecting");
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.printf(".");
    delay(250);}
  IPAddress localIP = WiFi.localIP();
  Serial.printf("connected!\r\n[WiFi]: IP-Address is %d.%d.%d.%d\r\n", localIP[0], localIP[1], localIP[2], localIP[3]);
}
void setupSinricPro() {
  SinricProTemperaturesensor &mySensor = SinricPro[TEMP_SENSOR_ID];
  mySensor.onPowerState(onPowerState);
  SinricPro.onConnected([](){ Serial.printf("Connected to SinricPro\r\n"); digitalWrite(wifiLed, LOW); }); 
  SinricPro.onDisconnected([](){ Serial.printf("Disconnected from SinricPro\r\n"); digitalWrite(wifiLed, HIGH); });
  SinricPro.restoreDeviceStates(true);
  SinricPro.begin(APP_KEY, APP_SECRET);  
}
