# 🌡️ Temperature & Humidity Monitor with Overheat Alert

A real-time temperature and humidity monitoring system built 
with Arduino Uno and DHT22 sensor. Automatically triggers 
LED and buzzer alert when temperature exceeds safe limit.

> Simulated using Wokwi — no hardware required.

---

## 🔗 Live Simulation
👉 [Click here to run the simulation]([PASTE YOUR WOKWI LINK HERE](https://wokwi.com/projects/458678314911387649)

---

## 📋 What It Does

- Reads temperature and humidity every 2 seconds
- Displays live readings on LCD screen
- Green LED glows when temperature is normal
- Red LED + Buzzer alarm triggers when temperature exceeds 35°C
- Serial Monitor logs all readings continuously
- Automatically resets when temperature returns to normal

---

## 🧰 Components Used

| Component | Purpose |
|-----------|---------|
| Arduino Uno | Main controller |
| DHT22 Sensor | Temperature & humidity reading |
| LCD 16x2 I2C | Live display of readings |
| Green LED | Normal status indicator |
| Red LED | Overheat alert indicator |
| Buzzer | Audio alarm |
| 220Ω Resistors | LED protection |
| 10kΩ Resistor | DHT22 signal stability |

---

## 🔌 Wiring

| Component | Pin | Arduino |
|-----------|-----|---------|
| DHT22 VCC | Power | 5V |
| DHT22 DATA | Signal | Pin 2 |
| DHT22 GND | Ground | GND |
| LCD SDA | Data | A4 |
| LCD SCL | Clock | A5 |
| Green LED | Anode | Pin 8 |
| Red LED | Anode | Pin 9 |
| Buzzer | Positive | Pin 10 |

---

## 🚀 How to Run

1. Click the simulation link above
2. Press the green ▶ Play button
3. See live temperature on LCD
4. Click DHT22 sensor → drag temperature above 35°C
5. Watch alarm trigger automatically
6. Drag back below 35°C to reset

---

## 💻 Built With

- Language: Arduino C++
- Simulator: Wokwi (free)
- Libraries: DHT Sensor Library, LiquidCrystal I2C

---

## 👤 Author
Devanshi Gupta
```
