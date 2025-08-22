# 🌡️ ESP32 Smart Fan Controller — v0.1

Minimal ESP32 project that controls a fan with **setpoint + hysteresis** logic (similar to an air conditioner).  
This first version runs **locally** and prints logs to the Serial Monitor with **timestamps in seconds**.

🎥 Demo video: https://youtu.be/REPLACE_WITH_YOUR_VIDEO_ID

---

## Features (v0.1)
- Turns **ON** the fan when temperature >= `SETPOINT`.
- Turns **OFF** the fan when temperature <= `SETPOINT - HYST`.
- Uses the average of the **last 3 readings** to stabilize the DHT11 sensor.
- Serial Monitor output includes:
  - `[12s] Avg3: 28.7 °C`
  - `[58s] High limit reached -> Fan ON`
  - `[142s] Low limit reached -> Fan OFF`

---

## Hardware
- ESP32 DevKit board
- DHT11 temperature sensor
- Relay module (1 channel)
- Fan (5–12V) or LED for testing
- Breadboard + jumper wires

⚠️ **Note:** If using 230V AC, ensure proper safety (isolation, enclosure, fuses). For prototyping, stick to 12V.

---

## Quick start
1. Clone this repo or download the code.
2. Open the sketch in Arduino IDE (or PlatformIO).
3. Select **ESP32 Dev Module** as the board, correct COM port.
4. Upload the code.
5. Open Serial Monitor at **115200 baud**.
6. Adjust `SETPOINT` and `HYST` in the code to match your needs.

---

## Next version (v0.2)
- Log fan state and temperature to **ThingSpeak** (cloud).
- Build temperature/fan history charts online.
