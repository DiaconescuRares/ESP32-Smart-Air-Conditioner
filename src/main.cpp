#include <Arduino.h>
#include "DHTesp.h"

#define SETPOINT 35.0   // temperature at which the fan turns ON
#define HYST     2.0    // how much below SETPOINT it must drop to turn OFF

DHTesp dht;
const int DHT_PIN = 14;
const int RELAY_PIN = 13;

bool highTempCheck(float temperature, float setpoint);
bool lowTempCheck(float temperature, float setpoint);
void turnOnRelay(int relay_pin);
void turnOffRelay(int relay_pin);
float read_temperature();

void setup() {
  Serial.begin(115200);
  pinMode(RELAY_PIN, OUTPUT);
  dht.setup(DHT_PIN, DHTesp::DHT11);

  Serial.printf("Setpoint=%.1f°C, Stop at <= %.1f°C\n", SETPOINT, SETPOINT - HYST);
}

void loop() {
  float current_temperature = read_temperature();

  if (highTempCheck(current_temperature, SETPOINT)) {
    unsigned long seconds = millis() / 1000;
    Serial.printf("[%lus] High limit reached -> Fan ON\n", seconds);
    turnOnRelay(RELAY_PIN);

    // stay ON until T <= SETPOINT - HYST
    while (lowTempCheck(current_temperature, SETPOINT) == 0) {
      current_temperature = read_temperature();
    }

    seconds = millis() / 1000;
    Serial.printf("[%lus] Low limit reached -> Fan OFF\n", seconds);
    turnOffRelay(RELAY_PIN);
  }
}

bool highTempCheck(float temperature, float setpoint) {
  // returns true if T >= setpoint
  return (temperature >= setpoint);
}

bool lowTempCheck(float temperature, float setpoint) {
  // returns true if T <= setpoint - HYST
  return (temperature <= (setpoint - HYST));
}

float read_temperature()
{
  static float buffer[3] = {NAN, NAN, NAN}; 
  static int index = 0;
  static int filled = 0;
  static float lastAvg = NAN;

  delay(2000);
  float t = dht.getTemperature();  // reads current temperature

  // if invalid reading, return last valid average
  if (isnan(t)) return lastAvg;

  buffer[index] = t;               // adds current temperature to buffer
  index = (index + 1) % 3;         // updates the index of the buffer
  if (filled < 3)                  // for the first 3 readings, filled is incremented
    filled++;

  float sum = 0;
  for (int i = 0; i < filled; i++)
    sum += buffer[i];              // calculates the sum of the buffer
  float avg = sum / filled;        // returns the average of the buffer (even if not yet full)

  lastAvg = avg;

  // print elapsed seconds since program start + average temperature
  unsigned long seconds = millis() / 1000;
  Serial.printf("[%lus] Avg3: %.1f °C\n", seconds, avg);

  return avg;
}

void turnOnRelay(int relay_pin) {
  digitalWrite(relay_pin, HIGH);   // change to LOW if your relay is active LOW
}

void turnOffRelay(int relay_pin) {
  digitalWrite(relay_pin, LOW);    // change to HIGH if your relay is active LOW
}
