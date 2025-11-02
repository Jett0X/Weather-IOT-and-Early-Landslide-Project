# Weather-IOT-and-Early-Landslide-Project
Simulated Rainfall: It uses a controlled rain simulation system to replicate and test the effects of different rainfall intensities—light, moderate, and heavy—on soil moisture and stability.

# ⚠️ Landslide Early Warning System (LEWS) - Arduino IoT Monitor

An **Arduino Uno-based soil moisture and environmental monitoring system** designed to detect and provide early warnings for potential landslides by leveraging real-time data from soil saturation and atmospheric conditions.

---

## ⚡️ Project Overview

Landslides are often triggered by heavy rainfall. This project develops a low-cost, multi-sensor solution that goes beyond just measuring soil wetness. By integrating the **BMP280 sensor**, the system gains a **predictive capability**—a sharp drop in atmospheric pressure can serve as a pre-emptive alert for an incoming storm, allowing for earlier warnings before the soil becomes critically saturated.

### Key Features
* **Real-Time Monitoring:** Continuous measurement of soil moisture and atmospheric conditions.
* **Predictive Warning:** Utilizes barometric pressure data (from BMP280) to forecast heavy rainfall and potential risk *before* saturation occurs.
* **Controlled Simulation:** Uses a dedicated rain simulation rig to replicate and analyze the effects of **light, moderate, and heavy** rainfall on soil stability.
* **IoT Ready:** Designed for future integration with Wi-Fi modules (like ESP8266 or ESP32) for remote data logging and alerts.

---

## 🛠️ Hardware Requirements

<h3>The system integrates both soil and atmospheric sensors using the **Arduino Uno** as the central hub.</h3>

| Component | Description | Connection Type | Quantity |
| :--- | :--- | :--- | :--- |
| **Arduino Uno** | Microcontroller board for data proce    ssing and sensor control. | - | 1 |
| **Capacitive Soil Moisture Sensor** | Measures soil moisture level (critical landslide trigger). | Analog Pin (e.g., A0) | 1+ |
| **BMP280 Sensor** | Measures **Atmospheric Pressure** and **Temperature** (for predictive weather monitoring). | I2C (SDA -> A4, SCL -> A5) | 1 |
| **Display (e.g., I2C LCD)** | To display real-time sensor readings and system status. | I2C | 1 |
| **Controlled Rain Rig** | Custom setup to deliver calibrated rainfall intensities. | - | 1 |
| **Warning Indicator** | (Optional) LED or Buzzer for high-risk alerts. | Digital Pin | 1 |

---

## 💻 Software and Dependencies

The firmware is developed using the **Arduino Integrated Development Environment (IDE)**.

### Required Libraries
You must install these libraries via the Arduino Library Manager:

1.  `Wire.h` (Standard I2C library)
2.  `Adafruit_Sensor` (Adafruit Unified Sensor Driver - a dependency)
3.  `Adafruit_BMP280` (For communicating with the BMP280 sensor)
4.  `LiquidCrystal_I2C` (If using an I2C LCD display)

### Setup & Code
1.  Clone this repository:
    ```bash
    git clone [https://github.com/Jett0X](https://github.com/Jett0X/Weather-IOT-and-Early-Landslide-Project)
    ```
2.  Open the main `.ino` sketch in the Arduino IDE.
3.  Ensure all required libraries are installed.
4.  Upload the sketch to your **Arduino Uno** board.

---

## 🔬 Predictive Methodology

The system monitors two primary risk factors: **Soil Saturation** and **Atmospheric Pressure Drop**.

$$
\text{RISK} = f(\text{Moisture}_{\text{Current}}, \Delta \text{Pressure}/\Delta \text{Time})
$$

| Factor | Critical Threshold | Action |
| :--- | :--- | :--- |
| **Soil Moisture ($\text{M}$)** | $\text{M} \ge \text{M}_{\text{critical}}$ (e.g., 85%) | **Immediate Warning (Red Alert)**: Soil stability is compromised. |
| **Atmospheric Pressure ($\text{P}$)** | $\Delta \text{P} \le -5 \text{ hPa}$ in $1 \text{ hour}$ | **Pre-emptive Warning (Yellow Alert)**: Heavy rain is likely; prepare for saturation. |

The controlled rain simulation will be critical for accurately determining the $\text{M}_{\text{critical}}$ threshold for the specific soil type being tested.

---

## 🛣️ Future Enhancements
* **True IoT Integration:** Replace the Arduino Uno with an **ESP32** or **ESP8266** for built-in Wi-Fi connectivity to log data to a cloud service (e.g., ThingSpeak) and send remote alerts (SMS/Email).
* **Humidity Monitoring:** If a **BME280** is used, humidity data can provide a more complete environmental profile.
* **Multi-Point Sensing:** Deploy a network of soil moisture sensors at various depths and locations for a comprehensive stability map.

---

## 🤝 Contributing

We welcome contributions! Please feel free to open an issue or submit a pull request.

---

## 📄 License

This project is licensed under the MIT License - see the `https://github.com/Jett0X/Weather-IOT-and-Early-Landslide-Project/blob/main/LICENSE` file for details.