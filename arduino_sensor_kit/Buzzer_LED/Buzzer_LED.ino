#define BUZZER 5
#define LED 6

void setup() {
  // put your setup code here, to run once:
  pinMode(BUZZER,OUTPUT);
  pinMode(LED,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  tone(BUZZER,1000);
  digitalWrite(LED,HIGH);
  delay(500);
  
  noTone(BUZZER);
  digitalWrite(LED,LOW);
  delay(500);
}
