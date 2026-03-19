🚗 Real-Time Vehicle Status Monitoring System using CAN Protocol
📌 Project Overview

The Real-Time Vehicle Status Monitoring System is an embedded systems project designed to improve vehicle safety and diagnostics using the Controller Area Network (CAN) protocol.

This system monitors and displays critical vehicle parameters such as fuel level, indicator status, and airbag deployment status in real time using multiple interconnected nodes.

🎯 Aim

To enhance vehicle safety and real-time monitoring by implementing a distributed embedded system using CAN protocol for reliable communication between vehicle subsystems.

💡 Key Features

✔ Real-time vehicle parameter monitoring
✔ Fuel level measurement and display
✔ Accident detection using accelerometer sensor
✔ Automatic airbag deployment indication
✔ Indicator control using external interrupts
✔ Multi-node communication using CAN protocol
✔ LCD dashboard display

🧠 System Architecture

The project is divided into three CAN nodes:

🔹 Main Node

Reads accelerometer data continuously

Detects accident based on threshold limits

Displays:

Airbag status

Fuel level

Vehicle condition

Sends indicator control signals via CAN

Receives fuel data from Fuel Node

🔹 Indicator Node

Receives signals from Main Node via CAN

Controls vehicle indicator LEDs

🔹 Fuel Node

Reads fuel gauge sensor using ADC

Sends fuel percentage data to Main Node via CAN

🛠 Hardware Requirements

Microcontroller: LPC2129

CAN Transceiver: MCP2551

LCD Display

MMA7660 Accelerometer Sensor

Fuel Gauge Sensor

LEDs

Switches (External Interrupts)

USB-to-UART Converter

💻 Software Requirements

Embedded C Programming

IDE: Keil µVision

Flashing Tool: Flash Magic

⚙ Technologies Used

Embedded C

CAN Communication Protocol

ARM7 Microcontroller Architecture

ADC (Analog to Digital Conversion)

Interrupt Handling

Sensor Interfacing

Real-Time Embedded Systems

🔄 Working Principle

Fuel sensor data is read using ADC and transmitted via CAN.

Accelerometer monitors vehicle tilt and sudden movements.

If acceleration exceeds safety threshold:

Accident is detected

Airbag deployment status is displayed

External interrupts trigger indicator signals.

All vehicle data is displayed on an LCD dashboard in real time.

📟 Output Displayed on LCD

Fuel Percentage

Airbag Status (Deployed / Safe)

Accident Detection Status

Indicator Signals

🎓 Learning Outcomes

Through this project, the following concepts were learned:

Embedded C programming

CAN protocol implementation

LPC2129 microcontroller architecture

ADC interfacing

External interrupt handling

Sensor data processing

Multi-node embedded system design

🚀 Applications

Automotive safety systems

Vehicle health monitoring

Fleet management systems

Real-time vehicle diagnostics

Accident detection and alert systems

👨‍💻 Author

Vijay Kumar
Electronics and Communication Engineering
Embedded Systems Developer
