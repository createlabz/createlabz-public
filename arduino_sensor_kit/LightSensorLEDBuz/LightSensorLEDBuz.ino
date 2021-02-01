#define LDR A1
#define LED 6
#define buz 5

int inputval=0;
int outputval=0;

void setup() {
  // put your setup code here, to run once:
  pinMode(LDR,INPUT);
  pinMode(LED,OUTPUT);
  pinMode(buz,OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  inputval=analogRead(LDR);
  outputval=map(inputval,0,749,255,0);

  analogWrite(LED,outputval);
  tone(buz,outputval*5);
  
  Serial.println(outputval);

  delay(1000);
}
