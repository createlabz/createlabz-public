#include <Keypad.h>
#include <Servo.h>
#include <SevSegShift.h>

#define SHIFT_PIN_SHCP 6
#define SHIFT_PIN_STCP 5
#define SHIFT_PIN_DS   4

SevSegShift sevseg(SHIFT_PIN_DS, SHIFT_PIN_SHCP, SHIFT_PIN_STCP, 1, true);
Servo myservo;

const byte rows=4;
const byte cols=4;
char key[rows][cols]={
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};

byte rowPins[rows]={2,A1,A5,A4};
byte colPins[cols]={A3,7,8,13};

Keypad customKeypad= Keypad(makeKeymap(key),rowPins,colPins,rows,cols);

int buzz = A2;

char setPassword[5] = "01BA";
char keyNum[5];
String addKey;

int openSeconds = 10000; //door stays unlocked for 10 seconds

void setup() {
  byte numDigits = 4;
  byte digitPins[] = {12, 11, 10, 9}; // These are the PINS of the ** Arduino **
  byte segmentPins[] = {0, 1, 2, 3, 4, 5, 6, 7}; // these are the PINs of the ** Shift register **
  bool resistorsOnSegments = false; // 'false' means resistors are on digit pins
  byte hardwareConfig = COMMON_ANODE; // See README.md for options
  bool updateWithDelays = false; // Default 'false' is Recommended
  bool leadingZeros = true; // Use 'true' if you'd like to keep the leading zeros
  bool disableDecPoint = false; // Use 'true' if your decimal point doesn't exist or isn't connected
  
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments, updateWithDelays, leadingZeros, disableDecPoint);
  sevseg.setBrightness(100);
  
  myservo.attach(3);
  clearSevDisplay();
  
  pinMode(buzz, OUTPUT);
}

void loop() {
  displayNumber();  
  sevseg.refreshDisplay();
}


void displayNumber() { 
  char customKey = customKeypad.getKey();
  if ( strlen(keyNum) <= 4) {
    if(customKey){
      if(customKey=='*'){ 
        keyPress();
        clearSevDisplay();
      }
      if(customKey=='#') {
        keyPress();
        checkPassword();
      }
      if (customKey=='A'){
        keyPress();
        addKey = "A";
        strcat( keyNum, addKey.c_str() );
        sevseg.setChars(keyNum);
        sevseg.refreshDisplay();
      }
      if (customKey=='B'){
        keyPress();
        addKey = "B";
        strcat( keyNum, addKey.c_str() );
        sevseg.setChars(keyNum);
        sevseg.refreshDisplay();
      }
      if (customKey=='C'){
        keyPress();
        addKey = "C";
        strcat( keyNum, addKey.c_str() );
        sevseg.setChars(keyNum);
        sevseg.refreshDisplay();
        Serial.println(keyNum);
      }
      if (customKey=='D'){
        keyPress();
        addKey = "D";
        strcat( keyNum, addKey.c_str() );
        sevseg.setChars(keyNum);
        sevseg.refreshDisplay();
      }
      if (customKey=='1'){
        keyPress();
        addKey = "1";
        strcat( keyNum, addKey.c_str() );
        sevseg.setChars(keyNum);
        sevseg.refreshDisplay();
      }
      if (customKey=='2'){
        keyPress();
        addKey = "2";
        strcat( keyNum, addKey.c_str() );
        sevseg.setChars(keyNum);
        sevseg.refreshDisplay();
      }
      if (customKey=='3'){
        keyPress();
        addKey = "3";
        strcat( keyNum, addKey.c_str() );
        sevseg.setChars(keyNum);
        sevseg.refreshDisplay();
      }
      if (customKey=='4'){
        keyPress();
        addKey = "4";
        strcat( keyNum, addKey.c_str() );
        sevseg.setChars(keyNum);
        sevseg.refreshDisplay();
      }
      if (customKey=='5'){
        keyPress();
        addKey = "5";
        strcat( keyNum, addKey.c_str() );
        sevseg.setChars(keyNum);
        sevseg.refreshDisplay();
      }
      if (customKey=='6'){
        keyPress();
        addKey = "6";
        strcat( keyNum, addKey.c_str() );
        sevseg.setChars(keyNum);
        sevseg.refreshDisplay();
      }
      if (customKey=='7'){
        keyPress();
        addKey = "7";
        strcat( keyNum, addKey.c_str() );
        sevseg.setChars(keyNum);
        sevseg.refreshDisplay();
      }
      if (customKey=='8'){
        keyPress();
        addKey = "8";
        strcat( keyNum, addKey.c_str() );
        sevseg.setChars(keyNum);
        sevseg.refreshDisplay();
      }
      if (customKey=='9'){
        keyPress();
        addKey = "9";
        strcat( keyNum, addKey.c_str() );
        sevseg.setChars(keyNum);
        sevseg.refreshDisplay();
      }
      if (customKey=='0'){
        keyPress();
        addKey = "0";
        strcat( keyNum, addKey.c_str() );
        sevseg.setChars(keyNum);
        sevseg.refreshDisplay();
      }
    }
  }
  else {
    checkPassword();
  }
}

void clearSevDisplay() {
  //return to lock position
  myservo.write(0);
  delay(500);
   
  memset(keyNum, 0, sizeof(keyNum));
  sevseg.setChars("----");
  sevseg.refreshDisplay();
}

void keyPress() {
  tone(buzz,500);
  delay(50);
  noTone(buzz);
}

void checkPassword(){
  if ( strcmp(keyNum, setPassword) == 0 ) {
    //you're in!
    validBuzz();

    //move to unlocked position
    for (int pos=0;pos<=180;pos+=5)
    {
      myservo.write(pos);
      delay(5);
    }
    delay(openSeconds);

    clearSevDisplay();
  }
  else {
    //wrong password!
    invalidBuzz();
    clearSevDisplay();
  }
}

void validBuzz() {
  tone(buzz,1000);
  delay(1000);
  noTone(buzz);
}

void invalidBuzz(){
  tone(buzz,1500);
  delay(1500);
  noTone(buzz);
}
