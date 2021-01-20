/*
 * LinkIt One: LED Blink built in test
 * create by jeminico
 */

// Link-It-One LED built in pin
#define LED_BUILT_IN 13

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILT_IN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILT_IN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILT_IN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}
