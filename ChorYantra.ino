
int flexPin = A1;        
int forcePin = A2;       
int tempPin = A0;        
int motionPin = 3;       
int buzzerPin = 9;       


int flexThreshold = 200;       
int forceThreshold = 300;      
float tempThreshold = 40.0;    


bool systemActive = false;
unsigned long activationStart = 0;
const unsigned long activeDuration = 20000;

void setup() {
  Serial.begin(9600);
  pinMode(motionPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  int motionDetected = digitalRead(motionPin);

  
  if (motionDetected == HIGH && !systemActive) {
    systemActive = true;
    activationStart = millis();
    Serial.println("Motion detected. Monitoring system activated.");
  }

  
  if (systemActive && (millis() - activationStart <= activeDuration)) {
   
    int flexValue = analogRead(flexPin);
    int forceValue = analogRead(forcePin);
    int tempRaw = analogRead(tempPin);

    //Converting stuff from analog values to needed 
    float voltage = tempRaw * (5.0 / 1023.0);
    float tempC = (voltage - 0.5) * 100.0;

    
    bool isFlexed = flexValue < flexThreshold;
    bool isForceApplied = forceValue > forceThreshold;
    bool isOverheated = tempC > tempThreshold;

    
    Serial.print("Flex: "); Serial.print(flexValue);
    Serial.print(" | Force: "); Serial.print(forceValue);
    Serial.print(" | Temperature: "); Serial.print(tempC);
    Serial.println(" °C");

    //Conditions
    if (isFlexed && isForceApplied && isOverheated) {
      Serial.println("ALERT: Case is being tampered with, broken, and burned.");
      triggerAlarm();
    } else if (isFlexed && isForceApplied) {
      Serial.println("ALERT: Case is being tampered with and forcefully moved.");
      triggerAlarm();
    } else if (isFlexed && isOverheated) {
      Serial.println("ALERT: Case is being tampered with and burned.");
      triggerAlarm();
    } else if (isForceApplied && isOverheated) {
      Serial.println("ALERT: Case is being moved and burned.");
      triggerAlarm();
    } else if (isFlexed) {
      Serial.println("ALERT: Case is being tampered with.");
      triggerAlarm();
    } else if (isForceApplied) {
      Serial.println("ALERT: Case is being moved or force is applied.");
      triggerAlarm();
    } else if (isOverheated) {
      Serial.println("ALERT: Case is being burned.");
      triggerAlarm();
    }

    delay(500);
  }

  // Reset system after 20 seconds
  if (systemActive && (millis() - activationStart > activeDuration)) {
    systemActive = false;
    Serial.println("Monitoring complete. System reset.");
  }
}

// Buzzer 
void triggerAlarm() {
  digitalWrite(buzzerPin, HIGH);
  delay(300);
  digitalWrite(buzzerPin, LOW);
}
