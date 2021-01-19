

void setup(){
pinMode(2,INPUT);
pinMode(5, OUTPUT);
pinMode(6, OUTPUT);
pinMode(8,OUTPUT);
}

void loop(){
 if (digitalRead(2) == LOW)
 { digitalWrite(5, HIGH);
   digitalWrite(6, LOW);
   digitalWrite(8,LOW);
 
 }

 else {
  digitalWrite(5,LOW);
  digitalWrite(6, HIGH);
  digitalWrite(8,HIGH);
 }
}
