#define TMP_PIN A1          
#define SOIL_PIN A0       
#define RELAY_PIN 3         

void setup() {
  Serial.begin(9600);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
}

void loop() {
  int tmpRaw = analogRead(TMP_PIN);
  float voltage = tmpRaw * (5.0 / 1023.0);
  float temperature = (voltage - 0.5) * 100;  

  int soil = analogRead(SOIL_PIN);
  int moisture = map(soil, 1023, 0, 0, 100);  

  Serial.print("Temp: ");
  Serial.print(temperature);
  Serial.print(" °C, Soil: ");
  Serial.print(moisture);
  Serial.println(" %");

  if (moisture < 30) {
    digitalWrite(RELAY_PIN, HIGH); 
  } else {
    digitalWrite(RELAY_PIN, LOW);  
  }

  delay(2000);
}