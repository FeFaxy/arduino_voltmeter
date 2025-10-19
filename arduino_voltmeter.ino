/*
  ==============================
   Arduino UNO Digital Voltmeter
   Measures up to ~24 V DC safely
   Author: Re:Engineered
  ==============================
*/

// --- Libraries ---
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// --- LCD Setup ---
// Address 0x27 is most common; use 0x3F if display stays blank
LiquidCrystal_I2C lcd(0x27, 16, 2);

// --- Calibration Values ---
const float VREF = 4.987;       // Actual 5V rail (measure with DMM)
const float R1   = 100000.0;    // Top resistor in divider (Ω)
const float R2   = 20000.0;     // Bottom resistor (Ω)
const byte  N    = 16;          // Number of samples for averaging

// --- Helper Function: Average and Convert ADC ---
float readV(byte pin) {
  unsigned long sum = 0;
  for (byte i = 0; i < N; i++) {
    sum += analogRead(pin);
    delayMicroseconds(400);
  }
  float adc = sum / float(N);
  return (adc * VREF) / 1023.0;   // Voltage at A0 node
}

// --- Setup ---
void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Voltmeter");
  delay(800);
  lcd.clear();
}

// --- Main Loop ---
void loop() {
  float vA0 = readV(A0);
  float vin = vA0 * (R1 + R2) / R2;  // Scale up to actual input voltage

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("VIN:");

  lcd.setCursor(0, 1);
  if (vin < 0 || vin > 31.0) {
    lcd.print("Over Range");
  } else {
    // Autoscale display for readability
    if (vin < 1.0)
      lcd.print(String(vin * 1000.0, 1) + " mV");
    else if (vin < 10.0)
      lcd.print(String(vin, 3) + " V");
    else
      lcd.print(String(vin, 2) + " V");
  }

  delay(150);
}
/*  --- Notes ---
    - Input range: 0–30 V DC (for 100kΩ/20kΩ divider)
    - Recommend staying below 24V DC
    - Max voltage = 5 V * (R1 + R2) / R2
    - For other ranges, change R1 and R2 and update SCALE.
    - Optional 0.1 µF cap across A0–GND for smoother readings.
    - For serial-only version, remove all lcd.* lines and use:
        Serial.begin(9600);
        Serial.println(vin);
*/