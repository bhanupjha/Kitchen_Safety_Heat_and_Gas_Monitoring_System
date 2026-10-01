# Kitchen Safety Heat and Gas Monitoring System

## Project Overview

The Kitchen Safety Heat and Gas Monitoring System is an embedded safety application developed for the NXP LPC2148 ARM7TDMI-S microcontroller.
The system continuously samples ambient temperature via an analog LM35 sensor (10-bit ADC CH1) and monitors combustible gas concentration using an MQ2 sensor.

## Features

- Temperature monitoring using LM35
- Gas leakage detection using MQ2
- 16x2 LCD display
- RTC-based date and time
- Buzzer and LED alert
- Safety event recording
- Periodic display of the latest safety event
- Password-protected edit mode
- Temperature threshold editing
- RTC time/date editing
- Password change option
- Keypad-based menu

## Hardware Requirements

- LPC2148
- 16x2 LCD
- 4x4 Matrix Keypad
- LM35
- MQ2
- Buzzer
- LEDs
- Switches
- USB-UART / DB-9 cable

## Software Requirements

- Embedded C
- Keil µVision
- Flash Magic
- Proteus (for simulation/testing)

## System Block Diagram

![Block Diagram](project_img/Block_diagram.jpg)

## Flowchart

![Flowchart](project_img/Flowchart.jpg)

## Project Workflow

1. Initialize LPC2148 peripherals and required modules.
2. Read temperature from LM35.
3. Read gas level from MQ2.
4. Display sensor values and RTC information.
5. Compare sensor values with configured thresholds.
6. Generate an alert when an unsafe condition is detected.
7. Store the latest safety event with RTC timestamp.
8. Periodically display the latest event.
9. Allow secure parameter editing through Switch1 and keypad.
10. Return to normal monitoring mode.

## Project Demonstration

### Hardware Demo
[▶️ Watch Hardware Demonstration](https://drive.google.com/file/d/13GhJ-6IEEeRoyB-XdcSyzsBExra1H6uY/view?usp=sharing)

### simulation Demo [Lpc2124]
[▶️ Watch Simulation Demonstration](https://drive.google.com/file/d/1YwytDOk2-eklzklUDdrZADGpv8nrLNAr/view?usp=sharing)

## Security / Edit Mode

Switch1 enters the secure edit mode.

The user must enter the correct password before modifying system parameters.

Available options include:

- Edit RTC
- Edit temperature threshold
- Change password
- Exit

After three incorrect password attempts, the system enters a temporary
lock condition.

## Project Structure

```text
Kitchen_Safety_Heat_and_Gas_Monitoring_System/
│
├── Header_file/
│ ├── LCD.h
│ ├── ADC.h
│ ├── RTC.h
│ └── ...
│
├── Source_file/
│ ├── main.c
│ ├── LCD.c
│ ├── ADC.c
│ ├── RTC.c
│ └── ...
│
├──proteus_simulation/
|  |── kitchen_safety.DSN
|
├── project_img/
│ ├── block_diagram.png
│ ├── flowchart.png
│
│
└── README.md
```

## Author

Bhanu prakash
