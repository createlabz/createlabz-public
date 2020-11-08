/*
 * Created: October 2020
 * by Nolf Ivan C. Labios
 * Potentiometer controlled LEDs with buzzer
*/

/* 
 *  Created: October 2020
 *  Nolf Ivan C. Labios
 *  Potentiometer controlled LEDs with buzzer
 *  Part 3 of Controlling an LED series
 */

//blu =13;
//gr1 =12;
//gr2 =11;
//rd1 = 10;
//rd2 = 9;

int ledArray[] = {13, 12, 11, 10, 9};

int buz = 8;

int potentio = A0;
int PotenInput=0;


void setup() {
  // put your setup code here, to run once:

  //Use a for loop to set all LEDs as OUTPUT
  for(int i = 0; i < 6; i++)
{
  pinMode(ledArray[i], OUTPUT);
}

  pinMode(buz, OUTPUT);
  pinMode(potentio,INPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  PotenInput = analogRead(potentio);    
  int num = map(PotenInput,0,1022,0,4);

  switch(num)                           
  {
    case 0: //very low (0%-20%)
    digitalWrite(ledArray[0], HIGH);
    digitalWrite(ledArray[1], LOW);
    digitalWrite(ledArray[2], LOW);
    digitalWrite(ledArray[3], LOW);
    digitalWrite(ledArray[4], LOW);
    noTone(buz);
    break;
    case 1: //low (20%-40%)
    digitalWrite(ledArray[0], LOW);
    digitalWrite(ledArray[1], HIGH);
    digitalWrite(ledArray[2], LOW);
    digitalWrite(ledArray[3], LOW);
    digitalWrite(ledArray[4], LOW);
    noTone(buz);
    break;
    case 2: //medium (40%-60%)
    digitalWrite(ledArray[0], LOW);
    digitalWrite(ledArray[1], LOW);
    digitalWrite(ledArray[2], HIGH);
    digitalWrite(ledArray[3], LOW);
    digitalWrite(ledArray[4], LOW);
    noTone(buz);
    break;
    case 3: //high (60%-80%)
    digitalWrite(ledArray[0], LOW);
    digitalWrite(ledArray[1], LOW);
    digitalWrite(ledArray[2], LOW);
    digitalWrite(ledArray[3], HIGH);
    digitalWrite(ledArray[4], LOW);
    tone(buz,500);                
   break;
    case 4: //very high (80%-100%)
    digitalWrite(ledArray[0], LOW);
    digitalWrite(ledArray[1], LOW);
    digitalWrite(ledArray[2], LOW);
    digitalWrite(ledArray[3], LOW);
    digitalWrite(ledArray[4], HIGH);
    tone(buz,1000);
    break;
  }
    delay(300);
}
