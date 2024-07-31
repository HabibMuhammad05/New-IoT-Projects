int thresholds[16] = {530, 448, 373, 253, 541, 463, 391, 276, 553, 476, 408, 300, 562, 489, 427, 320};
char key[16]       = {'1', '2', '3', 'A', '4', '5', '6', 'B', '7', '8', '9', 'C', '*', '0', '#', 'D'};
bool state = true;
void setup() {
  pinMode(A0, INPUT);
  pinMode(13, INPUT_PULLUP);
  Serial.begin(115200);
}

void loop() {
  int val = analogRead(A0);
  
  for (int i = 0; i < 16; i++){
    if( abs(val - thresholds[i]) < 5){
      Serial.println(val);
      Serial.println(key[i]);
      stateCheck();
      while(analogRead(A0) < 1000) {delay(10); }
    }
  }
  

  if(state){
    Serial.println("WifiMode");
  }else{
    Serial.println("ketyMode");}
    
}
void stateCheck(){
  if(digitalRead(13) == 0){
  state = !state;}
}
