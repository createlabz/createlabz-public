// Relay State Changing test
// Written by jeminico (Createlabz)

/************************ Relay Configuration *******************************/
// Relay pin
int relayPin = 15;
// Relay State
int state = LOW;
const long delayChangeState = 5000;

void setup() {
  // put your setup code here, to run once:
  
  // Start of initialization
  Serial.println("Initializing Setup..");
  // Initialize Serial
  Serial.begin(9600);
  
  // Initialize relay
  Serial.println("Initializing Relay..");
  pinMode(relayPin, OUTPUT);
  
  Serial.println("Done Initializing Setup!");
}

void loop() {
  // put your main code here, to run repeatedly:
  changeStateRelay();
}

// Change state of the Relay
void changeStateRelay(){
  // Set state of relay
  if(state == LOW) state = HIGH;
  else state = LOW;
  digitalWrite(relayPin, state);
  Serial.println("Relay Change State");
  delay(delayChangeState);
}
