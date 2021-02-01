#define BUTTON 4
#define LED 6

int buttonState=0;
void setup() {
  // put your setup code here, to run once:
  pinMode(BUTTON,INPUT);
  pinMode(LED,OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  buttonState=digitalRead(BUTTON);
  if (buttonState==HIGH){
    Serial.println("Button is activated and LED is ON"); //Button is being pressed
    digitalWrite(LED,HIGH);
  }
  if (buttonState==LOW){
    Serial.println("Button is deactivated and LED is OFF"); //Button is not being pressed
    digitalWrite(LED,LOW);
  }
  delay(500);
}
