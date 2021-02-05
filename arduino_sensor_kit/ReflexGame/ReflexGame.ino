#include "Arduino_SensorKit.h"
#define ledPin 6
#define buttonPin 4
#define buzzerPin 5

int long ranDelay = 0;
int sensorValue = 0;
float realTime, timeResponse, fastestTimeResponse;
#define buzzerTone 466 // NOTE_AS4 TONE

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
  pinMode(buzzerPin, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {
  //  displayFastestTime();
  // Start action
  start();
  // Wait button to be pressed to start
  waitButton();

  // Ready action
  ready();
  // Go action return true to proceed, false if not.
  if(go() == true){
    // Wait button to be pressed to record player response time.
    waitButton();
    // Record player response time
    recordTime();
  }
  // Wait within 3 seconds to proceed to next game
  delay(3000);
}

void waitButton(){
  // Wait and stops when button is pressed
  while (digitalRead(buttonPin) == LOW) {};
}

void start() {
  // Clear line 0
  Oled.clearLine(0);
  // Clear line 2
  Oled.clearLine(2);
  // Set cursor to first character and first line
  Oled.setCursor(0, 0);
  // Print instruction to start game
  Oled.print("Push button ");
  Oled.setCursor(0, 1);
  Oled.print("to start game ");
}

void ready() {
  // Clear line 0
  Oled.clearLine(0);
  // Clear line 1
  Oled.clearLine(1);
  // Set cursor to first line
  Oled.setCursor(0, 0);
  // Print Ready Signal
  Oled.print("Get Ready!");
  // Wait for 1 second
  delay(1000);
  // Clear line 1
  Oled.clearLine(0);
  // Set cursor to first line
  Oled.setCursor(0, 0);
  // Print get set signal
  Oled.print("Get Set!");
  // Wait for 1 second
  delay(1000);
}

bool go() {
  // Clear line 1
  Oled.clearLine(0);
  // Set cursor to line 1
  Oled.setCursor(0, 0);
  // Set random delay for player to wait
  ranDelay = random(5000);
  // Wait that depends on random
  delay(ranDelay);
  // Check if player is cheating when he pressed it to early.
  bool cheating = checkCheating();
  // If cheating return false to not proceed.
  if(cheating == true) return false;
  // Wait 50ms to proceed
  delay(50);
  // Signal LED by turning it on
  digitalWrite(ledPin, HIGH);
  // Signal buzzer by making a tone
  tone(buzzerPin, buzzerTone);
  // Print go signal
  Oled.print("Go!");
  // Get current time in milliseconds
  realTime = millis();
  // Return true to proceed
  return true;
}

bool checkCheating() {
  // Check if button is already set before go signal
  if (digitalRead(buttonPin) == HIGH) {
    // Clear line 1
    Oled.clearLine(0);
    // Set cursor to line 1
    Oled.setCursor(0, 0);
    // Signal disqualifaction
    Oled.print("Cheater!");
    // Return true to stop the player to continue.
    return true;
  }
  // Return false to make the player to continue
  return false;
}

void recordTime() {
  // Turn off the LED signal
  digitalWrite(ledPin, LOW);
  // Turn off the Buzzer signal.
  noTone(buzzerPin);
  // Clear line 1
  Oled.clearLine(0);
  // Set cursor to line 1
  Oled.setCursor(0, 0);
  // Set print time label
  Oled.print("Time ");
  // Get the total time response
  timeResponse = millis() - realTime;
  // Display time response
  Oled.print(timeResponse);
  // Display unit
  Oled.print(" ms");
  // Set the fastest time
  setFastestTime();
}

void setFastestTime() {
  // Check if the time response is much faster to the previous recorded time.
  if (fastestTimeResponse == 0 or timeResponse < fastestTimeResponse) {
    // Set cursor to line 3
    Oled.setCursor(0, 2);
    // Print new recorded fastest time
    Oled.print("New Fast Time!");
    // Set new fastest time
    fastestTimeResponse = timeResponse;
    // Display the fastest time
    displayFastestTime();
  }
}

void displayFastestTime() {
  // Clear line 7
  Oled.clearLine(6);
  // Set to line 7
  Oled.setCursor(0, 6);
  // Print fastest time label
  Oled.print("Fast:");
  // Print fastest time response
  Oled.print(fastestTimeResponse);
  // Print unit
  Oled.print(" ms");
}
