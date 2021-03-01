#define trigPin 9
#define echoPin 10
#define onLED 4
#define detectLED 3
#define detectBuzz 7
/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#include <SoftwareSerial.h>
SoftwareSerial SwSerial(11, 12); // RX, TX

#include <BlynkSimpleSerialBLE.h>

char auth[] = "HHFvRZPPdcMNGKONWw0waQrce8vQu7m8";

long duration;
int distance;
int acquiredValue;
int notifyVar = 0;

BlynkTimer timer1;
BlynkTimer timer2;

void myNormalTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, "System is ON");
}

void myDetectedTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, "Obstruction Detected");
}

BLYNK_CONNECTED() {
  Blynk.syncAll();
}

void setup() {
  // put your setup code here, to run once:
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(onLED, OUTPUT);
  pinMode(detectLED, OUTPUT);
  pinMode(detectBuzz, OUTPUT);
  
  digitalWrite(onLED, HIGH);
  
  SwSerial.begin(9600);
  Serial.begin(9600);
  Blynk.begin(SwSerial, auth);
  Serial.println("Waiting for connections...");

  timer1.setInterval(1000L, myNormalTimerEvent);
}

void loop() {
  Blynk.run();
  
  ultrasonicFunction();

  if (distance < 50) {
    digitalWrite(onLED, LOW);
    digitalWrite(detectLED, HIGH);

    tone(detectBuzz, 1000);

    if (notifyVar == 0) {
      notifyVar++;
      
      Blynk.notify("!!Obstruction Detected!!");
      timer2.setInterval(1000L, myDetectedTimerEvent);
      timer2.run();
    }
  }

  if (acquiredValue == 1) {
    digitalWrite(onLED, HIGH);
    digitalWrite(detectLED, LOW);

    noTone(detectBuzz);

    notifyVar--;

    acquiredValue = 0;
    Blynk.notify("System Reset");
    timer1.setInterval(1000L, myNormalTimerEvent);
    timer1.run();
  }
}

void ultrasonicFunction() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance= duration*0.034/2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
}

BLYNK_WRITE(V1)
{
  acquiredValue = param.asInt(); // assigning incoming value from pin V1 to a variable
}
