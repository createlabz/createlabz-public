#include "Arduino_SensorKit.h"
#define ledPin 6
#define buttonPin 4

int long ranDelay = 0;
int sensorValue = 0;
float realTime, timeResponse, fastestTimeResponse;

void setup()
{
  Serial.begin(9600);

  // Initialize OLED diplay
  Oled.begin();
  // Set OLED Display mode
  Oled.setFlipMode(true); // If true rotates the display to 180 degrees
  // OLED Font type
  Oled.setFont(u8x8_font_chroma48medium8_r);

  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {
  //  displayFastestTime();
  start();
  while (digitalRead(buttonPin) == LOW) {}

  ready();
  if(go() == true){
    while (digitalRead(buttonPin) == LOW) {}
    recordTime();
  }
  

  delay(3000);
}

void start() {
  Oled.clearLine(0);
  Oled.clearLine(2);
  Oled.setCursor(0, 0);
  Oled.print("Push button ");
  Oled.setCursor(0, 1);
  Oled.print("to start game ");
}

void ready() {
  Oled.clearLine(0);
  Oled.clearLine(1);
  Oled.setCursor(0, 0);
  Oled.print("Get Ready!");
  delay(1000);
  Oled.clearLine(0);
  Oled.setCursor(0, 0);
  Oled.print("Get Set!");
  delay(1000);
}

bool go() {
  Oled.clearLine(0);
  Oled.setCursor(0, 0);
  ranDelay = random(5000);
  delay(ranDelay);
  bool cheating = checkCheating();
  if(cheating == true) return false;
  delay(50);
  digitalWrite(ledPin, HIGH);
  Oled.print("Go!");
  realTime = millis();
  return true;
}

bool checkCheating() {
  if (digitalRead(buttonPin) == HIGH) {
    Oled.clearLine(0);
    Oled.setCursor(0, 0);
    Oled.print("Cheater!");
    return true;
  }
  return false;
}

void recordTime() {
  digitalWrite(ledPin, LOW);
  Oled.clearLine(0);
  Oled.setCursor(0, 0);
  Oled.print("Time ");
  timeResponse = millis() - realTime;
  Oled.print(timeResponse);
  Oled.print(" ms");
  setFastestTime();
}

void setFastestTime() {
  if (fastestTimeResponse == 0 or timeResponse < fastestTimeResponse) {
    Oled.setCursor(0, 2);
    Oled.print("New Fast Time!");
    fastestTimeResponse = timeResponse;
    displayFastestTime();
  }
}

void displayFastestTime() {
  Oled.clearLine(6);
  Oled.setCursor(0, 6);
  Oled.print("Fast:");
  Oled.print(fastestTimeResponse);
  Oled.print(" ms");
}
