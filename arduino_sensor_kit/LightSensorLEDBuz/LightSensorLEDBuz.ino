#define LDR A3
#define LED 6
#define BUZ 5

int inputval=0;
int outputval=0;

void setup() {
  // put your setup code here, to run once:
  pinMode(LDR,INPUT);
  pinMode(LED,OUTPUT);
  pinMode(BUZ,OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  inputval=analogRead(LDR);
  outputval=map(inputval,0,756,255,0);

  analogWrite(LED,outputval);
  tone(BUZ,outputval*5);
  
  Serial.println(outputval);

  delay(1000);
}
