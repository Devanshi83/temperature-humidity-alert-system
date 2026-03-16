#include "DHT.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define DHT_PIN     2
#define DHT_TYPE    DHT22
#define GREEN_LED   8
#define RED_LED     9
#define BUZZER      10
#define TEMP_LIMIT  35.0

DHT dht(DHT_PIN, DHT_TYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

float temperature = 0;
float humidity = 0;
bool alertShown = false;

void setup() {
  Serial.begin(9600);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  dht.begin();
  lcd.init();
  lcd.backlight();
  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(RED_LED, LOW);
  noTone(BUZZER);
  Serial.println("=========================================");
  Serial.println("   Temperature Monitor System Ready!    ");
  Serial.println("=========================================");
  lcd.setCursor(0, 0);
  lcd.print("Temp Monitor");
  lcd.setCursor(0, 1);
  lcd.print("Starting...");
  delay(2000);
  lcd.clear();
}

void loop() {
  temperature = dht.readTemperature();
  humidity    = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("ERROR: Sensor read failed! Check wiring.");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Sensor Error!");
    delay(2000);
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" C  |  Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature, 1);
  lcd.print(" C");
  lcd.setCursor(0, 1);
  lcd.print("Humi: ");
  lcd.print(humidity, 1);
  lcd.print(" %");

  if (temperature >= TEMP_LIMIT) {
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);
    if (!alertShown) {
      alertShown = true;
      Serial.println("ALERT! HIGH TEMPERATURE DETECTED!");
    }
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("!! HIGH TEMP !!");
    lcd.setCursor(0, 1);
    lcd.print(temperature, 1);
    lcd.print("C > 35C");
    tone(BUZZER, 1000);
    delay(300);
    tone(BUZZER, 1500);
    delay(300);
    noTone(BUZZER);
    delay(200);
  } else {
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, LOW);
    noTone(BUZZER);
    alertShown = false;
    Serial.println("Status: NORMAL - All safe.");
  }

  Serial.println("------------------------------------------");
  delay(2000);
}
