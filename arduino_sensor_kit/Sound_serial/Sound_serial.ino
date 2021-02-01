#define SOUND A2

int soundinput=0;
void setup() {
  // put your setup code here, to run once:
  pinMode(SOUND,INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
 soundinput=analogRead(SOUND);
 Serial.println(soundinput);
 delay(500);
}
