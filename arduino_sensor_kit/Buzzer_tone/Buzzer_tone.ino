#define BUZZER 5

void setup() {
  // put your setup code here, to run once:
  pinMode(BUZZER,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  //tone(BUZZER,1000);
  delay(500);
  noTone(BUZZER);
  delay(500);
}
