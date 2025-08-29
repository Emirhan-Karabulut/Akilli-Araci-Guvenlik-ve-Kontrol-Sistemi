#include <LiquidCrystal.h>
LiquidCrystal lcd(22, 23, 24, 25, 26, 27);

#define TEMP_LIMIT 25
#define LIGHT_LIMIT 250
#define LOW_FUEL 10
#define CRITICAL_FUEL 5
#define CONVERT_TO_DEGREE ((5.0/1023.0)*100)

#define BTN_START 2
#define BTN_BELT 3
#define SW_DOOR 4
#define TEMP_SENS A0
#define LIGHT_SENS A1
#define FUEL_SENS A2
#define LED_RED 5
#define LED_BLUE 6
#define LED_YELLOW 7
#define LED_RGB_R 8
#define LED_RGB_G 12
#define LED_RGB_B 13
#define BUZZER 9
#define MOTOR 10
#define AC_MOTOR 11

bool motorStarted = false, beltFastened = false, doorClosed = false;
bool lightsOn = false, acOn = false, yellowLedState = false, prevDoorClosed = false;
int temperature = 0, lightLevel = 0, fuelLevel = 0;
unsigned long lastYellowToggle = 0, lastLcdChange = 0;
byte lcdState = 0;

void setup() {
  pinMode(BTN_START, INPUT_PULLUP);
  pinMode(BTN_BELT, INPUT_PULLUP);
  pinMode(SW_DOOR, INPUT_PULLUP);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_RGB_R, OUTPUT);
  pinMode(LED_RGB_G, OUTPUT);
  pinMode(LED_RGB_B, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(MOTOR, OUTPUT);
  pinMode(AC_MOTOR, OUTPUT);

  lcd.begin(16, 2);
  lcd.print("Arac Kontrol");
  lcd.setCursor(0, 1);
  lcd.print("Sistemi");
  delay(1000);
  lcd.clear();
}

void loop() {
  temperature = round(analogRead(TEMP_SENS) * CONVERT_TO_DEGREE) - 2;
  lightLevel = analogRead(LIGHT_SENS);
  fuelLevel = map(analogRead(FUEL_SENS), 0, 1023, 0, 100);
  doorClosed = (digitalRead(SW_DOOR) == LOW);

  if (!doorClosed) {
    displayMessage("Uyari: Kapi Acik", "Motor Calismaz");
    digitalWrite(LED_RGB_R, LOW); 
    digitalWrite(LED_RGB_G, HIGH); 
    digitalWrite(LED_RGB_B, LOW);
    if (motorStarted) 
      closeAllSystem();
  } else if (prevDoorClosed != doorClosed) {
    digitalWrite(LED_RGB_R, HIGH); 
    digitalWrite(LED_RGB_G, HIGH); 
    digitalWrite(LED_RGB_B, HIGH);
    displayMessage("Kapi Kapandi", "");
  }
  prevDoorClosed = doorClosed;

  if (digitalRead(BTN_BELT) == LOW) {
    beltFastened = !beltFastened;
    delay(300);
    digitalWrite(LED_RED, !beltFastened);
    digitalWrite(BUZZER, !beltFastened);
    displayMessage("Emniyet Kemeri", beltFastened ? "Takildi" : "Takili Degil!");
    if (!beltFastened) 
      closeAllSystem();
  }

  if (digitalRead(BTN_START) == LOW) {
    if(doorClosed){
      if(fuelLevel > 0){
        if (beltFastened) {
        motorStarted = !motorStarted;
        digitalWrite(MOTOR, motorStarted);
        displayMessage(motorStarted ? "Motor Calisti" : "Motor Durdu", "");
        if (!motorStarted)
          closeAllSystem();
        } else {
        digitalWrite(LED_RED, HIGH); digitalWrite(BUZZER, HIGH);
        displayMessage("Emniyet Kemeri", "Takili Degil!");
        }
      }else
        displayMessage("Yakit Bitti!", "");
    }
    
    delay(300);
  }

  if (motorStarted) {
    bool newAcState = (temperature > TEMP_LIMIT);
    if (newAcState != acOn) {
      acOn = newAcState;
      digitalWrite(AC_MOTOR, acOn);
      displayMessage("Sicaklik: " + String(temperature) + "C", acOn ? "Klima Acildi" : "Klima Kapandi");
    }

    bool newLightsState = (lightLevel <= LIGHT_LIMIT);
    if (newLightsState != lightsOn) {
      lightsOn = newLightsState;
      digitalWrite(LED_BLUE, lightsOn);
      displayMessage(lightsOn ? "Farlar Acik" : "Farlar Kapandi", "");
    }

    if (fuelLevel <= 0) {
      closeAllSystem();
      displayMessage("Yakit Bitti", "Motor Durdu");
    } else if (fuelLevel <= CRITICAL_FUEL && millis() - lastYellowToggle >= 400) {
      yellowLedState = !yellowLedState;
      digitalWrite(LED_YELLOW, yellowLedState);
      lastYellowToggle = millis();
    } else {
      digitalWrite(LED_YELLOW, fuelLevel <= LOW_FUEL ? HIGH : LOW);
    }
  }

  updateLcd();
  delay(50);
}

void updateLcd() {
  if (millis() - lastLcdChange < 2000)
    return;
  
  lastLcdChange = millis();
  lcdState = (lcdState + 1) % 3;
  lcd.clear();
  
  if (!motorStarted) {
    lcd.print("Motor: Kapali");
    lcd.setCursor(0, 1);
    lcd.print(!beltFastened ? "Kemer Takilmadi" : (doorClosed ? "" : "Kapi Acik"));
    return;
  }
  
  String lines[5][2] = {
    {"Sicaklik: " + String(temperature) + "C", "Klima: " + String(acOn ? "Acik" : "Kapali")},
    {"Farlar: " + String(lightsOn ? "Acik" : "Kapali")},
    {"Yakit: %" + String(fuelLevel),
      fuelLevel <= CRITICAL_FUEL ? "KRITIK: Yakit Az!" :
      (fuelLevel <= LOW_FUEL ? "UYARI: Yakit Az!" : "")}
  };
  
  lcd.print(lines[lcdState][0]);
  if (lines[lcdState][1].length() > 0) {
    lcd.setCursor(0, 1);
    lcd.print(lines[lcdState][1]);
  }
}

void displayMessage(String line1, String line2) {
  lcd.clear();
  lcd.print(line1);
  if (line2.length() > 0) {
    lcd.setCursor(0, 1);
    lcd.print(line2);
  }
  lastLcdChange = millis();
}

void closeAllSystem() {
  motorStarted = false;
  digitalWrite(MOTOR, LOW);
  digitalWrite(AC_MOTOR, LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_BLUE, LOW);
  lightsOn = false;
  acOn = false;
}