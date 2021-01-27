#include "Arduino_SensorKit.h"

void setup() {
  // Serial Setup
  Serial.begin(9600);

  // DHT Temperature and Humidity Sensor Setup
  Environment.begin();

  // OLED Display Setup
  Oled.begin();
  Oled.setFlipMode(true);

  // Barometer pressure Sensor Setup
  Pressure.begin();
}

void loop() {
  // Set OLED font type
  Oled.setFont(u8x8_font_chroma48medium8_r);
  //  Oled.setFont(u8x8_font_chroma48medium8_r);

  // Set starting cursor (1st Line)
  Oled.setCursor(0, 0);
  // Print Weather Forecast introductory text
  Oled.print("Weather Forecast");

  // Set cursor (2nd Line)
  Oled.setCursor(0, 1);
  // Get and print Barometer temperature sensor data.
  Oled.print("Temp: ");
  Oled.print(Pressure.readTemperature());
  Oled.print(" C");

  // Set cursor (3rd Line)
  Oled.setCursor(0, 2);
  // Get and Display DHT Humidity Sensor data.
  Oled.print("Humid: ");
  Oled.print(Environment.readHumidity());
  Oled.print(" %");

  // Set cursor (4th Line)
  Oled.setCursor(0, 3);
  // Get and display Barometer atmospheric pressure sensor data.
  Oled.print("Pres: ");
  Oled.print(Pressure.readPressure());
  Oled.print(" Pa");

  // Set cursor (5th Line)
  Oled.setCursor(0, 4);
  // Get and display altitude sensor data
  Oled.print("Alt: ");
  Oled.print(Pressure.readAltitude());
  Oled.print(" m");

  // Get and display DHT temperature sensor data.
  //  Oled.setCursor(0, 1);
  //  Oled.print("DHT Temp: ");
  //  Oled.print(Environment.readTemperature());
  //  Oled.print("C");
  Oled.refreshDisplay();
  delay(1000);
}
