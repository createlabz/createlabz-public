#include "Arduino_SensorKit.h"

int temp;
int humi;

void setup() {
  // put your setup code here, to run once:
  Environment.begin();
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  temp = Environment.readTemperature();
  humi = Environment.readHumidity();

  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.print(" C");

  Serial.print("\t");

  Serial.print("Humi: ");
  Serial.print(humi);
  Serial.println(" %");

  delay(1000);
}
