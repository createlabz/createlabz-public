#include "Arduino_SensorKit.h"

#define buzzer 5

float presVal;
float tempVal;
float altiVal;

void setup() {
  // put your setup code here, to run once:
  Pressure.begin();
  Serial.begin(9600);

  pinMode(buzzer, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  presVal = Pressure.readPressure();
  tempVal = Pressure.readTemperature();
  altiVal = Pressure.readAltitude();

  Serial.print("Temperature: ");
  Serial.print(tempVal);
  Serial.print(" C");

  Serial.print(" \t");

  Serial.print("Pressure: ");
  Serial.print(presVal);
  Serial.print(" Pa");

  Serial.print(" \t  ");

  Serial.print("Altitude: ");
  Serial.print(altiVal);
  Serial.println(" m");

  if (tempVal >= 30) {
    tone(buzzer, 1000);
  }
  else {
    noTone(buzzer);
  }

  delay(1000);
}
