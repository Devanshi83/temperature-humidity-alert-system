# Temperature & Humidity Monitor with Smart Alert System

A real-time indoor environment monitoring system built on Arduino Uno
using a DHT22 sensor. The system continuously tracks temperature,
relative humidity, and heat index — triggering distinct audio-visual
alerts when readings fall outside scientifically validated thresholds.

Fully simulated on [Wokwi](https://wokwi.com) — no physical hardware
required.

---

## Live Simulation

👉 [Click here to open and run the simulation](PASTE_YOUR_WOKWI_LINK_HERE)

To test:
1. Press the green ▶ Play button
2. Click the DHT22 sensor to open the control panel
3. Drag temperature above 32°C → 2 long beeps trigger
4. Drag humidity above 65% → 3 short beeps trigger
5. Return values to safe range to reset

---

## Why This Project

Monitoring temperature and humidity manually means someone has to
constantly check the readings. That is not practical. This system
runs continuously and only demands attention when something is
actually wrong — through a distinct alert that differs depending
on whether the problem is temperature or humidity. The distinction
matters because the corrective action is different in each case.

---

## How It Works

The DHT22 sensor reports temperature and humidity every 2 seconds.
The Arduino evaluates each reading against defined thresholds:

- Readings within range → Green LED on, system silent
- Temperature out of range → Red LED + 2 long beeps
- Humidity out of range → Red LED + 3 short beeps
- Either value below lower limit → same alert behavior
- LCD cycles between two views: current readings with status,
  and heat index with total alert count
- All readings logged continuously to Serial Monitor

The two distinct buzzer patterns are intentional. If someone hears
the alert from another room, they can tell immediately whether it
is a temperature or humidity problem before they even look at
the screen.

---

## Safe Operating Thresholds

| Parameter | Safe Range | Alert Triggers At |
|-----------|-----------|------------------|
| Temperature | 10°C – 32°C | Above 32°C or below 10°C |
| Relative Humidity | 30% – 65% | Above 65% or below 30% |

These values are taken directly from peer-reviewed published
research. See the Research Basis section below.

---

## Research Basis

The thresholds used in this project are derived from the following
published academic sources:

**Primary Source:**
Azhari, T.I. Nasution, S.H. Sinaga, and Sudiati (2023).
*Design of Monitoring System Temperature And Humidity Using DHT22
Sensor and NRF24L01 Based on Arduino.*
Journal of Physics: Conference Series, Volume 2421, IOP Publishing.
DOI: [10.1088/1742-6596/2421/1/012018](https://doi.org/10.1088/1742-6596/2421/1/012018)

This is the most directly comparable published study to this project.
It uses identical hardware — DHT22 and Arduino — for indoor
environment monitoring and explicitly defines 32°C as the upper
temperature threshold and 65% RH as the upper humidity threshold.

**Supporting Source:**
I.K.A. Enriko et al. (2023).
*Implementation of Temperature and Humidity Monitoring System
Using LoRaWAN.*
Atlantis Press.
https://www.atlantis-press.com/article/125980164.pdf

References the Ministry of Health indoor standard of 40–70% RH,
supporting the humidity range used in this project.

**Sensor Accuracy Validation:**
IIARD International Journal of Engineering and Mathematical
Theory (2025), Vol. 11, No. 7. P-ISSN 2695-2149.
Confirms DHT22 accuracy at ±0.5°C and ±2–5% RH — sufficient
precision for indoor environmental monitoring.
https://iiardjournals.org

---

## Features

| Feature | Description |
|---------|-------------|
| Real-time monitoring | New reading every 2 seconds |
| Heat index | Apparent temperature from temp + humidity combined |
| Dual LCD pages | Readings + status / Heat index + alert count |
| Smart buzzer patterns | 2 long beeps = temperature / 3 short = humidity |
| Alert counter | Total alerts tracked and displayed |
| Lower limit alerts | Covers dangerous cold and dryness too |
| Serial logging | Full data printed every reading cycle |

---

## Components

| Component | Specification | Purpose |
|-----------|-------------|---------|
| Arduino Uno Rev3 | ATmega328P | Microcontroller |
| DHT22 Sensor | ±0.5°C, ±2–5% RH | Temperature & humidity sensing |
| LCD 16×2 I2C | Address 0x27 | Live data display |
| Green LED | 5mm | Safe status indicator |
| Red LED | 5mm | Alert status indicator |
| Buzzer | Passive | Audio alert output |
| Resistor 220Ω × 2 | — | LED current limiting |
| Resistor 10kΩ × 1 | — | DHT22 data line pull-up |

---

## Wiring

| Component | Pin | Arduino |
|-----------|-----|---------|
| DHT22 VCC | Power | 5V |
| DHT22 DATA | Signal | Pin 2 |
| DHT22 DATA | Pull-up | 5V via 10kΩ |
| DHT22 GND | Ground | GND |
| LCD VCC | Power | 5V |
| LCD GND | Ground | GND |
| LCD SDA | I2C Data | A4 |
| LCD SCL | I2C Clock | A5 |
| Green LED (+) | Anode | Pin 8 via 220Ω |
| Green LED (–) | Cathode | GND |
| Red LED (+) | Anode | Pin 9 via 220Ω |
| Red LED (–) | Cathode | GND |
| Buzzer (+) | Positive | Pin 10 |
| Buzzer (–) | Negative | GND |

---

## Libraries

Install via the Wokwi Library Manager or accept the prompt on
first compile:

- DHT sensor library — Adafruit
- LiquidCrystal I2C — Frank de Brabander
- Wire — built-in, no install needed

---

## Built With

- Language: Arduino C++
- Simulator: Wokwi (free)
- Libraries: DHT Sensor Library, LiquidCrystal I2C, Wire

---

## Author

**[Your Name]**
[LinkedIn](#) · [GitHub](#)
