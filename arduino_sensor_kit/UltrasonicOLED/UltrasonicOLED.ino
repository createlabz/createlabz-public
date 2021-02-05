#include "Arduino_SensorKit.h"

// Set echo pin
#define echoPin 2
// Set trigger pin
#define triggerPin 3
// Set max distance
#define MAX_DISTANCE 200

// defines variables
long duration; // variable for the duration of sound wave travel
unsigned int distance; // variable for the distance measurement

void setup() {
  pinMode(triggerPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  Oled.begin();
  // Set OLED Display mode
  Oled.setFlipMode(true); // If true rotates the display to 180 degrees
  // OLED Font type
  Oled.setFont(u8x8_font_chroma48medium8_r);
  
  // Display header to OLED
  displayHeader();
}

void loop() {
  // Read ultrasonic to get distance and set it.
  unsigned int newDistance = readUltrasonic();
  // Check if new distance is within range (For calibration also)
  if (newDistance < MAX_DISTANCE) {
    // Set distance
    distance = newDistance;
    // Display distance value to OLED
    displayDistance();
  }

  delay(50);
}


unsigned int readUltrasonic() {
  // Clears the trigPin condition
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(echoPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  return duration * 0.034 / 2;  // Speed of sound wave divided by 2 (go and back)
}

void displayHeader() {
  // Set cursor to first line
  Oled.setCursor(0, 0);
  // Set header
  Oled.println("Ultrasonic Test");
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
  // Print distance unit in centimeter
  Oled.println(" cm   ");
}
