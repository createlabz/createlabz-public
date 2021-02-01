#define SOUND A2
#define LED 6

int soundinput=0;
void setup() {
  // put your setup code here, to run once:
  pinMode(SOUND,INPUT);
  pinMode(LED,OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
 soundinput=analogRead(SOUND);
 Serial.println(soundinput);
 if (soundinput>=500){
  digitalWrite(LED,HIGH);
  delay(1000);
 }
 else{
  digitalWrite(LED,LOW);
 }
 delay(100);
}
