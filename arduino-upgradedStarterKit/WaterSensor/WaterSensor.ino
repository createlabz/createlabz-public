/* 
 *  Created: November 2020
 *  Nolf Ivan C. Labios
 *  water Level Sensor with LED Indicator and Relay
 *  Part 5 of Controlling an LED series
 */
 
int led_red=13;
int led_grn=12;
int led_blu=11;
int relay =8;

int waterSensor=A0;
int waterOut=0;

void setup() {
  
  pinMode(led_blu,OUTPUT);
  pinMode(led_grn,OUTPUT);
  pinMode(led_red,OUTPUT);
  pinMode(relay,OUTPUT);

  pinMode (waterSensor,INPUT);
  Serial.begin(9600);
}

void loop() {
  
  waterOut=analogRead(waterSensor);

  int waterMap = map(waterOut, 0, 1023, 0, 255);
  int level = constrain(waterMap, 0,170);
  
  Serial.println(level);

  if(level>20&&level<130)
   { 
    digitalWrite(led_blu, HIGH);
    digitalWrite(led_grn, LOW);
    digitalWrite(led_red, LOW);
    digitalWrite(relay,LOW);
   }
  
  else if(level>130&&level<145)
   {
    digitalWrite(led_blu, LOW);
    digitalWrite(led_grn, HIGH);
    digitalWrite(led_red, LOW);
    digitalWrite(relay,LOW);
   }
  
  else if(level>145&&level<165)
   {
    digitalWrite(led_blu, LOW);
    digitalWrite(led_grn, LOW);
    digitalWrite(led_red, HIGH);
    digitalWrite(relay,HIGH); 
   }


}
