# 🧬 Arduino-Based PCR Machine Prototype
> A low-cost, open-source Electrically Controlled PCR Machine (Thermocycler) for DNA amplification.

## 🎓 Academic Context
This project was developed for the **EEE 4518: Electrical and Electronic Workshop** course at the **Islamic University of Technology (IUT)**, Gazipur, Bangladesh.

**Built by Team Cor Machina:**
* Mubeen Raisul Hassan Chowdhury
* Nahid Sadique Tasin
* Hussaib Hazzil Abbasi
* M Faiad Faisal Sarthok
* An-Nafi Ahasan

---

## 📖 Project Overview
This repository contains the hardware design and control software for a microcontroller-based Polymerase Chain Reaction (PCR) thermocycler. Designed to precisely automate the temperature cycles (denaturation, annealing, and extension) required for DNA amplification, this prototype serves as an accessible, functional alternative to expensive commercial PCR machines.

## ✨ Key Features
* **Programmable Thermal Cycling:** Customizable temperature profiles and time durations for different PCR stages.
* **Closed-Loop Control:** Real-time thermal feedback using a MAX6675 thermocouple to automatically maintain target temperatures.
* **Bidirectional Thermal Actuation:** Utilizes high-power resistive heating and Peltier-based thermoelectric cooling for rapid temperature transitions.
* **Real-Time Monitoring:** An I2C LCD provides continuous user interface feedback on the current block temperature, cycle phase, and operational status.

## 🛠️ Hardware Architecture
### 1. Control & Sensing
* Arduino Uno (Central Control Logic)
* MAX6675 Temperature Sensor with K-Type Thermocouple
* 2-Channel Relay Module
* 16x2 I2C LCD Display

### 2. Thermal System
* Custom Aluminum Thermal Block (drilled for PCR tubes)
* Thermoelectric Cooler (Peltier Module) with Aluminum Heatsink
* High-Power Heating Resistors (10W, 10Ω)
* 12V BLDC Cooling Fan

### 3. Power System
* 12V DC 10A Switch Mode Power Supply (SMPS)
* DC-DC Buck Converter (12V to 9V step-down)
* 9V Rechargeable Backup Battery (UPS for logic retention)

## ⚙️ Working Principle
The system is primarily powered by a 12V SMPS, driving the high-current thermal components, while a buck converter safely powers the Arduino logic circuit. The Arduino Uno processes real-time temperature data from the thermocouple and operates a closed-loop feedback system via the relay module:
* **🔥 Heating:** Relay 1 activates the high-power resistors mounted to the thermal block.
* **❄️ Cooling:** Relay 2 activates the Peltier module and BLDC fan, rapidly drawing heat away from the block.

## 🌡️ Thermal Cycling Profile
The system is programmed to successfully execute the following sequential profile to replicate the biological PCR process:

1. **Initialization:** `95°C` for `5 minutes`
2. **Denaturation:** `95°C` for `40 seconds`
3. **Annealing:** `54°C` for `40 seconds`
4. **Extension:** `72°C` for `50 seconds` 
   > *(Steps 2-4 repeat for 35 total cycles)*
5. **Finalization:** `72°C` for `5 minutes`
