# 智慧燈控展示窗 iLight-Display-Window
IoT Devices with ARC IoTDK aiming to light on the object in display window. Perfectly brings out the beauty of exhibit.

* [Introduction](#introduction)
	* [Function](#function)
	* [System Architecture](#system-architecture)
* [Hardware and Software Setup](#hardware-and-software-setup)
	* [Required Hardware](#required-hardware)
	* [Required Software](#required-software)
	* [Hardware Connection](#hardware-connection)
* [User Manual](#user-manual)
	* [Before Running This Application](#before-running-this-application)
	* [Run This Application](#run-this-application)

## Introduction
**iLight Display Window —— Light up your life!**

This project is aiming to produce a display window that can control led light automatically. No matter how does environment light shed around our object, it can perfectly show the beauty of exhibit.

### Function
- **Detecting lightness of display window**
- **Adjusting the luminance of LED and the position to light on**
- **Monitoring exhibit via camera**

### System Architecture
![image](https://github.com/weftuon1/iLight-Display-Window/blob/master/src/system_pic.png)

## Hardware and Software Setup

### Required Hardware
- 1 ARC IoT Development Kit
- 2 Servo Motor
- 1 Ligt Sensor
- 1 Webcam
- 1 Raspberry Pi 3
- 8 White LED

### Required Software
- Metaware or ARC GNU Toolset
- Serial port terminal, such as putty, MobaXterm or CuteCom

### Hardware Connection
1. ARC IoTDK
   - Connect to PC via USB port.
   - Connect to RPi via uart port(pin IO0, IO1, GND).
   - Connect to two servos via pin IO2, IO4, GND, VCC.
   - Connect to LED vio pin IO3, GND.
   - Connect to light sensor via pin AD0, GND, VCC.

2. RPi
   - Connect to ARC IoTDK via uart.
   - Connect to PC via wireless network card.

## User Manual

### Before Running This Application

### Run This Application
