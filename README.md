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

<img width="1264" height="843" alt="image" src="https://github.com/user-attachments/assets/3f166850-5287-44e7-82ea-2f15c7c0a05e" />

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


---

## 🔌 Pin Configuration

### 🚌 CAN Interface Pin Configuration

| Signal       | LPC2129 Pin | Description                        |
| ------------ | ----------- | ---------------------------------- |
| RD1 (CAN RX) | P0.25       | CAN Receive input from transceiver |
| TD1 (CAN TX) | P0.24       | CAN Transmit output to transceiver |

---

### 💡 Indicator LED Array Configuration

| Indicator LED | LPC2129 Pin | Description         |
| ------------- | ----------- | ------------------- |
| LED0          | P0.0        | Running pattern LED |
| LED1          | P0.1        | Running pattern LED |
| LED2          | P0.2        | Running pattern LED |
| LED3          | P0.3        | Running pattern LED |
| LED4          | P0.4        | Running pattern LED |
| LED5          | P0.5        | Running pattern LED |
| LED6          | P0.6        | Running pattern LED |
| LED7          | P0.7        | Running pattern LED |

---

### 🎛 External Interrupt Switch Configuration (Indicator Generator Node)

| Switch                 | LPC2129 Pin  | Description                                     |
| ---------------------- | ------------ | ----------------------------------------------- |
| LEFT Indicator Switch  | P0.1 (EINT0) | Generates interrupt for LEFT indicator command  |
| RIGHT Indicator Switch | P0.7 (EINT2) | Generates interrupt for RIGHT indicator command |

---

### ⛽ Fuel Sensor (ADC) Configuration

| Signal             | LPC2129 Pin   | Description                             |
| ------------------ | ------------- | --------------------------------------- |
| Fuel Sensor Output | P0.28 (AD0.1) | Analog input for fuel level measurement |

---

### 📡 Accelerometer (I2C – MMA7660) Configuration

| Signal | LPC2129 Pin | Description    |
| ------ | ----------- | -------------- |
| SDA    | P0.3        | I2C Data Line  |
| SCL    | P0.2        | I2C Clock Line |

---

### 🚨 Airbag / Status Indication LEDs

| Device    | LPC2129 Pin | Description                      |
| --------- | ----------- | -------------------------------- |
| Green LED | P0.21       | Normal vehicle status indication |
| Red LED   | P0.22       | Airbag / crash alert indication  |

---

### 📶 CAN Transmission Activity LED

| Device        | LPC2129 Pin | Description                             |
| ------------- | ----------- | --------------------------------------- |
| TX Status LED | P0.0        | Toggles during CAN message transmission |

---

---

## ⚙ Technologies Used

🔹 Embedded C Programming  
🔹 CAN Communication Protocol  
🔹 ARM7 Microcontroller Architecture  
🔹 ADC (Analog to Digital Conversion)  
🔹 External Interrupt Handling  
🔹 Sensor Interfacing  
🔹 Real-Time Embedded Systems  

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

## 📷 Project Demonstration

<img width="1500" height="1125" alt="image" src="https://github.com/user-attachments/assets/d0add10d-f479-48e8-980e-2dc6fc9829c7" />


This image shows the hardware setup of the Real-Time Vehicle Status Monitoring System using CAN Protocol.

Multiple LPC2129 boards are connected through CAN communication to form different nodes. The system monitors vehicle parameters like fuel level, indicator status, and airbag condition in real time.

The LCD display shows live vehicle data, LEDs indicate signal status, and sensors simulate fuel level and accident detection. This setup demonstrates successful multi-node communication and real-time vehicle monitoring.

📟 LCD Output – Fuel Level Display
<img width="943" height="520" alt="image" src="https://github.com/user-attachments/assets/13a13c1c-c79a-4322-8e32-bc9bb75420d1" />

This image shows the LCD display of the vehicle dashboard.

It indicates the fuel level as 98%, while the indicator and airbag systems are currently in OFF state.
The display confirms proper fuel sensor reading and real-time data update through CAN communication.

📟 LCD Output – Airbag Activation Status
<img width="1045" height="673" alt="image" src="https://github.com/user-attachments/assets/c5c47824-9593-4fc9-989e-83fe827de072" />

This image shows the LCD dashboard displaying vehicle status during an emergency condition.

The airbag system is turned ON, indicating accident detection, while the indicator remains OFF. Fuel level is displayed as 100%.
This confirms proper accident detection and airbag status indication through the CAN-based monitoring system.

📟 LCD Output – Indicator Status Display
![WhatsApp Image 2026-03-19 at 23 23 46](https://github.com/user-attachments/assets/be2fc2d1-813a-4771-9bcb-481762a8dcf3)

This image shows the LCD dashboard displaying the LEFT indicator signal status.
The system activates the left indicator through external interrupt control while continuously monitoring fuel level and airbag status.

This confirms proper indicator control and real-time status update using CAN communication.

📟 LCD Output – Right Indicator Status
<img width="833" height="407" alt="image" src="https://github.com/user-attachments/assets/11a77a3a-2170-42f2-bec8-b1144b1af0ad" />

LCD display showing RIGHT indicator activation with real-time vehicle parameter monitoring.


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

## ✅ Conclusion

The Real-Time Vehicle Status Monitoring System using CAN Protocol was successfully designed and implemented to improve vehicle safety and monitoring. The system effectively enables communication between multiple nodes using CAN protocol to monitor critical vehicle parameters such as fuel level, indicator status, and airbag deployment in real time.

The project demonstrates reliable multi-node communication, accurate sensor interfacing, and efficient real-time data display on an LCD dashboard. Accident detection using an accelerometer and indicator control through external interrupts further enhance the system’s practical automotive applications.

Overall, this project provides strong practical knowledge in embedded systems, microcontroller programming, communication protocols, and real-time automotive system design.

---

## 🚀 Applications

🚘 Automotive Safety Systems  
📡 Vehicle Diagnostics  
🚚 Fleet Management  
⚠ Accident Detection & Alert Systems  
🛠 Real-Time Vehicle Health Monitoring  

---

## 🔮 Future Enhancements

📍 GPS-based Accident Location Tracking  
📶 GSM Module for Emergency Alerts  
📱 Mobile App Integration  
☁ Cloud-Based Vehicle Diagnostics  
🎥 Camera-Based Driver Monitoring  
🔋 Advanced Sensor Integration  

---

## 👨‍💻 Author

**Vijay Kumar**
🎓 B.Tech – Electronics & Communication Engineering  
💼 Embedded Systems & Trainee  
📍 India  

---

## ⭐ Project Status

✅ Completed  
🧪 Tested on Hardware  
📡 CAN Communication Verified  
📟 Real-Time Monitoring Successful  

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
