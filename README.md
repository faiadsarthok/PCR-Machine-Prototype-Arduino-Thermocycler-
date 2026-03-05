# Arduino-Based PCR Machine Prototype

## Project Overview
This repository contains the hardware design and control software for a low-cost, microcontroller-based Polymerase Chain Reaction (PCR) thermocycler. Designed to precisely automate the temperature cycles (denaturation, annealing, and extension) required for DNA amplification, this prototype serves as an accessible, functional alternative to expensive commercial PCR machines. 

## Key Features
* **Programmable Thermal Cycling:** Customizable temperature profiles and time durations for different PCR stages.
* **Closed-Loop Control:** Real-time thermal feedback using a MAX6675 thermocouple to automatically maintain target temperatures.
* **Bidirectional Thermal Actuation:** Utilizes high-power resistive heating and Peltier-based thermoelectric cooling for rapid temperature transitions.
* **Real-Time Monitoring:** An I2C LCD provides continuous feedback on the current block temperature and cycle phase.

## Hardware Architecture
* **Control & Sensing:** Arduino Uno, MAX6675 Temperature Sensor (K-Type Thermocouple), 2-Channel Relay Module, 16x2 I2C LCD.
* **Thermal System:** Custom Aluminum Thermal Block, Thermoelectric Cooler (Peltier) with Heatsink, High-Power Heating Resistors (10W, 10Ω), 12V BLDC Cooling Fan.
* **Power System:** 12V DC 10A SMPS, DC-DC Buck Converter (12V to 9V step-down), 9V Rechargeable Backup Battery.

## Working Principle
The system is powered by a 12V SMPS, driving the high-current thermal components, while a buck converter safely powers the control logic. The Arduino Uno processes real-time temperature data and operates a closed-loop feedback system via a relay module:
* **Heating:** Relay 1 activates the high-power resistors mounted to the thermal block.
* **Cooling:** Relay 2 activates the Peltier module and BLDC fan, quickly drawing heat away from the block.

## Thermal Cycling Profile
The system is programmed to successfully execute the following sequential profile to replicate the biological PCR process:
1. **Initialization:** 95°C for 5 minutes.
2. **Denaturation:** 95°C for 40 seconds.
3. **Annealing:** 54°C for 40 seconds.
4. **Extension:** 72°C for 50 seconds. *(Steps 2-4 repeat for the required number of cycles)*
5. **Finalization:** 72°C for 5 minutes.
