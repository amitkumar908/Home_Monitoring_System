/***************************************************
 * BLYNK TEMPLATE CONFIGURATION — MUST BE FIRST!
 ***************************************************/
#define BLYNK_TEMPLATE_ID "TMPL3nppcP_Gd"
#define BLYNK_TEMPLATE_NAME "SmartHome"
#define BLYNK_AUTH_TOKEN "P5ne4fkXl4yZyJ2b7Ckc1-bpoZBQWCt2"

/***************************************************
 * Library Includes
 ***************************************************/
#include <Arduino.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>   // Include AFTER the template macros
#include "DHTesp.h"
#include <Wire.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_Sensor.h>

/***************************************************
 * WiFi Configuration
 ***************************************************/
char ssid[] = "SKS";
char pass[] = "10101010";

/***************************************************
 * Pin Definitions
 ***************************************************/
#define FLAME_DO 4
#define DHT_PIN 18
#define MQ135_PIN 34

/***************************************************
 * Sensor Objects
 ***************************************************/
DHTesp dht;
Adafruit_BMP280 bmp;
BlynkTimer timer;

/***************************************************
 * Function: Send Sensor Data
 ***************************************************/
void sendSensorData() {
  // --- DHT22 ---
  TempAndHumidity dhtData = dht.getTempAndHumidity();
  if (!isnan(dhtData.temperature) && !isnan(dhtData.humidity)) {
    Serial.printf("🌡️ Temp(DHT22): %.2f °C | 💧 Humidity: %.2f %%\n",
                  dhtData.temperature, dhtData.humidity);
    Blynk.virtualWrite(V4, dhtData.temperature);
    Blynk.virtualWrite(V5, dhtData.humidity);
  } else {
    Serial.println("⚠️ Failed to read DHT22!");
  }

  // --- Flame Sensor ---
  int flame = digitalRead(FLAME_DO);
  if (flame == LOW) {
    Serial.println("🔥 Fire Detected!");
    Blynk.virtualWrite(V0, 1);
  } else {
    Serial.println("✅ No Fire Detected");
    Blynk.virtualWrite(V0, 0);
  }

  // --- MQ135 ---
  int mq135_value = analogRead(MQ135_PIN);
  Serial.printf("🌫️ MQ135 Raw Value: %d\n", mq135_value);
  Blynk.virtualWrite(V3, mq135_value);

  // --- BMP280 ---
  float pressure = bmp.readPressure() / 100.0F;
  float altitude = bmp.readAltitude(1013.25);
  Serial.printf("⛰️ BMP280 -> Pressure: %.2f hPa | Altitude: %.2f m\n", pressure, altitude);
  Blynk.virtualWrite(V1, pressure);
  Blynk.virtualWrite(V2, altitude);

  Serial.println("-----------------------------");
}

/***************************************************
 * Setup
 ***************************************************/
void setup() {
  Serial.begin(115200);
  delay(1000);

  // Initialize Sensors
  pinMode(FLAME_DO, INPUT);
  dht.setup(DHT_PIN, DHTesp::DHT22);

  if (!bmp.begin(0x76)) {
    Serial.println("❌ Could not find BMP280 sensor! Check wiring or I2C address.");
  } else {
    Serial.println("✅ BMP280 sensor initialized.");
  }

  // Connect to Blynk
  Serial.println("🔗 Connecting to WiFi & Blynk...");
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  timer.setInterval(2000L, sendSensorData);
  Serial.println("🔥 SmartHome Monitoring Started");
}

/***************************************************
 * Loop
 ***************************************************/
void loop() {
  Blynk.run();
  timer.run();
}