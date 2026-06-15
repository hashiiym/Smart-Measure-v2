# 📏 Smart Measure v2 (ESP32 Digital Tape Measure)

An ESP32-based digital measurement device that uses an ultrasonic sensor to calculate distances with high precision. It features a built-in Digital Signal Processing (DSP) smoothing filter to eliminate acoustic noise and displays real-time readings in both meters and inches on a sleek 0.91" OLED screen.

## ✨ Features
* **Real-Time Telemetry:** Instant distance calculations updated multiple times per second.
* **DSP Smoothing:** Custom algorithm that takes rapid-fire acoustic samples, throws out false echoes, and averages valid readings for a rock-solid display.
* **Dual-Unit Display:** Simultaneously shows measurements in Meters (large font) and Inches (small font).
* **OLED UI:** Clean, minimalist user interface utilizing an I2C 128x32 display.

## 🛠️ Hardware Requirements
* **Microcontroller:** ESP32 (e.g., ESP-WROOM-32 DevKit V1)
* **Sensor:** HC-SR04 Ultrasonic Distance Sensor
* **Display:** 0.91" I2C OLED Display (128x32 SSD1306)
* **Misc:** Breadboard, Jumper Wires, Micro-USB Cable

## 🔌 Wiring Connections

Ensure your board is completely unpowered before wiring. 

**⚠️ Important Voltage Note:** The OLED screen uses 3.3V logic, but the HC-SR04 sensor **requires 5V** to emit a strong acoustic pulse. Do not plug the HC-SR04 VCC into a 3V3 pin, or the readings will fail.

| Component | Component Pin | ESP32 Pin | Purpose |
| :--- | :--- | :--- | :--- |
| **0.91" OLED** | VCC | **3V3** | Power for the display |
| | GND | **GND** | Ground connection |
| | SDA | **D21** | I2C Data Line |
| | SCL | **D22** | I2C Clock Line |
| **HC-SR04** | VCC | **VIN (5V)** | Power for the ultrasonic transmitter |
| | GND | **GND** | Ground connection |
| | TRIG | **D5** | Triggers the high-frequency sound pulse |
| | ECHO | **D18** | Listens for the bouncing sound wave |

*(Optional Pro-Tip: The HC-SR04 outputs a 5V signal on the ECHO pin. While the ESP32 can usually tolerate this on input pins for rapid prototyping, best practice for long-term use is to add a simple voltage divider between the ECHO pin and D18 to step it down to 3.3V).*

## 📚 Libraries Used

This project relies on the following official libraries. You must install them via the **Library Manager** in the Arduino IDE before compiling.

1. **`Wire.h`** (Built-in)
   * *Purpose:* Handles the low-level I2C hardware communication between the ESP32 and the OLED screen.
2. **`Adafruit GFX Library`** by Adafruit
   * *Purpose:* The core graphics engine. It provides the math and logic to draw text, cursors, shapes, and handle screen coordinates.
3. **`Adafruit SSD1306`** by Adafruit
   * *Purpose:* The specific hardware driver that translates the GFX commands into signals the SSD1306 OLED chip can actually understand and display.
