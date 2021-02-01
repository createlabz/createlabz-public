#include "Arduino_SensorKit.h"

#define buzzer 5

int temp;
int humi;

void setup() {
  // put your setup code here, to run once:
  Environment.begin();

  Oled.begin();
  Oled.setFlipMode(true);
  Oled.setFont(u8x8_font_courB18_2x3_f);

  pinMode(buzzer, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  temp = Environment.readTemperature();
  humi = Environment.readHumidity();
  
  Oled.setCursor(0, 0);
  Oled.print("Temp:");
  Oled.print(temp);
  Oled.print("C");

  Oled.setCursor(0, 20);
  Oled.print("Humi:");
  Oled.print(humi);
  Oled.print("%");
  Oled.refreshDisplay();

  if (temp > 31 || humi < 30 || humi > 71 || temp < 16) {
    tone(buzzer, 1000);
  }
  else {
    noTone(buzzer);
  }

  delay(1000);
}
