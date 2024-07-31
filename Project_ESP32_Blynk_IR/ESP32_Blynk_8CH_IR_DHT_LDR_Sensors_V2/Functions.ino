
//-----------------------------------------------------------------------------//
//-----------------------------------------------------------------------------//
//-----------------------------------Functions---------------------------------//
//-----------------------------------------------------------------------------//
//-----------------------------------------------------------------------------//


//--------------------------------IR Remote Func.------------------------------//
void ir_remote(){
  if (irrecv.decode(&results)) {
      switch(results.value){
          case 0x80BF49B6:  
            digitalWrite(RelayPin1, toggleState_1);
            toggleState_1 = !toggleState_1;
            Blynk.virtualWrite(VPIN_BUTTON_1, toggleState_1);
            delay(100);            
            break;
          case 0x80BFC936:  
            digitalWrite(RelayPin2, toggleState_2);
            toggleState_2 = !toggleState_2;
            Blynk.virtualWrite(VPIN_BUTTON_2, toggleState_2);
            delay(100);            
            break;
          case 0x80BF33CC:  
            digitalWrite(RelayPin3, toggleState_3);
            toggleState_3 = !toggleState_3;
            Blynk.virtualWrite(VPIN_BUTTON_3, toggleState_3);
            delay(100);            
            break;
          case 0x80BF718E:  
            digitalWrite(RelayPin4, toggleState_4);
            toggleState_4 = !toggleState_4;
            Blynk.virtualWrite(VPIN_BUTTON_4, toggleState_4);
            delay(100);            
            break;
          case 0x80BFF10E:  
            digitalWrite(RelayPin5, toggleState_5);
            toggleState_5 = !toggleState_5;
            Blynk.virtualWrite(VPIN_BUTTON_5, toggleState_5);
            delay(100);            
            break;
          case 0x80BF13EC:  
            digitalWrite(RelayPin6, toggleState_6);
            toggleState_6 = !toggleState_6;
            Blynk.virtualWrite(VPIN_BUTTON_6, toggleState_6);
            delay(100);            
            break;
          case 0x80BF51AE:  
            digitalWrite(RelayPin7, toggleState_7);
            toggleState_7 = !toggleState_7;
            Blynk.virtualWrite(VPIN_BUTTON_7, toggleState_7);
            delay(100);            
            break;
          case 0x80BFD12E:  
            digitalWrite(RelayPin8, toggleState_8);
            toggleState_8 = !toggleState_8;
            Blynk.virtualWrite(VPIN_BUTTON_8, toggleState_8);
            delay(100);            
            break;  
          default : break;         
        }   
        Serial.println(results.value, HEX);    
        irrecv.resume();   
  } 
}

//--------------------------DHT Read Sensor Func.----------------------------//
void readSensor(){
    
  ldrVal = map(analogRead(LDR_PIN), 0, 4095, 10, 0);
  
  float h = dht.readHumidity();
  float t = dht.readTemperature(); 
  
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  else {
    humidity1 = h;
    temperature1 = t;
    Serial.println(temperature1);
    Serial.println(ldrVal);
  }  
}

//----------------------All Sensor Data Sending Func.------------------------//
void sendSensor(){
  readSensor();
  Blynk.virtualWrite(VPIN_HUMIDITY, humidity1);
  Blynk.virtualWrite(VPIN_TEMPERATURE, temperature1);
  Blynk.virtualWrite(VPIN_LDR, ldrVal);
}

//--------------------Blynk Switch 1 Data Sending Func.----------------------//
BLYNK_WRITE(VPIN_BUTTON_1) {
  toggleState_1 = param.asInt();
  if(toggleState_1 == 1){
    digitalWrite(RelayPin1, LOW);
  }
  else { 
    digitalWrite(RelayPin1, HIGH);
  }
}

//--------------------Blynk Switch 2 Data Sending Func.----------------------//
BLYNK_WRITE(VPIN_BUTTON_2) {
  toggleState_2 = param.asInt();
  if(toggleState_2 == 1){
    digitalWrite(RelayPin2, LOW);
  }
  else { 
    digitalWrite(RelayPin2, HIGH);
  }
}

//--------------------Blynk Switch 3 Data Sending Func.----------------------//
BLYNK_WRITE(VPIN_BUTTON_3) {
  toggleState_3 = param.asInt();
  if(toggleState_3 == 1){
    digitalWrite(RelayPin3, LOW);
  }
  else { 
    digitalWrite(RelayPin3, HIGH);
  }
}

//--------------------Blynk Switch 4 Data Sending Func.----------------------//
BLYNK_WRITE(VPIN_BUTTON_4) {
  toggleState_4 = param.asInt();
  if(toggleState_4 == 1){
    digitalWrite(RelayPin4, LOW);
  }
  else { 
    digitalWrite(RelayPin4, HIGH);
  }
}

