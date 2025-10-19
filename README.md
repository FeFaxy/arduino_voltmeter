# Arduino Voltmeter (0–24 V DC)

A simple digital voltmeter built using an **Arduino UNO R3**, two resistors, and a 16×2 I²C LCD display.  
Displays live DC voltage readings with ±0.05 V accuracy.  

---

## 🧰 Features
- Measures **0–24 V DC** safely via a voltage divider  
- I²C LCD output (address `0x27` by default)  
- 0.1 µF capacitor for stable readings  
- Averaging filter for smooth display  
- Auto-scales between volts and millivolts  

---

## ⚙️ Hardware Setup
| Pin | Connection |
|-----|-------------|
| A0  | Divider midpoint |
| A4  | SDA (LCD) |
| A5  | SCL (LCD) |
| 5V  | LCD VCC |
| GND | LCD GND and divider GND |

Resistors:
- R1 = 100 kΩ (VIN → A0)  
- R2 = 20 kΩ (A0 → GND)

Optional:  
- 0.1 µF capacitor from A0 → GND  
- 5.1 V zener diode for A0 protection  

---

## 🧩 Code
The main `.ino` file is in `/code/Arduino_Voltmeter.ino`.

---

## 📈 Calibration
1. Measure Arduino’s 5 V rail with a DMM and update `VREF` in code.  
2. Measure your actual resistor values and adjust `R1` and `R2`.  
3. Verify readings at 5 V and 9 V for ±0.05 V accuracy.

---

## 🧠 Notes
- DC voltages only. Do **not** connect to AC mains.  
- Safe input range ≈ 0–24 V DC.  
- Change divider ratio for higher ranges.  

---

## 📜 License
MIT License © 2025 Re:Engineered
