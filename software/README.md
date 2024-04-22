# Software for the Temperature and Humidity Monitor

This directory contains the source code for the Temperature and Humidity Monitor project, which utilizes an Arduino Nano, KY-012 DHT11 sensor, OLED SSD1306 display, RGB LED, SD card module, and a push-button.

## Structure

- `humidity_monitor\humidity_monitor.ino`: The main Arduino sketch file.
- `config.h`: Configuration file containing pin assignments and other global settings.
- `requirements.txt`: Necessary third-party libraries.

## Setup Instructions

1. **Install Arduino IDE or any other IDE extension**: Ensure you have the latest version of the Arduino IDE installed on your computer. Download it from [Arduino Website](https://www.arduino.cc/en/Main/Software).

2. **Clone the Repository**: Clone this repository to your local machine or download the zip file and extract it.

    ```bash
    git clone https://github.com/yourusername/Temperature-Humidity-Monitor.git
    cd Temperature-Humidity-Monitor/software
    ```

3. **Library Dependencies**: The following libraries are needed for this project. Ensure they are installed:
    - `DHT` for interfacing with the DHT11 sensor.
    - `SSD1306` for the OLED display.
    - `SD` for the SD card module.

    You need to add these libraries to your Arduino IDE. Follow these steps:
    
    - Open Arduino IDE, go to Sketch > Include Library > Add .ZIP Library...
    - Navigate to each and select the library folder.

4. **Load the Sketch**: Open the `humidity_monitor.ino` file in Arduino IDE.

5. **Upload to Arduino**: Connect your Arduino Nano to your computer via USB. Select the correct board and port in Arduino IDE, then upload the sketch.
