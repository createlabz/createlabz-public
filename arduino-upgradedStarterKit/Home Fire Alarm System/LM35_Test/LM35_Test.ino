/*
 * Created: December 2020
 * by Nolf Ivan C. Labios
 * LM35 test for Home Fire Alarm System
*/

const int t_sensor= A1; // Assigning analog pin A5 to variable 'sensor'
float c_out; //variable to store temperature in degree Celsius

void setup() {
  pinMode(sensor,INPUT); // Configuring sensor pin as input
  Serial.begin(9600);
}

void loop() {
  float reading=analogRead(t_sensor); //Reading the value from sensor
  float vout= (reading*5000)/1024; //Converting to Celsius
  c_out= vout/10;
  
  Serial.print("Sensor Reading = ");
  Serial.print(reading);
  Serial.print("\t ");
  Serial.print("in Degrees C = ");
  Serial.print(temp);
  Serial.println();

  delay(1000); //Delay of 1 second for ease of viewing 
}
