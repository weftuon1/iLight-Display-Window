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
![system architecture][0]

## Hardware and Software Setup

### Required Hardware
- 1 ARC IoT Development Kit
- 1 Base Shiled V2
- 2 Servo Motor
- 1 Ligt Sensor
- 1 Webcam
- 1 Raspberry Pi 3
- 1 Grove Base Hat for Raspberry Pi
- 8 White LED
- 1 Wireless Dual-Band Mini USB Adapter(EW-7811UTC)

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
![ARC connection][1]

2. RPi
   - Connect to ARC IoTDK via uart.
   - Connect to PC via USB AP.
   - Connect camera via USB port
![RPi connection][2]

## User Manual

### Before Running This Application
- Environment: In door with proper lightness
- On RPi: Install opencv, fswebcam, pyserial. Check ls /dev/video? before using fswebcam command.
- On ARC IoTDK: Set parameters for location to degree transformation.

### Run This Application
- make run



[0]: https://github.com/weftuon1/iLight-Display-Window/blob/master/doc/architecture_system_pic.png		"system architecture"
[1]: https://github.com/weftuon1/iLight-Display-Window/blob/master/doc/ARC_connection.png	"ARC connection"
[2]: https://github.com/weftuon1/iLight-Display-Window/blob/master/doc/RPi_connection.png	"RPi connectoin"

[30]: https://www.seeedstudio.com/Grove-Base-Hat-for-Raspberry-Pi.html
[31]: https://www.seeedstudio.com/Base-Shield-V2.html
