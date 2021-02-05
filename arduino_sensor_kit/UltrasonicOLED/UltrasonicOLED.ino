#include "Arduino_SensorKit.h"
//#include <U8g2lib.h>
//U8X8_SSD1306_128X64_NONAME_HW_I2C Oled(U8X8_PIN_NONE);
// Initialize 128x64 OLED Display
//U8X8_SSD1306_128X64_NONAME_F_HW_I2C Oled(U8G2_R0, U8X8_PIN_NONE);

//#define echoPin 2 // attach pin D9 Arduino to pin Echo of HC-SR04
//#define trigPin 3 //attach pin D10 Arduino to pin Trig of HC-SR04

#include <NewPing.h>

#define ECHO_PIN 2
#define TRIGGER_PIN 3
#define MAX_DISTANCE 200

// NewPing setup of pins and maximum distance
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

// defines variables
long duration; // variable for the duration of sound wave travel
unsigned int distance; // variable for the distance measurement

void setup() {
  //  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  //  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  Oled.begin();
  // Set OLED Display mode
  Oled.setFlipMode(true); // If true rotates the display to 180 degrees
  // OLED Font type
  Oled.setFont(u8x8_font_chroma48medium8_r);
  // Set cursor to first line
  Oled.setCursor(0, 0);
  // Set header
  Oled.println("Ultrasonic Test"); // print some text in Serial Monitor
}
void loop() {

  readUltrasonic();
  delay(50);
}

void readUltrasonic() {
  //  // Clears the trigPin condition
  //  digitalWrite(trigPin, LOW);
  //  delayMicroseconds(2);
  //  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  //  digitalWrite(trigPin, HIGH);
  //  delayMicroseconds(10);
  //  digitalWrite(trigPin, LOW);
  //  // Reads the echoPin, returns the sound wave travel time in microseconds
  //  duration = pulseIn(echoPin, HIGH);
  //  // Calculating the distance
  //  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  //  displayDistance();
  distance = sonar.ping_cm();
  displayDistance();
}

void displayDistance() {
  // Displays the distance on the Serial Monitor
  // OLED clear line 1
  //  Oled.clearLine(1);
  // Set cursor to line 1
  Oled.setCursor(0, 1);
  // Print distance label
  Oled.print("Dist: ");
  // Print distance value
  Oled.print(distance);
  Serial.println(distance);
  // Print distance unit in centimeter
  Oled.println(" cm   ");
}
