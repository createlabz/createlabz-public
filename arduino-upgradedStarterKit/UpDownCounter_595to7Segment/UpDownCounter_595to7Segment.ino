/*  UpDownCounter_595to7Segment.ino
 *  2020-10-17
 *  Kristine Angelica B. Valderosa
 *  Up/Down Counter using Shift Register and 7-Segment Display
*/

const int dataPin = 2;  
const int latchPin = 4; 
const int clockPin = 7; 

const int upButton = 8;
const int downButton = 12;

int upButtonState = 0;
int downButtonState = 0;

int controlVar = 0; //0-upCount; 1-downCount

int countVar = 0;
 
void setup() {
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);

  pinMode(upButton, INPUT);
  pinMode(downButton, INPUT);
  
  byte bits = myfnNumToBits(countVar) ;
  myfnUpdateDisplay(bits);
  delay(1000);
}

void loop() {
  if (controlVar == 0){
    upCount();
  }
  if (controlVar == 1){
    downCount();
  }
}

void upCount(){
  countVar++;
  if (countVar > 9) {
    countVar = 0;
  }
  byte bits = myfnNumToBits(countVar) ;
  myfnUpdateDisplay(bits);
  delay(1000);
  buttonRead();
}

void downCount(){
  countVar--;
  if (countVar < 0) {
    countVar = 9;
  }
  byte bits = myfnNumToBits(countVar) ;
  myfnUpdateDisplay(bits);
  delay(1000);
  buttonRead();
}

void buttonRead() {
  upButtonState = digitalRead(upButton);
  downButtonState = digitalRead(downButton);
  if (upButtonState == HIGH) {
    controlVar = 0;
  }
  if (downButtonState == HIGH) {
    controlVar = 1;
  }
}

void myfnUpdateDisplay(byte eightBits) {
  digitalWrite(latchPin, LOW); 
  shiftOut(dataPin, clockPin, LSBFIRST, eightBits); 
  digitalWrite(latchPin, HIGH);
}

byte myfnNumToBits(int someNumber) {
  switch (someNumber) {
    case 0:
      return B11111100;
      break;
    case 1:
      return B01100000;
      break;
    case 2:
      return B11011010;
      break;
    case 3:
      return B11110010;
      break;
    case 4:
      return B01100110;
      break;
    case 5:
      return B10110110;
      break;
    case 6:
      return B10111110;
      break;
    case 7:
      return B11100000;
      break;
    case 8:
      return B11111110;
      break;
    case 9:
      return B11110110;
      break;
    default:
      return B10010010; // Error condition, displays three vertical bars
      break;   
  }
}
