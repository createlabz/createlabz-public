#include "Arduino_SensorKit.h"
#include <virtuabotixRTC.h>

virtuabotixRTC nRTC(6, 7, 8);

void setup() {
  // put your setup code here, to run once:
  Oled.begin();
  Oled.setFlipMode(true);
}

void loop() {
  // put your main code here, to run repeatedly:
  nRTC.updateTime();

  Oled.setFont(u8x8_font_chroma48medium8_r);
  Oled.setCursor(0, 35);
  Oled.print(nRTC.dayofmonth);
  Oled.print("/");
  Oled.print(nRTC.month);
  Oled.print("/");
  Oled.print(nRTC.year);

  Oled.setFont(u8x8_font_courB18_2x3_n);
  Oled.setCursor(0, 20);
  Oled.print(nRTC.hours);
  Oled.print(":");
  Oled.print(nRTC.minutes);
  Oled.print(":");
  Oled.print(nRTC.seconds);

  delay(500);
}
