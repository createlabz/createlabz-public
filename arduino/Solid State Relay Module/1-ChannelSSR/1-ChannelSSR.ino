 /*
* This is the Arduino code Solid State Relay
 * to control turn ON or OFF AC or DC load
 * Watch the video https://youtu.be/64NatLeGsaE
 *  * 
 * Written by Ahmad Shamshiri for Robojax Video
 * Date: Jan 13, 2018, in Ajax, Ontario, Canada
 * Permission granted to share this code given that this
 * note is kept with the code.
 * Disclaimer: this code is "AS IS" and for educational purpose only.
 * 
 */


 // Introduction to 5v Solid State relay.
int relayPin = 8;// set pin 8 for relay output

// setup code for Robojax Solid State Relay
void setup() {
    // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  Serial.println("Robojax Solid State Relay ");
  pinMode(relayPin, OUTPUT);

}

// loop code for Robojax Solid State Relay
void loop() {

  // Turn the relay switch ON (Robojax.com/learn/arduino)
  digitalWrite(relayPin, LOW);// set relay pin to low 
  Serial.println("Relay ON ");
  delay(1000);

   // Turn the relay switch OFF (Robojax.com/learn/arduino)
  digitalWrite(relayPin, HIGH);// set relay pin to HIGH
  Serial.println("Relay OFF ");
  delay(1000);
}
