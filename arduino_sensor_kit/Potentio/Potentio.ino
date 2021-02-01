#define POT A0

int inPOT=0;

void setup() {
  // put your setup code here, to run once:
  pinMode(POT,INPUT);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  inPOT=analogRead(POT);
  Serial.println(inPOT);

  delay(1000);
}
