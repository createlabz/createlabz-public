const int LED = 9; // set pin for led
const int LDR = A1; //set pin for photoresistor

int inputval=0; //variable for values to be read from A1
int outval =0; //variable for output value from A1

void setup() {
//Initialize pinModes
  pinMode(LED, OUTPUT);
  pinMode(LDR, INPUT);

}

void loop() {
    inputval = analogRead(LDR); 
    outval = map(inputval, 0, 380, 255, 0); //The 0-1023 can be changed depending on light from your setup

    int lightval = constrain(outval, 0,255);//the contain output values within 0-255 range
    analogWrite(LED, lightval);  
    delay (500);
}
