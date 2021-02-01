#define POT A0
#define LED 6

int inPOT=0;
int outPOT=0;

void setup() {
  // put your setup code here, to run once:
  pinMode(POT,INPUT);
  pinMode(LED,OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  inPOT=analogRead(POT);
  outPOT=map(inPOT,0,1023,0,255);

  analogWrite(LED,outPOT);
  Serial.println(outPOT);

  delay(1000);
}
