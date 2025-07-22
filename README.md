# Sumo Bot — Autonomous & Remote-Controlled Robot

## Overview

This project is an **autonomous competitive sumo robot** built using the ATmega32 microcontroller. The robot supports both **autonomous** and **manual remote-control modes**, leveraging IR sensors for edge detection, opponent tracking, and user input. It was designed for real-time decision-making in sumo-style competitions.

---

## Features

- 🔁 **Dual Mode Operation**: Autonomous mode for sumo battles and manual control using an IR remote.
- 🧠 **Embedded Control System**: Programmed in C with real-time decision logic and modular state machines.
- ⚙️ **Motor Control**: PWM-based bi-directional motor driving using TB6612FNG H-bridge.
- ⚡ **Power Management**: Single 7.4V 450mAh Li-ion battery regulated to support sensors, logic, and motors.
- 🧲 **Edge Detection**: Four QRE1113 IR reflectance sensors detect white lines around the arena.
- 🎯 **Opponent Detection**: Three GP2Y0A21YK0F Sharp analog IR distance sensors detect opponents in forward and diagonal directions.
- 🎮 **Remote Control**: IR receiver with custom command decoding for manual input and mode switching.

---

## Hardware Components

| Component                          | Quantity | Purpose                         |
|-----------------------------------|----------|---------------------------------|
| ATmega32 Microcontroller          | 1        | Core processing unit            |
| QRE1113 IR Reflectance Sensors    | 4        | Edge/line detection             |
| Sharp GP2Y0A21YK0F IR Sensors     | 3        | Opponent distance sensing       |
| TB6612FNG Motor Driver            | 1        | Motor direction and speed control |
| 7.4V 450mAh Li-ion Battery        | 1        | Power supply                    |
| IR Receiver Module                | 1        | Remote control input            |
| DC Motors                         | 2        | Locomotion                      |

---
## Schematic

---

## Software Highlights

- **Language**: C (AVR-GCC)
- **Control Architecture**:
  - Modular finite state machine (FSM) to handle autonomous behavior
  - Manual override with external interrupt for IR remote input
- **Motor Interface**:
  - Hardware PWM on Timer1 for speed control
  - Direction control via TB6612FNG
- **Sensor Processing**:
  - Analog reading for opponent tracking
  - Edge detection thresholding and filtering
- **IR Remote Protocol**:
  - NEC-style IR decoding via pin change interrupts
  - Command mapping for forward, reverse, turn, and mode switch

---

## PCB & Circuit Design

- **Custom PCB** integrating:
  - Microcontroller with breakout for all GPIO
  - TB6612FNG motor driver circuit
  - Voltage regulation (LDO for 5V and/or 3.3V as required)
  - Power and sensor connectors
- Reverse polarity protection and efficient power routing were considered.

---

## Status

✅ Fully functional prototype  
🔋 Runtime: ~3-5 minutes continuous on full charge  

---

## Future Improvements

- Improve power efficiency with voltage regulator
- Larger battery 
- Migrate to ATmega328p or STM32 for better I/O availability and power

---

## License

This project is open-source under the MIT License.

---

## Author

Terence Matsune  
Embedded Systems & Robotics Enthusiast  
