// Set buzzer pin
#define buzzerPin 5
// Set echo pin
#define echoPin 2
// Set trigger pin
#define triggerPin 3
// Set max distance
#define MAX_DISTANCE 200

// Buzzer tone (NOTE_AS4)
#define buzzerTone 466 // NOTE_AS4 TONE
// Note durations type
#define FAST_NOTE 16
#define MEDIUM_NOTE 8
#define SLOW_NOTE 4


long duration; // variable for the duration of sound wave travel
unsigned int distance; // variable for the distance measurement

void setup() {
  // put your setup code here, to run once:
  pinMode(triggerPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  
  pinMode(buzzerPin, OUTPUT); // Set buzzer pin as output
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned int newDistance = readUltrasonic();
  // Check if new distance is within range (For accuracy purposes also)
  if (newDistance < MAX_DISTANCE) {
    // Set distance
    distance = newDistance;
    // Check distance value
    checkDistance();
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

void checkDistance() {
  // Within far distance range
  if (distance >= 40 and distance <= 50) beepSignal(SLOW_NOTE);
  // Within medium distance range
  else if (distance >= 20 and distance < 40) beepSignal(MEDIUM_NOTE);
  // Within close distance range
  else if (distance >= 0 and distance < 20)  beepSignal(FAST_NOTE);
}

void beepSignal(int notePace) {
  // to calculate the note duration, take one second
  // divided by the note type.
  //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
  int noteDuration = 1000 / notePace;

  // Play tone within note duration
  tone(buzzerPin, buzzerTone, noteDuration);

  // to distinguish the notes, set a minimum time between them.
  // the note's duration + 30% seems to work well:
  int pauseBetweenNotes = noteDuration * 1.30;
  delay(pauseBetweenNotes);

  // Stop the buzzer playing
  noTone(buzzerPin);
}
