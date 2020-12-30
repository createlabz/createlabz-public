/*
 * Created: December 2020
 * by Nolf Ivan C. Labios
 * Attendance System using RFID and RTC
*/

// for the RFID
#include <MFRC522.h> 
#include <SPI.h>
#define SS_RFID 10  //Serial input pin
#define RST_RFID 9  //Reset pin
MFRC522 rfid(SS_RFID, RST_RFID); //Instance of the MFRC522 class 
String uidString; // Set variable to hold card UID


// for the RTC
#include <virtuabotixRTC.h> 
// Wiring construct: CLK =4 | DAT=7 | RST=8
// Change pin number according to the pins used
virtuabotixRTC myRTC(4, 7, 8);  //Instance of the virtuabotixRTC class

// for RGB module and buzzer || use PWM pins for RGB module
const int buz = 2;
const int blu_pin = 6;  
const int red_pin = 5; 
const int grn_pin = 3; 


// for attendance time
const int atndceHour = 22;
const int atndceMin = 24;

//for user arrival time
int userArriveHour;
int userArriveMin;




void setup() {
  //Set output pins
	  pinMode(red_pin, OUTPUT);
	  pinMode(grn_pin, OUTPUT);
	  pinMode(blu_pin, OUTPUT);  
	  
	  pinMode(buz, OUTPUT);
  
  // Initialization 
	  Serial.begin(9600);
    
	  SPI.begin(); 
	  rfid.PCD_Init(); 

 // Setup for the RTC  
	 // Construct: setDS1302Time(seconds, minutes, hours, day of the week, day of the month, month, year)
	 //myRTC.setDS1302Time(10, 33, 23, 4, 23, 12, 2020); //Set to actual date/time
	 //Remove or comment function above once date/time is set. This is done only once
	
	  Serial.println("RTC is set!");
	  myRTC.updateTime();
	  datetime();
    Serial.println();
  }

void loop() {
  //Continuously look for new cards
  	  myRTC.updateTime();
  	  RGB_color(0, 0, 255); //Blue
	    
  if(rfid.PICC_IsNewCardPresent()) {
		datetime();
		readRFID();
		checkArrival();
  }
  delay(10);
}

void datetime(){
  Serial.print("Current Date / Time: ");
  Serial.print(myRTC.month); 
  Serial.print("/");
  Serial.print(myRTC.dayofmonth);
  Serial.print("/");
  Serial.print(myRTC.year);
  Serial.print(" ");
  Serial.print(myRTC.hours);
  Serial.print(":");
  Serial.print(myRTC.minutes);
  Serial.print(":");
  Serial.println(myRTC.seconds);
}

void readRFID() {
  rfid.PICC_ReadCardSerial();
  Serial.print("UID tag: ");
  uidString = String(rfid.uid.uidByte[0]) + " " + String(rfid.uid.uidByte[1]) + " " + 
  String(rfid.uid.uidByte[2]) + " " + String(rfid.uid.uidByte[3]);
  Serial.println(uidString);
 
  // Buzzer sound when card is read
  tone(buz, 2000); 
  delay(100);        
  noTone(buz);
  
  Serial.print("Arrival Time: ");
  Serial.print(myRTC.hours);
  Serial.print(":");
  Serial.print(myRTC.minutes);
  Serial.print(": ");
  
  
  //Store Arrival Time 
  userArriveHour = myRTC.hours;
  userArriveMin = myRTC.minutes;
  
  delay(100);
}


void checkArrival(){
  if((userArriveHour < atndceHour)||((userArriveHour==atndceHour) && (userArriveMin <= atndceMin))){
    RGB_color(0, 255, 0); // Green
    delay(2000);
    RGB_color(0, 0, 255); //Blue
    Serial.println("You are just in time!");
    Serial.println();
  }
  else{
    RGB_color(255, 0, 0); // Red
    delay(2000);
    RGB_color(0, 0, 255); //Blue
    Serial.println("Sorry, you arrived late");
    Serial.println();
  }
}

void RGB_color(int red_light_value, int green_light_value, int blue_light_value) { //RGB color set
  analogWrite(red_pin, red_light_value);
  analogWrite(grn_pin, green_light_value);
  analogWrite(blu_pin, blue_light_value);
}
