#define BUTTON 4

int buttonState=0;
int activated=0;
int count=0;

void setup() {
  // put your setup code here, to run once:
  pinMode(BUTTON,INPUT);
  Serial.begin(9600);
  Serial.println("0");
}

void loop() {
  // put your main code here, to run repeatedly:
  buttonState=digitalRead(BUTTON);
  if (buttonState==HIGH && activated==0){
    count++;
    Serial.println(count);
    activated=1;
  }
  if (buttonState==LOW){
    activated=0;
  }
  delay(500);
}
