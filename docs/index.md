# Temperature and Humidity Monitor Documentation

## Introduction
This document provides a comprehensive guide to assembling, programming, and using the Arduino Nano-based temperature and humidity monitor.

## Components
- Arduino Nano
- KY-015 DHT11 Temperature and Humidity Sensor
- SSD1306 Display
- RGB LED (3 convenient resistors)
- Micro SD TF SPI Reader
- Push Button
- Wires
- USB Wire for programming and power supply

## Circuit Assembly
### Schematics
Refer to the [schematic.pdf](../hardware/schematics/TH_Monitor_schematic.pdf) file for details on how to connect each component.

### Assembly
1. Connect the KY-015 DHT11 sensor to pin D2 of the Arduino.
2. Connect the OLED display using I2C.
3. Assign pins for the RGB LED and the button.
4. Install the SD card reader on the available SPI.

## Programming
### Initial Setup
1. Install the necessary libraries as indicated in the `/software/requirements.txt` directory.
2. Modify the `config.h` file to change pins if necessary.

### Code Upload
Upload the `humidity_monitor.ino` to the Arduino using the Arduino IDE.

## Using the Monitor
Power on the device and you should see temperature and humidity readings on the OLED display for 10 seconds. Push the button to show again another 10 seconds.

## Technical Support
For further assistance, you can open an issue on GitHub.