//--------------------Blynk Switch 5 Data Sending Func.----------------------//
BLYNK_WRITE(VPIN_BUTTON_5) {
  toggleState_5 = param.asInt();
  if(toggleState_5 == 1){
    digitalWrite(RelayPin5, LOW);
  }
  else { 
    digitalWrite(RelayPin5, HIGH);
  }
}

//--------------------Blynk Switch 6 Data Sending Func.----------------------//
BLYNK_WRITE(VPIN_BUTTON_6) {
  toggleState_6 = param.asInt();
  if(toggleState_6 == 1){
    digitalWrite(RelayPin6, LOW);
  }
  else { 
    digitalWrite(RelayPin6, HIGH);
  }
}

//--------------------Blynk Switch 7 Data Sending Func.----------------------//
BLYNK_WRITE(VPIN_BUTTON_7) {
  toggleState_7 = param.asInt();
  if(toggleState_7 == 1){
    digitalWrite(RelayPin7, LOW);
  }
  else { 
    digitalWrite(RelayPin7, HIGH);
  }
}

//--------------------Blynk Switch 8 Data Sending Func.----------------------//
BLYNK_WRITE(VPIN_BUTTON_8) {
  toggleState_8 = param.asInt();
  if(toggleState_8 == 1){
    digitalWrite(RelayPin8, LOW);
  }
  else { 
    digitalWrite(RelayPin8, HIGH);
  }
}

//----------------Blynk All Switch Cutoff Data Sending Func.-----------------//
BLYNK_WRITE(VPIN_BUTTON_C) {
  all_SwitchOff();
}

//----------------Turning off All Switch (All Switch Cutoff)-----------------//
void all_SwitchOff(){
  toggleState_1 = 0; digitalWrite(RelayPin1, HIGH); Blynk.virtualWrite(VPIN_BUTTON_1, toggleState_1); delay(100);
  toggleState_2 = 0; digitalWrite(RelayPin2, HIGH); Blynk.virtualWrite(VPIN_BUTTON_2, toggleState_2); delay(100);
  toggleState_3 = 0; digitalWrite(RelayPin3, HIGH); Blynk.virtualWrite(VPIN_BUTTON_3, toggleState_3); delay(100);
  toggleState_4 = 0; digitalWrite(RelayPin4, HIGH); Blynk.virtualWrite(VPIN_BUTTON_4, toggleState_4); delay(100);
  toggleState_5 = 0; digitalWrite(RelayPin5, HIGH); Blynk.virtualWrite(VPIN_BUTTON_5, toggleState_5); delay(100);
  toggleState_6 = 0; digitalWrite(RelayPin6, HIGH); Blynk.virtualWrite(VPIN_BUTTON_6, toggleState_6); delay(100);
  toggleState_7 = 0; digitalWrite(RelayPin7, HIGH); Blynk.virtualWrite(VPIN_BUTTON_7, toggleState_7); delay(100);
  toggleState_8 = 0; digitalWrite(RelayPin8, HIGH); Blynk.virtualWrite(VPIN_BUTTON_8, toggleState_8); delay(100);
  Blynk.virtualWrite(VPIN_HUMIDITY, humidity1);
  Blynk.virtualWrite(VPIN_TEMPERATURE, temperature1);
  Blynk.virtualWrite(VPIN_LDR, ldrVal);
}

