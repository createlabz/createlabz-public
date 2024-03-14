
//install bluetooth serial
#include <BluetoothSerial.h>
byte recv = 0;
BluetoothSerial myBT;

int brightness = 0;

//digitlal setup
const int ledPin = 19;  // 16 corresponds to GPIO16

// setting PWM properties
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;


void setup() {
  // put your setup code here, to run once:
  pinMode(21, OUTPUT);
  pinMode(19, OUTPUT);
  myBT.begin("esp32BTclassic");
  Serial.begin(9600);

  //LED PWM SETUP
// configure LED PWM functionalitites
   ledcSetup(ledChannel, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(ledPin, ledChannel);
}

void loop() {
  // put your main code here, to run repeatedly:


if (myBT.available()>0){

  recv = myBT.read() ;
  Serial.write(recv);

  switch (recv) {
    case 'A':
    digitalWrite(21, HIGH);
 
   break;

    case 'B':
    digitalWrite(21, LOW);
    
    break;

    case 'C':
    //Serial.write(recv);
    brightness = 0;
    int avail = myBT.available();
    int nully;
        switch(avail){
          case 4:
          brightness = brightness + ((myBT.read())-48)*100;
          brightness = brightness + ((myBT.read())-48)*10;
          brightness = brightness + ((myBT.read())-48);
          nully = myBT.read();
          break;

          case 3:
          brightness = brightness + ((myBT.read())-48)*10;
          brightness = brightness + ((myBT.read())-48);
          nully = myBT.read();
          break;
 
          case 2:
          brightness = brightness + ((myBT.read())-48);
          nully = myBT.read();
          break;

        }

    break;
   
    }

  ledcWrite(ledChannel, brightness);
  delay(15);
  Serial.print("brightness----");
  Serial.println(brightness);
  } 
}




