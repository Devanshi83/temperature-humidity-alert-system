#include "DHT.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define DHT_PIN       2
#define DHT_TYPE      DHT22
#define GREEN_LED     8
#define RED_LED       9
#define BUZZER_PIN    10


const float TEMP_UPPER   = 32.0;
const float TEMP_LOWER   = 10.0;
const float HUMID_UPPER  = 65.0;
const float HUMID_LOWER  = 30.0;


DHT dht(DHT_PIN, DHT_TYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);


float currentHumid     = 0.0;
float heatIndex        = 0.0;
bool  alertActive      = false;
int   totalAlerts      = 0;
int   lcdPage          = 0;

void setup() {
  Serial.begin(9600);

  pinMode(GREEN_LED,  OUTPUT);
  pinMode(RED_LED,    OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  dht.begin();
  lcd.init();
  lcd.backlight();

  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(RED_LED,   LOW);
  noTone(BUZZER_PIN);

  printStartupHeader();
  showStartupLCD();
}


void loop() {
  delay(2000);

  currentTemp  = dht.readTemperature();
  currentHumid = dht.readHumidity();

  if (isnan(currentTemp) || isnan(currentHumid)) {
    handleSensorError();
    return;
  }

  heatIndex = dht.computeHeatIndex(currentTemp, currentHumid, false);

  printSerialReadings();
  updateLCD();

  if (isOutOfRange()) {
    handleAlert();
  } else {
    handleSafe();
  }

  Serial.println(F("----------------------------------------------"));
}

bool isOutOfRange() {
  return (currentTemp  >= TEMP_UPPER  ||
          currentTemp  <= TEMP_LOWER  ||
          currentHumid >= HUMID_UPPER ||
          currentHumid <= HUMID_LOWER);
}


String getAlertLabel() {
  if (currentTemp  >= TEMP_UPPER)  return "HIGH TEMP";
  if (currentTemp  <= TEMP_LOWER)  return "LOW TEMP";
  if (currentHumid >= HUMID_UPPER) return "HIGH HUMID";
  if (currentHumid <= HUMID_LOWER) return "LOW HUMID";
  return "UNKNOWN";
}


void handleAlert() {
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED,   HIGH);

  if (!alertActive) {
    alertActive = true;
    totalAlerts++;
    Serial.print(F(">>> ALERT #"));
    Serial.print(totalAlerts);
    Serial.print(F(" TRIGGERED: "));
    Serial.println(getAlertLabel());
    Serial.println(F("    Immediate attention required."));
  }

  bool isTempAlert = (currentTemp >= TEMP_UPPER || currentTemp <= TEMP_LOWER);

  if (isTempAlert) {
    twoLongBeeps();
  } else {
    threeShortBeeps();
  }
}


void handleSafe() {
  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(RED_LED,   LOW);
  noTone(BUZZER_PIN);

  if (alertActive) {
    alertActive = false;
    Serial.println(F(">>> Conditions restored to safe range."));
  } else {
    Serial.println(F("Status: SAFE — All readings within range."));
  }
}


void handleSensorError() {
  Serial.println(F("ERROR: Failed to read from DHT22 sensor."));
  Serial.println(F("       Check wiring and pull-up resistor."));
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("  Sensor Error  "));
  lcd.setCursor(0, 1);
  lcd.print(F(" Check Wiring! "));
}


void updateLCD() {
  lcd.clear();

  if (lcdPage == 0) {
    lcd.setCursor(0, 0);
    lcd.print(F("T:"));
    lcd.print(currentTemp, 1);
    lcd.print(F("C  H:"));
    lcd.print(currentHumid, 0);
    lcd.print(F("%"));

    lcd.setCursor(0, 1);
    if (isOutOfRange()) {
      lcd.print(F("!"));
      lcd.print(getAlertLabel());
      lcd.print(F("!"));
    } else {
      lcd.print(F("Status: SAFE"));
    }
    lcdPage = 1;

  } else {
    lcd.setCursor(0, 0);
    lcd.print(F("Feels: "));
    lcd.print(heatIndex, 1);
    lcd.print(F("C"));

    lcd.setCursor(0, 1);
    lcd.print(F("Alerts: "));
    lcd.print(totalAlerts);
    lcdPage = 0;
  }
}

void printSerialReadings() {
  Serial.print(F("Temp: "));
  Serial.print(currentTemp, 1);
  Serial.print(F("C  |  Humidity: "));
  Serial.print(currentHumid, 1);
  Serial.print(F("%  |  Feels Like: "));
  Serial.print(heatIndex, 1);
  Serial.print(F("C  |  Alerts: "));
  Serial.println(totalAlerts);
}


void printStartupHeader() {
  Serial.println(F("=============================================="));
  Serial.println(F("  Temperature & Humidity Monitor — Ready     "));
  Serial.println(F("=============================================="));
  Serial.println(F("Thresholds (Azhari et al., IOP, 2023):"));
  Serial.print  (F("  Temperature : "));
  Serial.print  (TEMP_LOWER);   Serial.print(F("C — "));
  Serial.print  (TEMP_UPPER);   Serial.println(F("C"));
  Serial.print  (F("  Humidity    : "));
  Serial.print  (HUMID_LOWER);  Serial.print(F("% — "));
  Serial.print  (HUMID_UPPER);  Serial.println(F("%"));
  Serial.println(F("----------------------------------------------"));
}


void showStartupLCD() {
  lcd.setCursor(0, 0);
  lcd.print(F(" Temp + Humidity"));
  lcd.setCursor(0, 1);
  lcd.print(F("  Monitor v2.0  "));
  delay(2500);
  lcd.clear();
}

void twoLongBeeps() {
  tone(BUZZER_PIN, 1000); delay(600);
  noTone(BUZZER_PIN);     delay(250);
  tone(BUZZER_PIN, 1000); delay(600);
  noTone(BUZZER_PIN);     delay(250);
}

void threeShortBeeps() {
  tone(BUZZER_PIN, 1500); delay(200);
  noTone(BUZZER_PIN);     delay(100);
  tone(BUZZER_PIN, 1500); delay(200);
  noTone(BUZZER_PIN);     delay(100);
  tone(BUZZER_PIN, 1500); delay(200);
  noTone(BUZZER_PIN);     delay(100);
}
