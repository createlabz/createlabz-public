#include "Arduino_SensorKit.h"

#define buzzer 5

float xVal;
float yVal;
float zVal;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Accelerometer.begin();

  pinMode(buzzer, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  xVal = Accelerometer.readX();
  yVal = Accelerometer.readY();
  zVal = Accelerometer.readZ();
    
  Serial.print("x:"); 
  Serial.print(xVal);  // Read the X Value 
  Serial.print("\t");
  Serial.print("y:"); 
  Serial.print(yVal);  // Read the Y Value       
  Serial.print("\t");
  Serial.print("z:"); 
  Serial.println(zVal);// Read the Z Value

  if (yVal <= -0.60 || yVal >= 0.60 || zVal <= 0.70) {
    tone(buzzer,1000);
  }
  else {
    noTone(buzzer);
  }

  delay(500);
}
