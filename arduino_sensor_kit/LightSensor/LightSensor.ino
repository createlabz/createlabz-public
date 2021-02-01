#define LDR A1
#define LED 6

int inputval=0;
int outputval=0;

void setup() {
  // put your setup code here, to run once:
  pinMode(LDR,INPUT);
  pinMode(LED,OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  inputval=analogRead(LDR);
  outputval=map(inputval,0,749,255,0);

  analogWrite(LED,outputval);
  Serial.println(outputval);

  delay(1000);
}
