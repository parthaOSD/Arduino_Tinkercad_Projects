#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo servo;

const int buzzer = 8;
const int led = 9;
const int button = 7;
int currentHour = 10;
int currentMinute = 29;
int medHour[] = {10, 14, 20};
int medMinute[] = {30, 0, 30};
int totalMeds = 3;

bool alertOn = false;
int activeMed = -1;

void setup() {
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();

  pinMode(buzzer, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(button, INPUT_PULLUP);

  servo.attach(6);
  servo.write(0);

  lcd.setCursor(0, 0);
  lcd.print("Medicare System");
  delay(2000);
  lcd.clear();
}

void loop() {
  delay(50);
  currentMinute++;
  if (currentMinute >= 60) {
    currentMinute = 0;
    currentHour++;
    if (currentHour >= 24) currentHour = 0;
  }

  
  lcd.setCursor(0, 0);
  lcd.print("Time: ");
  if (currentHour < 10) lcd.print("0");
  lcd.print(currentHour);
  lcd.print(":");
  if (currentMinute < 10) lcd.print("0");
  lcd.print(currentMinute);
  lcd.print("   ");

  lcd.setCursor(0, 1);
  lcd.print("Next Med Check");

  Serial.print("Time: ");
  Serial.print(currentHour);
  Serial.print(":");
  Serial.println(currentMinute);

  for (int i = 0; i < totalMeds; i++) {
     if (currentHour == medHour[i] &&
        currentMinute == medMinute[i] &&
        !alertOn) {

      activeMed = i;

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Take Medicine!");
      lcd.setCursor(0, 1);
      lcd.print("Dose ");
      lcd.print(i + 1);

      Serial.println("Medicine Alert!");

      digitalWrite(buzzer, HIGH);
      digitalWrite(led, HIGH);
      servo.write(90);

      alertOn = true;
    }
  }

  if (alertOn && digitalRead(button) == LOW) {

    delay(200);

    digitalWrite(buzzer, LOW);
    digitalWrite(led, LOW);
    servo.write(0);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Medicine Taken");
    lcd.setCursor(0, 1);
    lcd.print("Dose ");
    lcd.print(activeMed + 1);

    Serial.println("Taken");

    alertOn = false;
    activeMed = -1;

    delay(3000);
    lcd.clear();
  }

}