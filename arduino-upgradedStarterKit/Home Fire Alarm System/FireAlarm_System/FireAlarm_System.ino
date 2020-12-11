/*
 * Created: December 2020
 * by Nolf Ivan C. Labios
 * Home Fire Alarm System
*/

#include <IRremote.h>


const int t_sensor = A1; //LM35 Pin
const int f_sensor = A0; //Flame Sensor Pin

int f_val = 0;
float t_val;
float c_out;

const int IR_pin = 7;
IRrecv irrecv(IR_pin);

decode_results results;

int buz = 8;
int blu_pin = 9;  //Analog Pin for RGB Module
int red_pin = 10; //Analog Pin for RGB Module
int grn_pin = 11; //Analog Pin for RGB Module
int i=0;



void setup() {

  irrecv.enableIRIn();
  irrecv.blink13(true); //Arduino LED blinks when remote button is pressed
  
  pinMode(blu_pin,OUTPUT);
  pinMode(red_pin,OUTPUT);
  pinMode(grn_pin,OUTPUT);
  pinMode(buz,OUTPUT);

  pinMode(t_sensor,INPUT);
  pinMode(f_sensor,INPUT);
  Serial.begin(9600);
}

void loop() {

  RGB_color(0, 255, 0); // Green
  f_val = 0;
  c_out = 0;
  if (i==0){ //Checking Sensor Values
    f_val= analogRead(f_sensor);
    Serial.print("F sensor= ");
    Serial.print(f_val);
    Serial.print("\t");
   
    t_val=analogRead(t_sensor);
    t_val=(t_val*5000)/1024; //Converting temp to Celsius
    c_out=(t_val)/10;
  
    Serial.print("T in DegC= ");
    Serial.print(c_out);
    Serial.println();
    
    delay(1000); 
  }
  
  if (f_val < 890 || c_out>= 75) {
    emergencyAlert();
  } 
  
  if (f_val < 890 &&  c_out>= 75) {
    emergencyAlert();
  }
  
} 

void emergencyAlert(){ //When sensors are triggered
  i=1;
  RGB_color(255, 0, 0); // Red
  tone(buz,500,400);
  delay(500);
  remoteCheck();
}
  
void remoteCheck(){ //Check if remote is being operated
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
  
    if (results.value == 0xFF30CF && i==1 ) { //Turn off buzzer
      RGB_color(0, 0, 255); // Blue
      noTone (buz);
      delay(10000); //Wait for 10 seconds before restart
      i=0;
    }

    if (results.value == 0xFF18E7) { //RESET immediately
      RGB_color(255, 255, 0); // Yellow
      delay(1000);
      i=0;
    }
      
    irrecv.resume(); // Receive the next value
  }
}

void RGB_color(int red_light_value, int green_light_value, int blue_light_value) { //RGB color set
  analogWrite(red_pin, red_light_value);
  analogWrite(grn_pin, green_light_value);
  analogWrite(blu_pin, blue_light_value);
}
