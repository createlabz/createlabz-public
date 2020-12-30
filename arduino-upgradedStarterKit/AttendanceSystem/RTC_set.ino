/* 
 *  Created: December 2020
 *  by Nolf Ivan C. Labios
 *  This code is used to set the RTC Module
 */

// for the RTC
#include <virtuabotixRTC.h> 
// Wiring construct: CLK =4 | DAT=7 | RST=8
// Change pin number according to the pins used
virtuabotixRTC myRTC(4, 7, 8);  //Instance of the virtuabotixRTC class

void setup() {
  Serial.begin(9600);

 // Setup for the RTC  
   // Construct: setDS1302Time(seconds, minutes, hours, day of the week, day of the month, month, year)
   // myRTC.setDS1302Time(10, 33, 23, 4, 23, 12, 2020); //Set to actual date/time
   //Remove or comment function above once date/time is set. This is done only once
  
}

void loop() {
 // This allows for the update of variables for time or accessing the individual elements.
   myRTC.updateTime();

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
 delay(1000);
}
