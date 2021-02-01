#include "Arduino_SensorKit.h"

void setup() {
  // put your setup code here, to run once:
  Oled.begin();
  Oled.setFlipMode(true);
  Oled.setFont(u8x8_font_courB18_2x3_f);
}

void loop() {
  // put your main code here, to run repeatedly:
  Oled.setCursor(0, 0);
  Oled.print("CREATE");
  Oled.setCursor(0, 19);
  Oled.print("LABZ");

  delay(3000);
  Oled.clear();
  delay(10);

  Oled.setCursor(0, 0);
  Oled.print("INTRO TO");
  Oled.setCursor(0, 19);
  Oled.print("OLED");

  delay(3000);
  Oled.clear();
  delay(10);
}
