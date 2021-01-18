

#define metalDetection 3
#define Led1 5
#define Led2 6
#define buzzer 7
#define value

void setup()
{
Serial.begin(9600);
pinMode(metalDetection,INPUT);
pinMode(Led1,OUTPUT);
pinMode(Led2,OUTPUT);
pinMode(buzzer,OUTPUT);

}
void loop(){
value = analogRead(metalDetection);
if(value!=state)
{
  state=value;
  if (state==0){
  digitalWrite(5,HIGH);
  digitalWrite(6, LOW);
  analogWrite(7, HIGH);
  tone(7, 500);
  }
    
   else{
  digitalWrite(5,LOW);
  digitalWrite(6, HIGH);
  analogWrite(7, LOW);
  noTone(7);
    }
 }
}
