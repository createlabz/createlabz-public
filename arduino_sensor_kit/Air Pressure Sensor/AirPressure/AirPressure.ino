#include "Arduino_SensorKit.h"

float presVal;
float tempVal;
float altiVal;

void setup() {
  // put your setup code here, to run once:
  Pressure.begin();
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  presVal = Pressure.readPressure();
  tempVal = Pressure.readTemperature();
  altiVal = Pressure.readAltitude();

  Serial.print("Temperature: ");
  Serial.print(tempVal);
  Serial.print(" C");

  Serial.print("\t");

  Serial.print("Pressure: ");
  Serial.print(presVal);
  Serial.print(" Pa");

  Serial.print("\t");

  Serial.print("Altitude: ");
  Serial.print(altiVal);
  Serial.println(" m");

  delay(1000);
}
