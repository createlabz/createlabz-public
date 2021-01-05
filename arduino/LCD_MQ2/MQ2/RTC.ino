#include <OneWire.h>

#include <MQ2.h>

#include "U8glib.h"

U8GLIB_ST7920_128X64_4X u8g(10);

int Analog_Input = A1;
int smoke, lpg;
int read_value;
int Greenled = 8; 
int Redled = 9; 

MQ2 mq2(Analog_Input);
int sensorThreshold = 1;

void draw(void) {

  //u8g.setFont(u8g_font_unifont);
  u8g.setFont(u8g_font_osb18);
   u8g.drawStr( 25, 27, "Part 3:");
   u8g.drawStr( 10, 52, "Tutorials");
}


void picture(void) {
  u8g.setFont(u8g_font_osb18);
  u8g.drawStr( 0, 18, "Interfacing");
  u8g.drawStr( 0, 38, "GLCD with");
  u8g.drawStr( 20, 58, "Arduino");
}

void loop(void) {
  
  float = mq2.read(true); //set it false if you don't want to print the values in the Serial
  lpg = mq2.readLPG();
  smoke = mq2.readSmoke();
 
  if  (smoke == 0) {
    do {
    u8g.drawFrame(1,2,126,62);
    
  u8g.drawFrame(0,0,128,31);         
  u8g.drawFrame(0,33,128,31);   
      
  u8g.setFont(u8g_font_unifont);
  u8g.drawStr(40, 28, "Normal");
  u8g.drawStr(10, 15, "Smoke Reading:");    
  Serial.println(smoke); 
  u8g.drawStr(40, 61, "Normal");
  u8g.drawStr(20,46, "Gas Reading:");  
digitalWrite(R_led, LOW);  // Turn LED off.
digitalWrite(G_led, HIGH); // Turn LED on.       
  Serial.println(lpg); 

  } while( u8g.nextPage() );
  delay(2000);
   u8g.firstPage();  
  }

  if  (smoke > 0){ 
     u8g.firstPage();  
  do {
     u8g.drawFrame(0,0,128,31);         
  u8g.drawFrame(0,33,128,31);   
      
  u8g.setFont(u8g_font_unifont);
  u8g.drawStr(40, 28, "WARNING");
  u8g.drawStr( 10, 15, "Smoke Reading:");    
  Serial.println(smoke); 
  u8g.drawStr(40, 61, "WARNING");
  u8g.drawStr(20,46, "Gas Reading:");         
  Serial.println(lpg);
digitalWrite(Redled, HIGH);  // Turn LED off.
digitalWrite(Greenled, LOW); // Turn LED on.
   
  } while( u8g.nextPage() );
  }
    
  }


void clearLCD(){
    u8g.firstPage();  
    do {
    } while( u8g.nextPage() );
}

void setup(void) {
  Serial.begin(9600);
  mq2.begin();
  pinMode(Analog_Input, INPUT); // declare sensor as input
  pinMode(Redled,OUTPUT); // declare Red LED as output
  pinMode(Greenled,OUTPUT); // declare Green LED as output
    u8g.firstPage();  
  do {
    u8g.drawFrame(1,2,126,62);
    draw();
  } while( u8g.nextPage() );
  delay(2000);
  clearLCD();
   u8g.firstPage();  
  do {
     picture();
  } while( u8g.nextPage() );
  delay(3000);
 clearLCD();
  // rebuild the picture after some delay
  delay(50);
  
  // assign default color value
  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) {
    u8g.setColorIndex(255);     // white
  }
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) {
    u8g.setColorIndex(3);         // max intensity
  }
  else if ( u8g.getMode() == U8G_MODE_BW ) {
    u8g.setColorIndex(1);         // pixel on
  }
  else if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
    u8g.setHiColorByRGB(255,255,255);
  }
}
