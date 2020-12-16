#define sensorPin A5

#define ROW_1 2
#define ROW_2 3
#define ROW_3 4
#define ROW_4 5
#define ROW_5 6
#define ROW_6 7
#define ROW_7 8
#define ROW_8 9

#define COL_1 10
#define COL_2 11
#define COL_3 12
#define COL_4 13
#define COL_5 A0
#define COL_6 A1
#define COL_7 A2
#define COL_8 A3

const byte rows[] = {
    ROW_1, ROW_2, ROW_3, ROW_4, ROW_5, ROW_6, ROW_7, ROW_8
};
const byte col[] = {
  COL_1,COL_2, COL_3, COL_4, COL_5, COL_6, COL_7, COL_8
};

int sensorValue;
int lastTiltState = HIGH; 
long lastDebounceTime = 0; 
long debounceDelay = 50;

int num1;
int num2;

//dice combinations
byte oneone[] = {
  B01000000,
  B11000010,
  B01000110,
  B01000010,
  B01000010,
  B01000010,
  B11100010,
  B00000111
};
byte onetwo[] = {
  B01000000,
  B11000111,
  B01000001,
  B01000001,
  B01000111,
  B01000100,
  B11100100,
  B00000111
};
byte onethree[] = {
  B01000000,
  B11000111,
  B01000001,
  B01000001,
  B01000111,
  B01000001,
  B11100001,
  B00000111
};
byte onefour[] = {
  B01000000,
  B11000001,
  B01000011,
  B01000101,
  B01000111,
  B01000001,
  B11100001,
  B00000001
};
byte onefive[] = {
  B01000000,
  B11000111,
  B01000100,
  B01000100,
  B01000111,
  B01000001,
  B11100001,
  B00000111
};
byte onesix[] = {
  B01000000,
  B11000111,
  B01000100,
  B01000100,
  B01000111,
  B01000101,
  B11100101,
  B00000111
};
byte twoone[] = {
  B11100000,
  B00100010,
  B00100110,
  B11100010,
  B10000010,
  B10000010,
  B11100010,
  B00000111
};
byte twotwo[] = {
  B11100000,
  B00100111,
  B00100001,
  B11100001,
  B10000111,
  B10000100,
  B11100100,
  B00000111
};
byte twothree[] = {
  B11100000,
  B00100111,
  B00100001,
  B11100001,
  B10000111,
  B10000001,
  B11100001,
  B00000111
};
byte twofour[] = {
  B11100000,
  B00100001,
  B00100011,
  B11100101,
  B10000111,
  B10000001,
  B11100001,
  B00000001
};
byte twofive[] = {
  B11100000,
  B00100111,
  B00100100,
  B11100100,
  B10000111,
  B10000001,
  B11100001,
  B00000111
};
byte twosix[] = {
  B11100000,
  B00100111,
  B00100100,
  B11100100,
  B10000111,
  B10000101,
  B11100101,
  B00000111
};
byte threeone[] = {
  B11100000,
  B00100010,
  B00100110,
  B11100010,
  B00100010,
  B00100010,
  B11100010,
  B00000111
};
byte threetwo[] = {
  B11100000,
  B00100111,
  B00100001,
  B11100001,
  B00100111,
  B00100100,
  B11100100,
  B00000111
};
byte threethree[] = {
  B11100000,
  B00100111,
  B00100001,
  B11100001,
  B00100111,
  B00100001,
  B11100001,
  B00000111
};
byte threefour[] = {
  B11100000,
  B00100001,
  B00100011,
  B11100101,
  B00100111,
  B00100001,
  B11100001,
  B00000001
};
byte threefive[] = {
  B11100000,
  B00100111,
  B00100100,
  B11100100,
  B00100111,
  B00100001,
  B11100001,
  B00000111
};
byte threesix[] = {
  B11100000,
  B00100111,
  B00100100,
  B11100100,
  B00100111,
  B00100101,
  B11100101,
  B00000111
};
byte fourone[] = {
  B00100000,
  B01100010,
  B10100110,
  B11100010,
  B00100010,
  B00100010,
  B00100010,
  B00000111
};
byte fourtwo[] = {
  B00100000,
  B01100111,
  B10100001,
  B11100001,
  B00100111,
  B00100100,
  B00100100,
  B00000111
};
byte fourthree[] = {
  B00100000,
  B01100111,
  B10100001,
  B11100001,
  B00100111,
  B00100001,
  B00100001,
  B00000111
};
byte fourfour[] = {
  B00100000,
  B01100111,
  B10100100,
  B11100100,
  B00100111,
  B00100001,
  B00100001,
  B00000111
};
byte fourfive[] = {
  B00100000,
  B01100111,
  B10100100,
  B11100100,
  B00100111,
  B00100101,
  B00100101,
  B00000111
};
byte foursix[] = {
  B11100000,
  B10000010,
  B10000110,
  B11100010,
  B00100010,
  B00100010,
  B11100010,
  B00000111
};
byte fiveone[] = {
  B11100000,
  B10000111,
  B10000001,
  B11100001,
  B00100111,
  B00100100,
  B11100100,
  B00000111
};
byte fivetwo[] = {
  B11100000,
  B10000111,
  B10000001,
  B11100001,
  B00100111,
  B00100001,
  B11100001,
  B00000111
};
byte fivethree[] = {
  B11100000,
  B10000001,
  B10000011,
  B11100101,
  B00100111,
  B00100001,
  B11100001,
  B00000001
};
byte fivefour[] = {
  B11100000,
  B10000111,
  B10000100,
  B11100100,
  B00100111,
  B00100001,
  B11100001,
  B00000111
};
byte fivefive[] = {
  B11100000,
  B10000111,
  B10000100,
  B11100100,
  B00100111,
  B00100101,
  B11100101,
  B00000111
};
byte fivesix[] = {
  B01000000,
  B11000010,
  B01000110,
  B01000010,
  B01000010,
  B01000010,
  B11100010,
  B00000111
};
byte sixone[] = {
  B11100000,
  B10000010,
  B10000110,
  B11100010,
  B10100010,
  B10100010,
  B11100010,
  B00000111
};
byte sixtwo[] = {
  B11100000,
  B10000111,
  B10000001,
  B11100001,
  B10100111,
  B10100100,
  B11100100,
  B00000111
};
byte sixthree[] = {
  B11100000,
  B10000111,
  B10000001,
  B11100001,
  B10100111,
  B10100001,
  B11100001,
  B00000111
};
byte sixfour[] = {
  B11100000,
  B10000001,
  B10000011,
  B11100101,
  B10100111,
  B10100001,
  B11100001,
  B00000001
};
byte sixfive[] = {
  B11100000,
  B10000111,
  B10000100,
  B11100100,
  B10100111,
  B10100001,
  B11100001,
  B00000111
};
byte sixsix[] = {
  B11100000,
  B10000111,
  B10000100,
  B11100100,
  B10100111,
  B10100101,
  B11100101,
  B00000111
};

