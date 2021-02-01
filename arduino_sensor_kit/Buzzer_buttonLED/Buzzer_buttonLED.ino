#define BUZZER 5
#define LED 6
#define BUTTON 4

int buttonState=0;

void setup() {
  // put your setup code here, to run once:
  pinMode(BUZZER,OUTPUT);
  pinMode(LED,OUTPUT);
  pinMode(BUTTON,INPUT);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  buttonState=digitalRead(BUTTON);
  if (buttonState==HIGH){
    tone(BUZZER,1000);
    digitalWrite(LED,HIGH); 
    Serial.println("Button is pressed");
  }
  if (buttonState==LOW){
    noTone(BUZZER);
    digitalWrite(LED,LOW);
    Serial.println("Button is not being pressed");
  }
  delay(50);
}
