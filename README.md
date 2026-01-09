# Voice-controlled-Wheelchair
Arduino Smart Wheelchair with Obstacle Avoidance &amp; Dual Control An Arduino-based robotics project designed for a wheelchair prototype featuring ultrasonic-based safety braking, HC-05 Bluetooth remote control, and a physical switch override for manual forward movement.
# Arduino Smart Wheelchair with Obstacle Avoidance

An intelligent wheelchair control system featuring dual-mode operation (Bluetooth and Physical Switch) and automated safety braking using ultrasonic sensing.

---

## 📖 Project Overview
This project is designed to enhance mobility through a hybrid control system. It allows a user to control a motorized wheelchair via a Bluetooth-connected smartphone or a physical override switch. To ensure safety, the system integrates an ultrasonic sensor that acts as an automatic emergency brake if an obstacle is detected within 15cm.

### Key Features
* **Dual Control:** Seamlessly switch between Bluetooth commands and physical switch inputs.
* **Safety First:** Automatic obstacle detection and collision avoidance.
* **Directional Feedback:** Integrated Servo motor to indicate or assist in turning.
* **Real-time Monitoring:** Serial debugging output for distance and command status.

---

## 🛠 Hardware Requirements
* **Microcontroller:** Arduino Uno (or compatible)
* **Motor Driver:** L298N Dual H-Bridge
* **Bluetooth Module:** HC-05 or HC-06
* **Distance Sensor:** HC-SR04 Ultrasonic Sensor
* **Actuators:** 2x DC Motors, 1x Micro Servo (SG90)
* **Power:** 7.4V - 12V Li-ion Battery pack

---

## 🔌 Pin Mapping

| Component | Arduino Pin | Description |
| :--- | :--- | :--- |
| **Bluetooth RX** | 10 | Software Serial TX |
| **Bluetooth TX** | 11 | Software Serial RX |
| **Servo Motor** | 3 | Directional Control |
| **Motor A (In1, In2)**| 4, 5 | Left Side Motors |
| **Motor B (In3, In4)**| 6, 7 | Right Side Motors |
| **Enable Pins (ENA, ENB)**| 8, 9 | PWM Speed Control (High) |
| **Ultrasonic Trig** | 12 | Trigger Pulse |
| **Ultrasonic Echo** | 13 | Echo Return |
| **Forward Switch** | A0 | Manual Forward Override |

[Image of L298N motor driver Arduino connection diagram]

---

## 🕹 Control Logic

### 1. Manual Mode (Physical Switch)
When the switch connected to **A0** is flipped (HIGH), the wheelchair moves forward automatically. The system will still check the ultrasonic sensor; if an object is closer than 15cm, the motors will not engage.

### 2. Bluetooth Mode
When the physical switch is OFF, the system listens for the following characters via Bluetooth:
* **'F'**: Move Forward (Safety check active)
* **'B'**: Move Backward
* **'L'**: Stop, Turn Servo to 180°, and Rotate Left
* **'R'**: Stop, Turn Servo to 0°, and Rotate Right
* **'S'**: Stop all motors and center Servo