//--------------------------Manual Switch Control-----------------------------//
void manual_control(){
  if (digitalRead(SwitchPin1) == LOW && SwitchState_1 == LOW) {
    digitalWrite(RelayPin1, LOW);
    Blynk.virtualWrite(VPIN_BUTTON_1, HIGH);
    toggleState_1 = HIGH;
    SwitchState_1 = HIGH;
    Serial.println("Switch-1 on");
  }
  if (digitalRead(SwitchPin1) == HIGH && SwitchState_1 == HIGH) {
    digitalWrite(RelayPin1, HIGH);
    Blynk.virtualWrite(VPIN_BUTTON_1, LOW);
    toggleState_1 = LOW;
    SwitchState_1 = 0;
    Serial.println("Switch-1 off");
  }
  if (digitalRead(SwitchPin2) == LOW && SwitchState_2 == LOW) {
    digitalWrite(RelayPin2, LOW);
    Blynk.virtualWrite(VPIN_BUTTON_2, HIGH);
    toggleState_2 = HIGH;
    SwitchState_2 = HIGH;
    Serial.println("Switch-2 on");
  }
  if (digitalRead(SwitchPin2) == HIGH && SwitchState_2 == HIGH) {
    digitalWrite(RelayPin2, HIGH);
    Blynk.virtualWrite(VPIN_BUTTON_2, LOW);
    toggleState_2 = LOW;
    SwitchState_2 = LOW;
    Serial.println("Switch-2 off");
  }
  if (digitalRead(SwitchPin3) == LOW && SwitchState_3 == LOW) {
    digitalWrite(RelayPin3, LOW);
    Blynk.virtualWrite(VPIN_BUTTON_3, HIGH);
    toggleState_3 = HIGH;
    SwitchState_3 = HIGH;
    Serial.println("Switch-3 on");
  }
  if (digitalRead(SwitchPin3) == HIGH && SwitchState_3 == HIGH) {
    digitalWrite(RelayPin3, HIGH);
    Blynk.virtualWrite(VPIN_BUTTON_3, LOW);
    toggleState_3 = LOW;
    SwitchState_3 = LOW;
    Serial.println("Switch-3 off");
  }
  if (digitalRead(SwitchPin4) == LOW && SwitchState_4 == LOW) {
    digitalWrite(RelayPin4, LOW);
    Blynk.virtualWrite(VPIN_BUTTON_4, HIGH);
    toggleState_4 = HIGH;
    SwitchState_4 = HIGH;
    Serial.println("Switch-4 on");
  }
  if (digitalRead(SwitchPin4) == HIGH && SwitchState_4 == HIGH) {
    digitalWrite(RelayPin4, HIGH);
    Blynk.virtualWrite(VPIN_BUTTON_4, LOW);
    toggleState_4 = LOW;
    SwitchState_4 = LOW;
    Serial.println("Switch-4 off");
  }
  if (digitalRead(SwitchPin5) == LOW && SwitchState_5 == LOW) {
    digitalWrite(RelayPin5, LOW);
    Blynk.virtualWrite(VPIN_BUTTON_5, HIGH);
    toggleState_5 = HIGH;
    SwitchState_5 = HIGH;
    Serial.println("Switch-5 on");
  }
  if (digitalRead(SwitchPin5) == HIGH && SwitchState_5 == HIGH) {
    digitalWrite(RelayPin5, HIGH);
    Blynk.virtualWrite(VPIN_BUTTON_5, LOW);
    toggleState_5 = LOW;
    SwitchState_5 = LOW;
    Serial.println("Switch-5 off");
  }
  if (digitalRead(SwitchPin6) == LOW && SwitchState_6 == LOW) {
    digitalWrite(RelayPin6, LOW);
    Blynk.virtualWrite(VPIN_BUTTON_6, HIGH);
    toggleState_6 = HIGH;
    SwitchState_6 = HIGH;
    Serial.println("Switch-6 on");
  }
  if (digitalRead(SwitchPin6) == HIGH && SwitchState_6 == HIGH) {
    digitalWrite(RelayPin6, HIGH);
    Blynk.virtualWrite(VPIN_BUTTON_6, LOW);
    toggleState_6 = LOW;
    SwitchState_6 = LOW;
    Serial.println("Switch-6 off");
  }
  if (digitalRead(SwitchPin7) == LOW && SwitchState_7 == LOW) {
    digitalWrite(RelayPin7, LOW);
    Blynk.virtualWrite(VPIN_BUTTON_7, HIGH);
    toggleState_7 = HIGH;
    SwitchState_7 = HIGH;
    Serial.println("Switch-7 on");
  }
  if (digitalRead(SwitchPin7) == HIGH && SwitchState_7 == HIGH) {
    digitalWrite(RelayPin7, HIGH);
    Blynk.virtualWrite(VPIN_BUTTON_7, LOW);
    toggleState_7 = LOW;
    SwitchState_7 = LOW;
    Serial.println("Switch-7 off");
  }
  if (digitalRead(SwitchPin8) == LOW && SwitchState_8 == LOW) {
    digitalWrite(RelayPin8, LOW);
    Blynk.virtualWrite(VPIN_BUTTON_8, HIGH);
    toggleState_8 = HIGH;
    SwitchState_8 = HIGH;
    Serial.println("Switch-8 on");
  }
  if (digitalRead(SwitchPin8) == HIGH && SwitchState_8 == HIGH) {
    digitalWrite(RelayPin8, HIGH);
    Blynk.virtualWrite(VPIN_BUTTON_8, LOW);
    toggleState_8 = LOW;
    SwitchState_8 = LOW;
    Serial.println("Switch-8 off");
  }
}


//BLYNK_CONNECTED() {
//  // Request the latest state from the server
//  Blynk.syncVirtual(VPIN_BUTTON_1);
//  Blynk.syncVirtual(VPIN_BUTTON_2);
//  Blynk.syncVirtual(VPIN_BUTTON_3);
//  Blynk.syncVirtual(VPIN_BUTTON_4);
//  Blynk.syncVirtual(VPIN_BUTTON_5);
//  Blynk.syncVirtual(VPIN_BUTTON_6);
//  Blynk.syncVirtual(VPIN_BUTTON_7);
//  Blynk.syncVirtual(VPIN_BUTTON_8);
//  Blynk.syncVirtual(VPIN_TEMPERATURE);
//  Blynk.syncVirtual(VPIN_HUMIDITY);
//  Blynk.syncVirtual(VPIN_LDR);
//}

// When App button is pushed - switch the state
