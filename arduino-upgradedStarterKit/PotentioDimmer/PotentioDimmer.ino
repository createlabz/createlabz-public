/* 
 *  Created: October 2020
 *  Nolf Ivan C. Labios
 *  Adjusting LED brightness using potentiometer
 *  Part 1 of Controlling an LED series
 */
 
const int POT = A0; //analog input pin for potentiometer
const int LED = 9; //input pin for LED

int POTvalue=0; //variable for input values from A0
int outPOTvalue=0; //variable for output value from potentio

void setup() {
  //Initialize pinModes
  pinMode (LED,OUTPUT);
  pinMode (POT,INPUT);

}

void loop() {
  POTvalue = analogRead(POT); //reads value from analog pin
  outPOTvalue = map(POTvalue,0,1023,0,255); //re-map from 0-1023 to 0-250
  
  analogWrite(LED,outPOTvalue);
  delay(1000);
}
