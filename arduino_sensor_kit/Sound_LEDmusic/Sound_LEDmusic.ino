#define SOUND A2
#define LED 6

int soundinput=0;
int lightval=0;

void setup() {
  // put your setup code here, to run once:
  pinMode(SOUND,INPUT);
  pinMode(LED,OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
 soundinput=analogRead(SOUND);
 lightval=map(soundinput,0,500,0,255);
 analogWrite(LED,lightval);

 delay(100);
}
