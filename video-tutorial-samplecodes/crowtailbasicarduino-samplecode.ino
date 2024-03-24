/*
  Demo code of Crowtail - 4 Digital 7-Segment LED 
  by Tony
*/
#include "TM1650.h"
#include <inttypes.h>
static uint8_t TubeTab[] = {
               0x3F,0x06,0x5B,0x4F,
               0x66,0x6D,0x7D,0x07,
               0x7F,0x6F,0x77,0x7C,
               0x39,0x5E,0x79,0x71,   
               };//0~9,A,B,C,D,E,F  
static uint8_t TubeTabwithPoit[] = {
               0xBF,0x86,0xDB,0xCF,
               0xE6,0xED,0xFD,0x87,
               0xFF,0xEF   
               };//0~9  
TM1650 DigitalLED(A5,A4); //i2c
int8_t number[] = {0,0,0,0};

int moist = 0;
byte ledG = 5;
byte ledR = 4;
byte buzz = 3;
byte rel = 2;
byte dig1 = 0;
byte dig2 = 0;
byte dig3 = 0;
byte dig4 = 0;
int moist_pin = A0;




void setup()
{
  Serial.begin(9600);
  pinMode(ledG, OUTPUT);
  pinMode(ledR, OUTPUT);
  pinMode(buzz, OUTPUT);
  pinMode(rel, OUTPUT);
}
void loop()
{

//read the value of the sensor

moist = analogRead(moist_pin); //0-1023

dig1 = moist/1000;
dig2 = (moist%1000)/100;
dig3 = (moist%100)/10;
dig4 = moist%10;
//super moist value is 700+
//dry value < 600 
// normal level 600-700


//display starts---
    DigitalLED.clearDisplay();
 
     DigitalLED.display(0,TubeTab[dig1]);
     DigitalLED.display(1,TubeTab[dig2]);
     DigitalLED.display(2,TubeTab[dig3]);
     DigitalLED.display(3,TubeTab[dig4]);


if (moist >= 600){
  digitalWrite(ledG, HIGH);
  digitalWrite(ledR, LOW);
}else{
  digitalWrite(ledR, HIGH);
  digitalWrite(ledG, LOW);
  digitalWrite(rel, HIGH);
  digitalWrite(buzz, HIGH);
}

if (moist > 700){
    digitalWrite(rel,LOW);
}





    delay(500);
    digitalWrite(buzz, LOW);
    delay(500);
     DigitalLED.clearDisplay();




//display ends


}
