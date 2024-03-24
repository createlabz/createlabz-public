

/*
  LED

  This example creates a Bluetooth® Low Energy peripheral with service that contains a
  characteristic to control an LED.

  The circuit:
  - Arduino MKR WiFi 1010, Arduino Uno WiFi Rev2 board, Arduino Nano 33 IoT,
    Arduino Nano 33 BLE, or Arduino Nano 33 BLE Sense board.

  You can use a generic Bluetooth® Low Energy central app, like LightBlue (iOS and Android) or
  nRF Connect (Android), to interact with the services and characteristics
  created in this sketch.

  This example code is in the public domain.
*/

#include <ArduinoBLE.h>
#include <Wire.h>
#include <BH1750.h>


BH1750 lightSensor;

BLEService lightService("19B10000-E8F2-537E-4F6C-D104768A1214"); // Bluetooth® Low Energy LED Service

// Bluetooth® Low Energy LED Switch Characteristic - custom 128-bit UUID, read and writable by central
BLEByteCharacteristic lightCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);

const int ledPin = LED_BUILTIN; // pin to use for the LED

void setup() {
  Serial.begin(9600);
  Wire.begin();
  lightSensor.begin();

  while (!Serial);

  // set LED pin to output mode
 // pinMode(ledPin, OUTPUT);

  // begin initialization
  if (!BLE.begin()) {
    Serial.println("starting Bluetooth® Low Energy module failed!");

    while (1);
  }

  // set advertised local name and service UUID:
  BLE.setLocalName("BH1750");
  BLE.setAdvertisedService(lightService);

  // add the characteristic to the service
  lightService.addCharacteristic(lightCharacteristic);

  // add service
  BLE.addService(lightService);

  // set the initial value for the characeristic:
  lightCharacteristic.writeValue(0);

  // start advertising
  BLE.advertise();

  Serial.println("LIGHT BLE Peripheral");
}

void loop() {
  // listen for Bluetooth® Low Energy peripherals to connect:
  BLEDevice central = BLE.central();

  // if a central is connected to peripheral:
  if (central) {
    Serial.print("Connected to central: ");
    // print the central's MAC address:
    Serial.println(central.address());

    // while the central is still connected to peripheral:
    while (central.connected()) {
      // if the remote device wrote to the characteristic,
     int lightValue = lightSensor.readLightLevel();// reading the value of the BH1750 sensor
     Serial.print("Light Level: ");
     Serial.println(lightValue);
      if (lightValue > 100){
        lightCharacteristic.writeValue(1);
      } else{
        lightCharacteristic.writeValue(0);
      }
     
     delay(2000);

    }

    // when the central disconnects, print it out:
    Serial.print(F("Disconnected from central: "));
    Serial.println(central.address());
  }
}
