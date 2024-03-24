bool sens = false;
int ldrVal = 0;
byte flag = 0;
int count = 0;
int max_count = 300; //300 -- 5mins


void setup() {
  // put your setup code here, to run once:
pinMode(9, INPUT);
pinMode(10, OUTPUT);
Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
sens = digitalRead(9);
ldrVal = analogRead(A0);

Serial.print("ldr Value: ");
Serial.println(ldrVal);
Serial.print("flag: ");
Serial.println(flag);

if (flag == 0 && ldrVal > 950 && sens == false){
  flag = 1;
  count = max_count;
}

if (flag == 1 && sens == true){
   Serial.println("noSens");
  if (count < 1){
  flag = 0;
  count = 0;
  Serial.println("expired_turning off");
  }
 
 // delay(3000);
}

switch(flag){
  case 0:
  digitalWrite(10, LOW);
  delay(250);
  Serial.println("OFF");
  break;

  case 1:
  digitalWrite(10, HIGH);
  Serial.println("ON");
  Serial.print("count: ");
  Serial.println(count);
  delay(1000);

  break;
}


if (flag == 1){
  
   if (count >  0){
    count = count - 1;
   }
}

}
