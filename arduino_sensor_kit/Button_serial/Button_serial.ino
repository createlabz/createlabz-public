#define BUTTON 4

int buttonState=0;
void setup() {
  // put your setup code here, to run once:
  pinMode(BUTTON,INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  buttonState=digitalRead(BUTTON);
  if (buttonState==HIGH){
    Serial.println("Button is activated"); //Button is being pressed
    
  }
  if (buttonState==LOW){
    Serial.println("Button is deactivated"); //Button is not being pressed
  
  }
  delay(500);
}
