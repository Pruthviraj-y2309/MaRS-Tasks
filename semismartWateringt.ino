
int Moisturepin = A0;  
int Temppin = A2;      
int Lightpin = A3;     

int Ledsun = 9;        
int Ledtemp = 10;      
int Ledlight = 11;     

int moistureThreshold = 500;   
float temperatureThreshold = 30.0;
int lightThreshold = 700;      

void setup() {
  Serial.begin(9600);
  
  pinMode(Ledsun, OUTPUT);
  pinMode(Ledtemp, OUTPUT);
  pinMode(Ledlight, OUTPUT);
}

void loop() {
  int moistureValue = analogRead(Moisturepin);
  int tempValue = analogRead(Temppin);
  int lightValue = analogRead(Lightpin);

  //Converting to understandable format
  float voltage = tempValue * (5.0 / 1023.0);
  float temperatureC = (voltage - 0.5) * 100.0;

  Serial.print("Moisture: "); Serial.print(moistureValue);
  Serial.print(" | Temperature: "); Serial.print(temperatureC);
  Serial.print("°C | Light: "); Serial.println(lightValue);

  bool isHighTemp = temperatureC > temperatureThreshold;
  bool isHighLight = lightValue > lightThreshold;
  bool isDrySoil = moistureValue < moistureThreshold;

  
  setLEDColor(0, 0, 0);

  if (isDrySoil) {
    setLEDColor(255, 0, 0);  
    Serial.println("Soil is dry! Please water the plant.");
  } 
  else if (isHighTemp || isHighLight) {
    setLEDColor(0, 0, 255);  
    if (isHighTemp && isHighLight) {
      Serial.println("Warning: High sunlight and high temperature!");
    } else if (isHighTemp) {
      Serial.println("Warning: Temperature is too high!");
    } else {
      Serial.println("Warning: Sunlight is too strong!");
    }
  } 
  else {
    setLEDColor(0, 255, 0);  
    Serial.println("All conditions are optimal.");
  }

  delay(1000); 
}


void setLEDColor(int red, int green, int blue) {
  analogWrite(Ledsun, red);
  analogWrite(Ledtemp, green);
  analogWrite(Ledlight, blue);
}
