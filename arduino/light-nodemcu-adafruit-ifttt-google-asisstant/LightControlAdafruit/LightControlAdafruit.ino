// Light and temperature control via AdaFruit
// Written by jeminico (Createlabz)

/************************ Relay Configuration *******************************/
// Relay pin
int relayPin = 15;

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

void setup() {
  // put your setup code here, to run once:
  // Start of initialization
  Serial.println("Initializing Setup..");
  // Initialize Serial
  Serial.begin(9600);
  
  // Initialize relay
  Serial.println("Initializing Relay..");
  pinMode(relayPin, OUTPUT);
  
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

void loop() {
  // put your main code here, to run repeatedly:
  // Run Adafruit IO
  io.run();
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
