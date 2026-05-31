
int sensorVal;

void setup()
{
  pinMode(A0, INPUT);
  Serial.begin(9600);
  pinMode(7, OUTPUT);
}

void loop()
{
  sensorVal= analogRead(A0);
  
  
  Serial.println(sensorVal);
  
  
  if (sensorVal < 200) {
    digitalWrite(7, HIGH);
  } 
  
  else {
    digitalWrite(7, LOW);
  }
  delay(10); 
}