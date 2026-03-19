# 🚗 Real-Time Vehicle Status Monitoring System using CAN Protocol

<p align="center">
  <img src="https://img.shields.io/badge/Domain-Embedded%20Systems-blue">
  <img src="https://img.shields.io/badge/Protocol-CAN-green">
  <img src="https://img.shields.io/badge/Language-Embedded%20C-orange">
  <img src="https://img.shields.io/badge/Microcontroller-ARM7-red">
</p>

---

## 📌 Project Overview

<img align="right" width="260" src="https://cdn-icons-png.flaticon.com/512/743/743922.png">

The **Real-Time Vehicle Status Monitoring System** is an embedded systems project developed to improve vehicle safety and diagnostics using the **Controller Area Network (CAN) protocol**.

This system continuously monitors important vehicle parameters like:

* ⛽ Fuel Level
* 🚦 Indicator Status
* 💥 Accident Detection
* 🎈 Airbag Deployment Status

All data is transmitted between multiple embedded nodes using CAN communication and displayed on an LCD dashboard in real time.

---

## 🎯 Aim of the Project

To enhance vehicle safety by designing a distributed embedded system that monitors vehicle conditions in real time and enables reliable communication between subsystems using CAN protocol.

---

## ✨ Key Features

<img align="right" width="260" src="https://cdn-icons-png.flaticon.com/512/1048/1048953.png">

✔ Real-time vehicle parameter monitoring
✔ Multi-node CAN communication
✔ Fuel level sensing using ADC
✔ Accident detection using accelerometer
✔ Airbag deployment status indication
✔ Indicator control using external interrupts
✔ LCD-based vehicle dashboard display
✔ Reliable and fast data transmission

---

## 🧠 System Architecture

The system consists of **three interconnected CAN nodes**, each responsible for specific vehicle operations.

### 🔹 1️⃣ Main Node

**Responsibilities:**

* Continuously reads accelerometer data
* Detects accident using threshold limits
* Displays vehicle status on LCD
* Sends indicator control signals
* Receives fuel data from Fuel Node

**Displays on LCD:**

* Airbag Status
* Fuel Level
* Accident Detection Status
* System Condition

---

### 🔹 2️⃣ Indicator Node

**Responsibilities:**

* Receives commands from Main Node via CAN
* Controls vehicle indicator LEDs
* Performs signal blinking operations

---

### 🔹 3️⃣ Fuel Node

**Responsibilities:**

* Reads fuel sensor data using ADC
* Calculates fuel percentage
* Sends fuel data to Main Node via CAN

---

## 🛠 Hardware Requirements

<img align="right" width="260" src="https://cdn-icons-png.flaticon.com/512/2103/2103633.png">

| Component               | Purpose               |
| ----------------------- | --------------------- |
| LPC2129 Microcontroller | Main processing unit  |
| MCP2551 CAN Transceiver | CAN communication     |
| LCD Display             | Dashboard display     |
| MMA7660 Accelerometer   | Accident detection    |
| Fuel Gauge Sensor       | Fuel measurement      |
| LEDs                    | Indicator signals     |
| Switches                | External interrupts   |
| USB–UART Converter      | Programming interface |

---

## 💻 Software Requirements

| Software     | Purpose                          |
| ------------ | -------------------------------- |
| Embedded C   | Firmware development             |
| Keil µVision | Code compilation & debugging     |
| Flash Magic  | Microcontroller programming tool |

---

## ⚙ Technologies Used

* 🔹 Embedded C Programming
* 🔹 CAN Communication Protocol
* 🔹 ARM7 Microcontroller Architecture
* 🔹 ADC (Analog to Digital Conversion)
* 🔹 External Interrupt Handling
* 🔹 Sensor Interfacing
* 🔹 Real-Time Embedded Systems

---

## 🔄 Working Principle

<img align="right" width="260" src="https://cdn-icons-png.flaticon.com/512/2942/2942789.png">

### Step 1: Fuel Monitoring

Fuel sensor reads analog value → ADC converts to digital → Fuel % sent via CAN.

### Step 2: Accident Detection

Accelerometer continuously monitors vibrations and tilt.

### Step 3: Emergency Detection

If acceleration exceeds safety threshold:

* Accident detected
* Airbag deployment triggered
* Warning displayed on LCD

### Step 4: Indicator Control

External interrupts from switches send signals to Indicator Node via CAN.

### Step 5: Dashboard Display

All vehicle data is shown on LCD in real time.

---

## 📟 LCD Output Parameters

* Fuel Percentage
* Airbag Status (Deployed / Safe)
* Accident Detection Alert
* Indicator Status
* Vehicle Condition Messages

---

## 🎓 Learning Outcomes

Through this project, I gained strong knowledge in:

✅ Embedded C Programming
✅ CAN Protocol Implementation
✅ LPC2129 Microcontroller Architecture
✅ ADC & Sensor Interfacing
✅ External Interrupt Handling
✅ Multi-Node Embedded System Design
✅ Real-Time Data Processing

---

## 🚀 Applications

<img align="right" width="260" src="https://cdn-icons-png.flaticon.com/512/1995/1995574.png">

🚘 Automotive Safety Systems
📡 Vehicle Diagnostics
🚚 Fleet Management
⚠ Accident Detection & Alert Systems
🛠 Real-Time Vehicle Health Monitoring

---

## 🔮 Future Enhancements

* 📍 GPS-based Accident Location Tracking
* 📶 GSM Module for Emergency Alerts
* 📱 Mobile App Integration
* ☁ Cloud-Based Vehicle Diagnostics
* 🎥 Camera-Based Driver Monitoring
* 🔋 Advanced Sensor Integration

---

## 👨‍💻 Author

**Vijay Kumar**
🎓 B.Tech – Electronics & Communication Engineering
💼 Embedded Systems & Software Developer
📍 India

---

## ⭐ Project Status

✅ Completed
🧪 Tested on Hardware
📡 CAN Communication Verified
📟 Real-Time Monitoring Successful

---

## 📷 Project Demonstration

*(You can add your project photos here)*

```
![Project Setup](images/setup.jpg)
![LCD Output](images/lcd_output.jpg)
![Hardware Kit](images/hardware.jpg)
```

---

## 🔗 How to Run the Project

1️⃣ Compile code using Keil µVision
2️⃣ Generate HEX file
3️⃣ Flash into LPC2129 using Flash Magic
4️⃣ Power the hardware kit
5️⃣ Observe real-time vehicle data on LCD

---

## 🌟 Show Your Support

If you like this project, give it a ⭐ on GitHub!

---

> 💡 *This project demonstrates practical implementation of embedded systems, real-time monitoring, and automotive communication networks — making it highly relevant for automotive and IoT industries.*
