#define relayPin 9
#define buttonPin 4
#define soundSensorPin A2

int buttonState = 0; // Store button state
int prevRelayState = 0;

int soundValue = 0; // Store sound sensor value
int soundTreshold = 300; // Set the sound treshold

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // For debugging purpose

  pinMode(buttonPin,  INPUT); // Set button pin as input
  pinMode(relayPin, OUTPUT); // Set relay pin as output

}

void loop() {
  // put your main code here, to run repeatedly:
  onButtonChange();
  onSoundChange();

  // Delay running for 50ms
  delay(50);

}

void onButtonChange(){
  // Get button state
  buttonState = digitalRead(buttonPin);
  // Check if button is pressed
  if(buttonState == HIGH) onRelayChange();
}

void onSoundChange(){
  // Get multiple readings (32 readings)
  for(int i = 0; i < 32; i++) soundValue += analogRead(soundSensorPin);
  soundValue >>= 5; // Bitshift to 5 to calculate average reading (Divide by 32)
  Serial.println(soundValue);

  // If the sound sensor value is higher than sound treshold change the state of the relay
  if(soundValue > soundTreshold){
    Serial.print(" Over the sound treshold");
    onRelayChange();
  }
}

void onRelayChange(){
  // Change the previous state of the relay
  // If previous state is low make it high
  if(prevRelayState == LOW) prevRelayState = HIGH;
  // If previous state is high make it low.
  else prevRelayState = LOW;
  
  // Set the relay state
  digitalWrite(relayPin, prevRelayState);

  // Delay for a 1 second to change the relay state
  delay(1000);
}
