#define LED 6

void setup() {
  // put your setup code here, to run once:
  pinMode(LED,OUTPUT);
  Serial.begin(9600);
  Serial.println("Input 1 to turn ON the LED and 2 to turn OFF");

}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()){
    int num=Serial.parseInt();
    if (num==1){
      digitalWrite(LED,HIGH);
      Serial.println("LED is now ON");
    }
    if (num==2){
      digitalWrite(LED,LOW);
      Serial.println("LED is now OFF");
    }
    if (num > 2){
      Serial.println("Sorry, you have entered an invalid command.");
      Serial.println("Input 1 to turn ON the LED and 2 to turn OFF");
    }
    delay(500);
  }
}
