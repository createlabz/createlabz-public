#define BLYNK_PRINT Serial

#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>

#define trigPin 9
#define echoPin 10
#define onLED 4
#define detectLED 3
#define detectBuzz 7

long duration;
int distance;

int acquiredValue;
int notifyVar = 0;

/* Comment this out to disable prints and save space */
#include <SoftwareSerial.h>
SoftwareSerial EspSerial(12, 11); // RX, TX

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "5c6pFHdq71CuypOW2cRKpN22CmlJ5iYE";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Bruh";
char pass[] = "dragonclawz";

// Your ESP8266 baud rate:
#define ESP8266_BAUD 9600

ESP8266 wifi(&EspSerial);

void setup() {
  // put your setup code here, to run once:

  // Debug console
  Serial.begin(9600);
  delay(10);
  
  EspSerial.begin(ESP8266_BAUD);
  delay(10);

  Blynk.begin(auth, wifi, ssid, pass);
  Blynk.virtualWrite(V5, "System is ON");

  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(onLED, OUTPUT);
  pinMode(detectLED, OUTPUT);
  pinMode(detectBuzz, OUTPUT);
  
  digitalWrite(onLED, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Blynk.connected()) {
    Blynk.run();
    ultrasonicFunction();

    if (distance < 50) {
      digitalWrite(onLED, LOW);
      digitalWrite(detectLED, HIGH);
  
      tone(detectBuzz, 1000);
  
      if (notifyVar == 0) {
        notifyVar++;
  
        Blynk.notify("!!Obstruction Detected!!");
        Blynk.virtualWrite(V5, "Obstruction Detected");
      }
    }
    if (acquiredValue == 1) {
      digitalWrite(onLED, HIGH);
      digitalWrite(detectLED, LOW);
  
      noTone(detectBuzz);
  
      notifyVar--;
  
      acquiredValue = 0;
      Blynk.notify("System Reset");
      Blynk.virtualWrite(V5, "System is ON");
    }
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
