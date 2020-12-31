#include <Stepper.h>
#include <Servo.h>
 
#define STEPS 32

#define IN1  11
#define IN2  10
#define IN3   9
#define IN4   8
 
Stepper stepper(STEPS, IN4, IN2, IN3, IN1);
Servo servo;
 
#define vx  A3
#define vy  A4
#define sw  A5

#define horn 12

#define servoPin 6

int asw;
int avx;
int avy;
 
void setup()
{
  pinMode (sw, INPUT_PULLUP);
  pinMode (vy, INPUT);
  pinMode (vx, INPUT);

  pinMode (horn, OUTPUT);

  servo.attach(servoPin);
}
 
void loop()
{
  // read analog value from the potentiometer
  asw = analogRead(sw);
  avx = analogRead(vx);
  avy = analogRead(vy);

  int servo_val = map(avx, 0, 1023, 0, 180);
  servo.write(servo_val);
  delay(10);

  //when joystick is at the middle
  if (avx > 500 && avx < 510 && avy > 490 && avy < 500) {
    motorOff();
  }
  if (avy >= 500) {
    moveUp();
  }
  if (avy <= 490) {
    moveDown();
  }
  
  if (asw >= 0 && asw <= 20) {
    tone(horn,1000);
  }
  else {
    noTone(horn);
  }
}

void motorOff() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void moveUp() {
  int stepSpeed = map(avy, 523, 1023, 5, 500);
  stepper.setSpeed(stepSpeed);
  stepper.step(5);
  
  int servo_val = map(avx, 0, 1023, 0, 180);
  servo.write(servo_val);
  delay(10);
  
  avy = analogRead(vy);
  avx = analogRead(vx);
}

void moveDown() {
  int stepSpeed = map(avy, 500, 0, 5, 500);
  stepper.setSpeed(stepSpeed);
  stepper.step(-5);
  
  int servo_val = map(avx, 0, 1023, 0, 180);
  servo.write(servo_val);
  delay(10);

  avy = analogRead(vy);
  avx = analogRead(vx);
}
