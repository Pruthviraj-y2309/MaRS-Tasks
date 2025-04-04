
int sensor1 = 0, sensor2 = 0;

void setup()
{
  pinMode(A0, INPUT);
  pinMode(8, OUTPUT);
  pinMode(A1, INPUT);
  pinMode(3, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  sensor1 = analogRead(A0);
  analogWrite(9,map(sensor1,0,466,0,255));
  sensor2 = analogRead(A1);
  analogWrite(3,map(sensor2,0,466,0,255));
  delay(100); // Wait for 100 millisecond(s)
  Serial.print("Sensor1 = ");
  Serial.println(sensor1);
  Serial.print("Sensor2 = ");
  Serial.println(sensor2);
}
