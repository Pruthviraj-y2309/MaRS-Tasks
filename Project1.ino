//Setting up the pins 
int motionpirpin=3;
int titltpin=6;
int temppin=A0;
int flexpin=A1;
int sound=9;


void setup()
{
    
  pinMode(motionpirpin, INPUT);
  pinMode(tiltpin, INPUT_PULLUP); 
  pinMode(sound, OUTPUT);
  Serial.begin(9600);
}

void loop() {
    // Read sensor values
    int motion = digitalRead(motionpirpin);

    if (motion == HIGH && !systemActive) {
        Serial.println(" Motion Detected! System Activated.");
        systemActive = true;
        activationTime = millis();
      }

    if(systemActive){

        int tiltState = digitalRead(tiltpin);  
    int tempRaw = analogRead(temppin);
    int flexValue = analogRead(flexpin);
    
   //Conversing inputs into understandable values 
    float voltage = tempRaw * (5.0 / 1023.0); 
    float tempC = (voltage - 0.5) * 100.0;    
  
    bool alarm = false;
    
    
    Serial.print("Motion: "); Serial.print(motion);
    Serial.print(" | Tilt: "); Serial.print(tiltState);
    Serial.print(" | Temp (C): "); Serial.print(tempC);
    Serial.print(" | Flex: "); Serial.println(flexValue);
    
    
    if (motion == HIGH)
     {
      Serial.println("Motion detected.");
      
      
      if (tiltState == LOW) 
      {
        Serial.println("Tilt Alert! Case is being moved.");
        alarm = true;
      }
      
      
      if (tempC > TEMP_THRESHOLD) 
      {
        Serial.println("Heat Alert! High temperature detected.");
        alarm = true;
      }
      
      
      if (flexValue < FLEX_THRESHOLD) 
      {
        Serial.println("Flex Alert! Possible tampering detected.");
        alarm = true;
      }
    }
    
    // Trigger alarm if any issue is detected
    if (alarm)
     {
      digitalWrite(sound, HIGH); 
      delay(3000);                    
      digitalWrite(sound, LOW);  
    }
    
    delay(500);  


}
  