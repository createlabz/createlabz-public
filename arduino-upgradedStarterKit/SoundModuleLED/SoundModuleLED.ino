/* 
 *  Created: November 2020
 *  Nolf Ivan C. Labios
 *  Music reactive LEDs using Sound Module
 *  Part 4 of Controlling an LED series
 */

int ledblu1= 13; 
int ledblu2= 12;
int ledgrn3= 11;
int ledgrn4= 10;
int ledred5= 9;
int ledred6= 8;

int soundMod= A0;
int soundOut = 0;

void setup(){
  pinMode(ledblu1, OUTPUT); 
  pinMode(ledblu2, OUTPUT);
  pinMode(ledgrn3, OUTPUT);
  pinMode(ledgrn4, OUTPUT);
  pinMode(ledred5, OUTPUT);
  pinMode(ledred6, OUTPUT);
  
  pinMode(soundMod, INPUT); 
  Serial.begin (9600);
}
  
void loop (){
  soundOut =analogRead(soundMod); 
 
 
  Serial.println (soundOut); //This is done to know the min and max threshold for the sound sensor
  
  // when the sensor detects a signal, LED flashes
  // Once min and max threshold have been obtained, divide the values per LED
  
  //Minimum Threshold
  if (soundOut >= 495) {
    digitalWrite(ledblu1, HIGH); 
  }
  else {
    digitalWrite(ledblu1, LOW);
  }

  if (soundOut >= 500) {
    digitalWrite(ledblu2, HIGH);
  }
  else {
    digitalWrite(ledblu2, LOW);
  }
   
  if (soundOut >= 510) {
    digitalWrite(ledgrn3, HIGH);
  }
  else {
    digitalWrite(ledgrn3, LOW);
  }

  if (soundOut >= 515) {
    digitalWrite(ledgrn4, HIGH);
  }
  else {
    digitalWrite(ledgrn4, LOW);
  }

  if (soundOut >= 520) {
    digitalWrite(ledred5, HIGH);
  }
  else {
    digitalWrite(ledred5, LOW);
  }

  //Max Threshold
  if (soundOut >= 525) {
    digitalWrite(ledred6, HIGH);
  }
  else {
    digitalWrite(ledred6, LOW);
  }
}
