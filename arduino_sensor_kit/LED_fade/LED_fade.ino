#define LED 6

int light=0;
int fade=10;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(LED,light);

  light=light+fade;
  if (light<=0 || light >=255){
    fade=-fade;
  }
  delay(50);
}
