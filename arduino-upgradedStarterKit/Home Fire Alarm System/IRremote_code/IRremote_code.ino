/*
 * Created: December 2020
 * by Nolf Ivan C. Labios
 * IRremote test for Home Fire Alarm System
*/

#include <IRremote.h>

const int IR_pin = 7;
IRrecv irrecv(IR_pin); //Identify which pin the IR receiver is connected
decode_results results;

void setup(){
  Serial.begin(9600); 
  irrecv.enableIRIn(); 
  irrecv.blink13(true); //Arduino's LED will blink whenever IR receiver receives a signal
}

void loop(){
  if (irrecv.decode(&results)){ // will return true when IR code is received
        Serial.println(results.value, HEX); //received code is sored in the results.value
        irrecv.resume(); //resets the receiver and prepares to receive next code
        
  }
}
