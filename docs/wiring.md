# Wiring Guide for the Temperature and Humidity Monitor

This document provides detailed wiring instructions for assembling the temperature and humidity monitor using the Arduino Nano. Below is the connection schematic for each component involved in the project.

## Components
- Arduino Nano
- KY-015 DHT11 Temperature and Humidity Sensor
- SSD1306 Display
- RGB LED (3 convenient resistors)
- Micro SD TF SPI Reader
- Push Button
- Wires
- USB Wire for programming and power supply

## RGB LED Connections

Connect the RGB LED to the Arduino Nano as follows:

- **Red Pin**
  - Connect to digital pin D3 through a 140-ohm resistor (adjust based on your LED's specifications).
- **Green Pin**
  - Connect to digital pin D5 through a 100-ohm resistor (adjust based on your LED's specifications).
- **Blue Pin**
  - Connect to digital pin D6 through a 100-ohm resistor (adjust based on your LED's specifications).
- **Common Cathode (GND)**
  - Connect to the GND (ground) pin on the Arduino Nano.

## KY-015 DHT11 Sensor Connections

Connect the KY-015 DHT11 temperature and humidity sensor to the Arduino Nano as follows:

- **VCC**
  - Connect to the 5V pin on the Arduino Nano.
- **GND**
  - Connect to a GND pin on the Arduino Nano.
- **OUT**
  - Connect to digital pin D2 on the Arduino Nano.

## SD Card Module Connections

Wire the SD card module to the Arduino Nano using the following pins:

- **VCC**
  - Connect to the 5V pin on the Arduino Nano.
- **GND**
  - Connect to a GND pin on the Arduino Nano.
- **MISO**
  - Connect to digital pin D12 on the Arduino Nano.
- **MOSI**
  - Connect to digital pin D11 on the Arduino Nano.
- **SCK**
  - Connect to digital pin D13 on the Arduino Nano.
- **CS**
  - Connect to digital pin D10 on the Arduino Nano.

## OLED Display (SSD1306) Connections

Connect the SSD1306 OLED display to the Arduino Nano via the I2C interface:

- **VCC**
  - Connect to the 5V pin on the Arduino Nano.
- **GND**
  - Connect to a GND pin on the Arduino Nano.
- **SCL**
  - Connect to analog pin A5 on the Arduino Nano.
- **SDA**
  - Connect to analog pin A4 on the Arduino Nano.

## Push Button Connections

Connect the push button to the Arduino Nano as follows:

- **One Side**
  - Connect to digital pin D3 on the Arduino Nano.
- **Other Side**
  - Connect to a GND pin on the Arduino Nano.

## Summary

Ensure all connections are secure and double-check each connection before powering the Arduino Nano. This setup provides a comprehensive guide to assembling the temperature and humidity monitor. For further assistance, refer to the component datasheets and Arduino Nano documentation.
