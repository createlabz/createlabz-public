#include <Servo.h>

Servo servo;

#define serPin 6
#define lightPin A3

int lightVal;

void setup() {
  // put your setup code here, to run once:
  servo.attach(serPin);
}

void loop() {
  // put your main code here, to run repeatedly:
  lightVal = analogRead(lightPin);
  lightVal = map(lightVal, 0, 1023, 0, 180);
  servo.write(lightVal);
  delay(10);
}
