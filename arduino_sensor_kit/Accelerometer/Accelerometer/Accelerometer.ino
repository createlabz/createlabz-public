#include "Arduino_SensorKit.h"

float xVal;
float yVal;
float zVal;

void setup() {
  // put your setup code here, to run once:
  Accelerometer.begin();
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  xVal = Accelerometer.readX();
  yVal = Accelerometer.readY();
  zVal = Accelerometer.readZ();

  Serial.print("x:");
  Serial.print(xVal);
  Serial.print("\t");
  Serial.print("y:");
  Serial.print(yVal);
  Serial.print("\t");
  Serial.print("z:");
  Serial.println(zVal);

  delay(500);
}
