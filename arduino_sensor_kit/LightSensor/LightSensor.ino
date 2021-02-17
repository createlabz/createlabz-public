#define LDR A3

int inputval=0;

void setup() {
  // put your setup code here, to run once:
  pinMode(LDR,INPUT);
  
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  inputval=analogRead(LDR);
  Serial.println(inputval);

  delay(1000);
}
