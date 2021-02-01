#include <Servo.h>

Servo servo;

#define potPin A0
#define serPin 6
#define buzzer 5

int potVal;

void setup() {
  // put your setup code here, to run once:
  servo.attach(serPin);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  potVal = analogRead(potPin);
  potVal = map(potVal, 0, 1023, 0, 180);
  servo.write(potVal);
  delay(10);

  if (potVal <= 180 && potVal >=178) {
    tone(buzzer, 1000);
  }
  else {
    noTone(buzzer);
  }
}
