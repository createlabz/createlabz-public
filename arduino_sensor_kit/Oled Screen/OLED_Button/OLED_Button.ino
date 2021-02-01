#include "Arduino_SensorKit.h"

#define button 4

int buttonState = 0;
int screenNumber = 0;

void setup() {
  // put your setup code here, to run once:
  Oled.begin();
  Oled.setFlipMode(true);
  Oled.setFont(u8x8_font_courB18_2x3_f);

  pinMode(button, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  buttonState = digitalRead(button);

  if (screenNumber == 0) {
    Oled.setCursor(0, 0);
    Oled.print("1st");
    Oled.setCursor(0, 19);
    Oled.print("Screen");

    if (buttonState == HIGH) {
      screenNumber = screenNumber + 1;
      Oled.clear();
    }
  }
  else {
    Oled.setCursor(0, 0);
    Oled.print("2nd");
    Oled.setCursor(0, 19);
    Oled.print("Screen");

    if (buttonState == HIGH) {
      screenNumber = screenNumber - 1;
      Oled.clear();
    }
  }
}
