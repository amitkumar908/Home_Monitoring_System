# 📸 ESP32-CAM Motion Detection with Telegram Alerts

An **IoT-based smart surveillance system** that detects motion using a **PIR sensor** and captures an image using **ESP32-CAM**.  
Upon motion detection, the image is instantly sent to a **Telegram chat** and can also be viewed via a **live web stream**.

---

## 🚀 Overview

This project extends the *Home Monitoring System* by adding **visual motion detection and remote photo alerts**.  
It uses **ESP32-CAM** for image capture, **PIR** for motion sensing, and **Telegram Bot API** for notifications.

**Key Highlights**
- 📷 Captures image when motion is detected  
- 📲 Sends photo instantly to Telegram  
- 🌐 Real-time camera streaming over Wi-Fi  
- 🔒 Secure HTTPS connection to Telegram  
- 🧠 Built on AI-Thinker ESP32-CAM module  

---

## 🧩 Components Required

| Component | Description |
|------------|-------------|
| ESP32-CAM Module (AI Thinker) | Main microcontroller with camera |
| PIR Sensor (HC-SR501) | Detects motion using infrared radiation |
| FTDI USB-to-Serial Adapter | To program the ESP32-CAM |
| Jumper Wires | Connections |
| 5V Power Supply | Stable power source for ESP32-CAM |

---

## ⚙️ Circuit Connections

| ESP32-CAM Pin | Connect To | Description |
|----------------|-------------|-------------|
| **5V** | Power Supply (5V) | Power for ESP32-CAM |
| **GND** | GND | Common Ground |
| **GPIO 13** | PIR OUT | Motion sensor signal |
| **U0R / U0T** | FTDI TX/RX | For programming only |
| **IO0 → GND** | During Upload | Required to enter Flash Mode |

> ⚠️ After uploading, **disconnect IO0 from GND** and press **RESET**.

---

## 🧠 Working Principle

1. The **PIR sensor** detects infrared changes caused by human motion.  
2. When motion is detected, ESP32-CAM captures a **JPEG image**.  
3. The image is sent via **Telegram Bot API** using HTTPS (`api.telegram.org`).  
4. A **caption** “⚠️ Motion Detected!” appears in your Telegram chat.  
5. You can also access **live video feed** using your local IP address.

---

## 🧰 Software Setup

### 1️⃣ **Install Required Tools**
- **Arduino IDE** (latest)
- **ESP32 Board Support Package**
  - Go to *File → Preferences*  
  - Add this URL under *Additional Boards Manager URLs*:  
    ```
    https://dl.espressif.com/dl/package_esp32_index.json
    ```
  - Then install **ESP32 by Espressif Systems** from *Boards Manager*.

### 2️⃣ **Required Libraries**
These come pre-installed with the ESP32 package:
- `esp_camera.h`
- `WiFi.h`
- `WiFiClientSecure.h`

No external libraries are needed.

### 3️⃣ **Board Settings**
| Setting | Value |
|----------|--------|
| **Board** | AI Thinker ESP32-CAM |
| **Flash Mode** | QIO |
| **Partition Scheme** | Huge App (3MB No OTA/1MB SPIFFS) |
| **PSRAM** | Enabled |
| **Upload Speed** | 115200 or 921600 |

---

## ⚙️ Configuration

In the `.ino` file, update the following:

```cpp
const char* ssid     = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";
const char* botToken = "YOUR_TELEGRAM_BOT_TOKEN";
const char* chatID   = "YOUR_CHAT_ID";
