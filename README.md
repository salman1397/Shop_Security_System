# 🏪 Smart Shop Security System using IoT & ESP32

![Shop Security Banner](assets/shop_security_banner.gif)

## 🌟 Overview
The **Smart Shop Security System** is an IoT-based solution using **ESP32**, allowing remote control and monitoring of a shop’s security in real-time. The system enhances shop security with features such as:
- **Unauthorized Entry Detection**
- **Buzzer Alarm Activation**
- **Instant Notifications & Email Alerts**
- **Remote Appliance Control via Mobile Apps**

This ensures that shop owners can **monitor and control** their security system anytime, anywhere.

---

## 🚀 Features
✅ **Real-time intrusion detection**  
✅ **Instant mobile alerts & email notifications**  
✅ **Buzzer alarm activation upon unauthorized entry**  
✅ **Remote appliance control using Blynk & Bluetooth App**  
✅ **Live monitoring & event logging**  
✅ **Energy-efficient design for 24/7 operation**  

---

## 🛠️ Components Used
| Component | Description |
|-----------|------------|
| ![ESP32](https://github.com/salman1397/images/blob/main/images/esp32.png) | ESP32 WiFi & BLE Module |
| ![PIR Sensor](https://github.com/salman1397/images/blob/main/images/pir.jpg) | PIR Motion Sensor |
| ![Motion Sensor](https://github.com/salman1397/images/blob/main/images/microwavemotionsensor.png) | Microwave Motion Sensor |
| ![Buzzer](https://raw.githubusercontent.com/salman1397/images/refs/heads/main/images/siren.webp) | Alarm System for Security Alerts |
| ![3s Battery(12V)](https://github.com/salman1397/images/blob/main/images/battery3s.jpg) | 3S Battery (12.4 Volt) |
| ![3s BMS)](https://github.com/salman1397/images/blob/main/images/bms3s.png) | 3S BMS |
| ![12V adapter)](https://github.com/salman1397/images/blob/main/images/12Vadapter.jpg) | 12V Adapter |

---

## 📡 Working Principle
1️⃣ **ESP32 monitors the shop environment** using PIR sensors.  
2️⃣ If **unauthorized movement is detected**, the **buzzer alarm is triggered**.  
3️⃣ The system sends **real-time alerts** to the shop owner via the **Blynk app & email**.  
4️⃣ The owner can remotely **activate/deactivate security measures** through **Blynk or a custom Bluetooth app**.  
5️⃣ The system also enables **remote appliance control**, ensuring better shop management.

---

## 📱Dashboard And Notification
  | Aplications | Mobile Dashboards | Web Dashboard |
  |-------------|-------------------|---------------|
  | Dashboard | ![Mobile Dash](https://github.com/salman1397/images/blob/main/images/mobiledashboard.png) | ![web das](https://github.com/salman1397/images/blob/main/images/webdashboard1.png) ![web das](https://github.com/salman1397/images/blob/main/images/webdashboard2.png) |
  | Notification Dashboard | ![Mobile Notification](https://github.com/salman1397/images/blob/main/images/mobilenotification.png) | ![Web Notification](https://github.com/salman1397/images/blob/main/images/webnotification.png) |
  | Bluetooth App | ![Mobole Bluetooth](https://github.com/salman1397/images/blob/main/images/bluetoothmobile.png) | ![Bluetooth Web](https://github.com/salman1397/images/blob/main/images/bluetoothweb.png) |


---

## 🔧 Installation & Setup
### 1️⃣ Hardware Setup
- Connect the **ESP32** to **PIR sensors, buzzer, and relay module**.
- Power the ESP32 using a stable **5V adapter**.
- Place sensors strategically to **cover key entry points**.

### 2️⃣ Firmware & Code Upload
- Install **Arduino IDE** and **ESP32 Board Manager**.
- Install required libraries: `WiFi`, `Blynk`, `BluetoothSerial`, etc.
- Upload the firmware and configure **Blynk authentication tokens**.

### 3️⃣ Mobile App Setup
- Download and install the **Blynk app**.
- Connect the ESP32 device and configure it for remote access.
- Set up automation triggers and notifications.

---

## 📸 System Demonstration
![Shop Security Demo](assets/shop_security_demo.gif)

---

## ⚙️ Future Enhancements
- 📡 **LoRa-based long-distance communication**
- 🔋 **Battery backup for power failures**
- 📷 **ESP32-CAM integration for live streaming**
- 🎤 **Voice alerts for intrusions**

---

## 🏗️ Project Contributors
🔹 **[Your Name]** - Developer & Hardware Engineer  
🔹 **[Your GitHub](https://github.com/yourgithub)** - Repository Maintainer  

---

## 📜 License
This project is **open-source** and released under the **MIT License**.

---

## ⭐ Show Some Love!
If you liked this project, don't forget to **🌟 Star** the repo and **fork** it for future improvements!

[![GitHub Stars](https://img.shields.io/github/stars/yourgithub/shop-security.svg?style=social)](https://github.com/yourgithub/shop-security)
