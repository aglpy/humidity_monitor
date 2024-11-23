// Humidity Sensor
#include <SPI.h>

#include <ssd1306.h>
#include <dht_nonblocking.h>
#include <SD.h>

#include "config.h"

struct Color {int r, g, b;};

struct SensorResult {
    float temperature;
    float humidity;
};

DHT_nonblocking dht_sensor(SENSOR, DHT_TYPE_11);
File dataFile;

static SensorResult sensorResult;

Color _red = {255, 0, 0};
Color _green = {0, 255, 0};
Color _blue = {0, 0, 255};
Color _yellow = {200, 255, 0};
Color _black = {0, 0, 0};

bool sdError = false;

void _setLedColor(Color color) {
    analogWrite(LED_RED, color.r);
    analogWrite(LED_GREEN, color.g);
    analogWrite(LED_BLUE, color.b);
}

static unsigned long lastMeasure = 0;
bool _readyToMeasure() {
    unsigned long currentMillis = millis();
    return (currentMillis - lastMeasure >= 3000ul) || (currentMillis < lastMeasure);
}

void _writeRow(String filename, String row) {
  dataFile = SD.open(filename, FILE_WRITE);
  if (dataFile) {
    dataFile.println(row);
    dataFile.close();
  }
}

void _turnOffScreen() {
  ssd1306_displayOff();
}

void _turnOnScreen() {
  ssd1306_displayOn();
}

void setupLed() {
    pinMode(LED_RED, OUTPUT);
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_BLUE, OUTPUT);
    analogWrite(LED_RED, 0);
    analogWrite(LED_GREEN, 0);
    analogWrite(LED_BLUE, 0);
}

void humidityHigh() {
    _setLedColor(_green);
}

void humidityLow() {
    _setLedColor(_yellow);
}

void temperatureHigh() {
    _setLedColor(_red);
}

void temperatureLow() {
    _setLedColor(_blue);
}

void turnOffLed() {
    _setLedColor(_black);
}

void measure() {
  if(_readyToMeasure()) {
    while (!dht_sensor.measure(&sensorResult.temperature, &sensorResult.humidity)) delay(10);
    lastMeasure = millis();
  }
}

void initializeSDCard() {
  sdError = !SD.begin(SD_CHIP_SELECT);
}

void writeCSVHead() {
  if (!SD.exists("data.csv")) {
    String compilationTime = String(__DATE__) + " " + __TIME__;
    compilationTime.replace(":", " ");
    compilationTime.replace(" ", "_");
    _writeRow("data.csv", compilationTime + ",temperature,humidity");
  }
  if (!SD.exists("logs.csv")) {
    String compilationTime = String(__DATE__) + " " + __TIME__;
    compilationTime.replace(":", " ");
    compilationTime.replace(" ", "_");
    _writeRow("logs.csv", compilationTime + ",action");
  }
}

void writeResultCSV() {
  String row = String(millis()) + "," + String(sensorResult.temperature) + "," + String(sensorResult.humidity);
  _writeRow("data.csv", row);
}

void writeLog(String action) {
  String row = String(millis()) + "," + action;
  _writeRow("logs.csv", row);
}

void initializeScreen() {
  ssd1306_128x64_i2c_init();
  ssd1306_clearScreen();
  ssd1306_setFixedFont(ssd1306xled_font8x16);
}

void displayData() {
  char buffer[2];
  ssd1306_setCursor(0, 0);
  ssd1306_print("Temp/humidity");
  ssd1306_setCursor(0, 30);
  int numChars = sprintf(buffer, "%d", (int)sensorResult.temperature);
  if (numChars == 1) {
    ssd1306_print("  ");
  } else {
    ssd1306_print(" ");
  }
  ssd1306_print(buffer);
  ssd1306_print(" i");
  ssd1306_setCursor(23, 33);
  ssd1306_print("   ");
  ssd1306_setCursor(40, 30);
  ssd1306_print("C");
  ssd1306_setCursor(60, 30);
  sprintf(buffer, "%d", (int)sensorResult.humidity);
  ssd1306_print(buffer);
  ssd1306_print(" %");
  ssd1306_setCursor(10, 40);
  if (sdError) {
    ssd1306_print("SD error");
  }
}

void setupButton() {
  pinMode(BUTTON, INPUT_PULLUP);
}

bool showTemperatureLed = false;
void blinkLed() {
  if (ledTack()) {
    showTemperatureLed = !showTemperatureLed;
  }
  if (showTemperatureLed) {
    if (sensorResult.temperature > HIGH_TEMPERATURE) {
      temperatureHigh();
    } else if (sensorResult.temperature < LOW_TEMPERATURE) {
      temperatureLow();
    } else {
      turnOffLed();
    }
  } else {
    if (sensorResult.humidity > HIGH_HUMIDITY) {
      humidityHigh();
    } else if (sensorResult.humidity < LOW_HUMIDITY) {
      humidityLow();
    } else {
      turnOffLed();
    }
  }
}

bool showingMode = true;

int _tickLength = 100;
int _secondTicks = 1000/_tickLength;
int _showingTicks = 10*_secondTicks;
int _ledTicks = (int)(0.5*_secondTicks);
int _minuteTicks = 60*_secondTicks;
void tick() {
  _minuteTicks--;

  if (showingMode) {
    _showingTicks--;
    _ledTicks--;
    if (_showingTicks <= 0) {
      showingMode = false;
      _showingTicks = 10*_secondTicks;
      _turnOffScreen();
      turnOffLed();
    }
  }

  delay(_tickLength);
}

bool ledTack() {
  if (_ledTicks <= 0) {
    _ledTicks = (int)(0.5*_secondTicks);
    return true;
  }
  return false;
}

bool minuteTack() {
  if (_minuteTicks <= 0) {
    _minuteTicks = 60*_secondTicks;
    return true;
  }
  return false;
}

bool someoneLooking() {
  if (!digitalRead(BUTTON)) {
    showingMode = true;
    _showingTicks = 10*_secondTicks;
    writeLog("someone_looking");
    _turnOnScreen();
  }
  return showingMode;
}

void setup() {
    setupLed();
    setupButton(); 
    initializeScreen();
    initializeSDCard();
    writeCSVHead();
}

void loop() {
  if (minuteTack()) {
    if (!sdError) {
      measure();
      writeResultCSV();
    }
  }
  if (someoneLooking()) {
    measure();
    blinkLed();
    displayData();
  }

  tick();
}