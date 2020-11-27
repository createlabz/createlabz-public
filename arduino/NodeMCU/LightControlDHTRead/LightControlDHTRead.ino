// Light and temperature control via AdaFruit
// Written by jeminico (Createlabz)

/************************ Relay Configuration *******************************/
// Relay pin
int relayPin = 15;
// Relay State
int state = LOW;
long relayTimer,tempTimer;
const long relayTimerDelay = 5000;

/************************ DHT Sensor Configuration *******************************/
// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain

// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor
#include "DHT.h"

 // Digital pin connected to the DHT sensor
#define DHTPIN 2    
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht(DHTPIN, DHTTYPE);

// Timer delay for reading temperature
const long tempTimerDelay = 1000;


/************************ Adafruit IO Configuration *******************************/
#include <ESP8266WiFi.h>
#include <AdafruitIO.h>
#include <Adafruit_MQTT.h>
#include <ArduinoHttpClient.h>
#include "AdafruitIO_WiFi.h"

// visit io.adafruit.com if you need to create an account,
// or if you need your Adafruit IO key.
#define IO_USERNAME    "YOUR_IO_USERNAME"
#define IO_KEY         "YOUR_IO_KEY"
// Wifi Configuration
#define WIFI_SSID       "YOUR_WIFI_SSID"
#define WIFI_PASS       "YOUR_WIFI_PASS"
// Initialize Adafruit IO wifi
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

// Set up the 'command' feed
AdafruitIO_Feed *command = io.feed("COMMAND FEED");

// Setup function
void setup() {
  // Start of initialization
  Serial.println("Initializing Setup..");
  // Initialize Serial
  Serial.begin(9600);
  
  // Initialize relay
  Serial.println("Initializing Relay..");
  pinMode(relayPin, OUTPUT);
  relayTimer = millis();
  
  // Initialize DHT Sensor
  Serial.println("Initializing DHT Sensor..");
  dht.begin();
  tempTimer = millis();
  
   // connect to io.adafruit.com
  Serial.println("Initializing Adafruit IO..");
  io.connect();
  // set up a message handler for the 'command' feed.
  // the handleMessage function (defined below)
  // will be called whenever a message is
  // received from adafruit io.
  command->onMessage(handleMessage);
  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  // we are connected
  Serial.println();
  Serial.println(io.statusText());

  Serial.println("Done Initializing Setup!");
}

// Main function
void loop() {
//  changeStateRelay();
  readTemp();
  io.run();
}

// Change state of the Relay
void changeStateRelay(){
  // Timer to change state
  if(millis() <= relayTimer + relayTimerDelay) return;
  relayTimer = millis();
  // Set state of relay
  if(state == LOW) state = HIGH;
  else state = LOW;
  digitalWrite(relayPin, state);
  Serial.println("Relay Change State");
}

// Read Temperature
void readTemp(){
  if(millis() <= tempTimer + tempTimerDelay) return;
  tempTimer = millis();
  
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  // Display DHT Sensor reading values
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
}

// Handle Adafruit message.
void handleMessage(AdafruitIO_Data *data) {
  int command = data->toInt();
  if (command == 1){ //light up the LED
    Serial.print("received <- ");
    Serial.println(command);
    digitalWrite(relayPin, HIGH);  
  } else {
    Serial.print("received <- ");
    Serial.println(command);
    digitalWrite(relayPin, LOW);
  }
}