void setup() {
  pinMode(sensorPin, INPUT);
  digitalWrite(sensorPin, HIGH);
  
  for (byte i = 2; i <= 13; i++){
      pinMode(i, OUTPUT);
  }
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
}

void loop() {
  sensorValue = digitalRead(sensorPin);

  if (sensorValue == lastTiltState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
    num1 = random(1,6);
    num2 = random(1,6);
  }
  
  //when the sensor orientation changes
  if (sensorValue != lastTiltState) {
    diceDisplay();
  }
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    lastTiltState = sensorValue;
  }
  
  delay(500);
}

void diceDisplay() {
  if (num1 == 1 && num2 == 1) {
    for(int i = 0 ; i < 100 ; i++)        //Loop display 100 times 
    {
      Display(oneone);
    }
  }
  if (num1 == 1 && num2 == 2) {
    for(int i = 0 ; i < 100 ; i++)
    {
      Display(onetwo);
    }
  }
  if (num1 == 1 && num2 == 3) {
    for(int i = 0 ; i < 100 ; i++)
    {
      Display(onethree);
    }
  }
  if (num1 == 1 && num2 == 4) {
    for(int i = 0 ; i < 100 ; i++)
    {
      Display(onefour);
    }
  }
  if (num1 == 1 && num2 == 5) {
    for(int i = 0 ; i < 100 ; i++)
    {
      Display(onefive);
    }
  }
  if (num1 == 1 && num2 == 6) {
    for(int i = 0 ; i < 100 ; i++)
    {
      Display(onesix);
    }
  }
  if (num1 == 2 && num2 == 1) {
    for(int i = 0 ; i < 100 ; i++)
    {
      Display(twoone);
    }
  }
  if (num1 == 2 && num2 == 2) {
    for(int i = 0 ; i < 100 ; i++)
    {
      Display(twotwo);
    }
  }
  if (num1 == 2 && num2 == 3) {
    for(int i = 0 ; i < 100 ; i++)
    {
      Display(twothree);
    }
  }
  if (num1 == 2 && num2 == 4) {
    for(int i = 0 ; i < 100 ; i++)
    {
      Display(twofour);
    }
  }
  if (num1 == 2 && num2 == 5) {
    for(int i = 0 ; i < 100 ; i++)
    {
      Display(twofive);
    }
  }
  if (num1 == 2 && num2 == 6) {
    for(int i = 0 ; i < 100 ; i++)
    {
      Display(twosix);
    }
  }
  if (num1 == 3 && num2 == 1) {
    for(int i = 0 ; i < 100 ; i++)
    {
      Display(threeone);
    }
  }
  if (num1 == 3 && num2 == 2) {
    for(int i = 0 ; i < 100 ; i++)
    {
      Display(threetwo);
    }
  }
  if (num1 == 3 && num2 == 3) {
    for(int i = 0 ; i < 100 ; i++)
    {
      Display(threethree);
    }
  }
  if (num1 == 3 && num2 == 4) {
    for(int i = 0 ; i < 100 ; i++)
    {
      Display(threefour);
    }
  }
  if (num1 == 3 && num2 == 5) {
    for(int i = 0 ; i < 100 ; i++)
    {
      Display(threefive);
    }
  }
  if (num1 == 3 && num2 == 6) {
    for(int i = 0 ; i < 100 ; i++)
    {
      Display(threesix);
    }
  }
  if (num1 == 4 && num2 == 1) {
    for(int i = 0 ; i < 100 ; i++)
    {
      Display(fourone);
    }
  }
  if (num1 == 4 && num2 == 2) {
    for(int i = 0 ; i < 100 ; i++)
    {
      Display(fourtwo);
    }
  }
  if (num1 == 4 && num2 == 3) {
    for(int i = 0 ; i < 100 ; i++)
    {
      Display(fourthree);
    }
  }
  if (num1 == 4 && num2 == 4) {
    for(int i = 0 ; i < 100 ; i++)
    {
      Display(fourfour);
    }
  }
  if (num1 == 4 && num2 == 5) {
    for(int i = 0 ; i < 100 ; i++)
    {
      Display(fourfive);
    }
  }
  if (num1 == 4 && num2 == 6) {
    for(int i = 0 ; i < 100 ; i++)
    {
      Display(foursix);
    }
  }
  if (num1 == 5 && num2 == 1) {
    for(int i = 0 ; i < 100 ; i++)
    {
      Display(fiveone);
    }
  }
  if (num1 == 5 && num2 == 2) {
    for(int i = 0 ; i < 100 ; i++)
    {
      Display(fivetwo);
    }
  }
  if (num1 == 5 && num2 == 3) {
    for(int i = 0 ; i < 100 ; i++)
    {
      Display(fivethree);
    }
  }
  if (num1 == 5 && num2 == 4) {
    for(int i = 0 ; i < 100 ; i++)
    {
      Display(fivefour);
    }
  }
  if (num1 == 5 && num2 == 5) {
    for(int i = 0 ; i < 100 ; i++)
    {
      Display(fivefive);
    }
  }
  if (num1 == 5 && num2 == 6) {
    for(int i = 0 ; i < 100 ; i++)
    {
      Display(fivesix);
    }
  }
  if (num1 == 6 && num2 == 1) {
    for(int i = 0 ; i < 100 ; i++)
    {
      Display(sixone);
    }
  }
  if (num1 == 6 && num2 == 2) {
    for(int i = 0 ; i < 100 ; i++)
    {
      Display(sixtwo);
    }
  }
  if (num1 == 6 && num2 == 3) {
    for(int i = 0 ; i < 100 ; i++)
    {
      Display(sixthree);
    }
  }
  if (num1 == 6 && num2 == 4) {
    for(int i = 0 ; i < 100 ; i++)
    {
      Display(sixfour);
    }
  }
  if (num1 == 6 && num2 == 5) {
    for(int i = 0 ; i < 100 ; i++)
    {
      Display(sixfive);
    }
  }
  if (num1 == 6 && num2 == 6) {
    for(int i = 0 ; i < 100 ; i++)
    {
      Display(sixsix);
    }
  }
}

void  Display(byte buffer2[]){
  // Turn on each row in series
  for (byte i = 0; i < 8; i++) {
      setCols(buffer2[i]); 
      
      digitalWrite(rows[i], HIGH);
      delay(1);
      digitalWrite(rows[i], LOW);
      delay(1);
  }
}

void setCols(byte b) {
    digitalWrite(COL_1, (~b >> 0) & 0x01); // Get the 1st bit: 10000000
    digitalWrite(COL_2, (~b >> 1) & 0x01); // Get the 2nd bit: 01000000
    digitalWrite(COL_3, (~b >> 2) & 0x01); // Get the 3rd bit: 00100000
    digitalWrite(COL_4, (~b >> 3) & 0x01); // Get the 4th bit: 00010000
    digitalWrite(COL_5, (~b >> 4) & 0x01); // Get the 5th bit: 00001000
    digitalWrite(COL_6, (~b >> 5) & 0x01); // Get the 6th bit: 00000100
    digitalWrite(COL_7, (~b >> 6) & 0x01); // Get the 7th bit: 00000010
    digitalWrite(COL_8, (~b >> 7) & 0x01); // Get the 8th bit: 00000001
}
