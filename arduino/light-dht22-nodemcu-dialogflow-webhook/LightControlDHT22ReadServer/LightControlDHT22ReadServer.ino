// Load Wi-Fi library
#include <ESP8266WiFi.h>
/************************ Wifi Server Configuration *******************************/
// Replace with your network credentials
const char* ssid     = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// Set web server port number to 80
WiFiServer server(80);
// Variable to store the HTTP request
String header;
// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

// Timer to display local IP on serial monitor.
long getIPTimer;
long getIPTimerDelay = 5000;

/************************ Relay Configuration *******************************/
// Relay pin
int relayPin = 15;

/************************ DHT Sensor Configuration *******************************/
// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain

// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor
#include "DHT.h"

 // Digital pin connected to the DHT sensor
#define DHTPIN 4    
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
float humid,tempCelc,tempFaren;

void setup() {
  // Initialize Serial
  Serial.begin(9600);
  
  // Initialize relay
  Serial.println("Initializing Relay..");
  pinMode(relayPin, OUTPUT);

  // Initialize DHT Sensor
  Serial.println("Initializing DHT Sensor..");
  dht.begin();
  
  // Initialize WiFi Server
  Serial.print("Initializing WiFi Server..");
  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();

  // Print done initialize
   Serial.print("Done initializing.. ");
}

void loop(){
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    currentTime = millis();
    previousTime = currentTime;
    while (client.connected() && currentTime - previousTime <= timeoutTime) { // loop while the client's connected
      currentTime = millis();         
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            
            String deviceName;
            String deviceStatus;
            // turns the GPIOs on and off
            if (header.indexOf("GET /light/on") >= 0) {
              Serial.println("Light on");
              deviceName = "Light";
              deviceStatus = "on";
              digitalWrite(relayPin, HIGH);
            } else if (header.indexOf("GET /light/off") >= 0) {
              Serial.println("Light off");
              deviceName = "Light";
              deviceStatus = "off";
              digitalWrite(relayPin, LOW);
              // Set here
            } else if (header.indexOf("GET /sensor/dht22/temperature/read/celcius") >= 0) {
              readTemp();
              Serial.println("DHT22 Sensor read");
              Serial.print("Temp Read");
              Serial.println(tempCelc);
              deviceName = "DHT22";
              deviceStatus = String(tempCelc) + " in celcius";
            } 
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: application/json");
            client.println("Access-Control-Allow-Origin: *");
            client.println("");
            // Send JSON response
            client.print("{\""+deviceName+"\": \""
            +deviceStatus+"\"}");
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
  
  getIPAddress();
}

// Read Temperature
void readTemp(){
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  humid = dht.readHumidity();
  // Read temperature as Celsius (the default)
  tempCelc = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  tempFaren = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(humid) || isnan(tempCelc) || isnan(tempFaren)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(tempFaren, humid);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(tempCelc, humid, false);

  // Display DHT Sensor reading values
  Serial.print(F("Humidity: "));
  Serial.print(humid);
  Serial.print(F("%  Temperature: "));
  Serial.print(tempCelc);
  Serial.print(F("°C "));
  Serial.print(tempFaren);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
}

void getIPAddress(){
  // Delay display ip address
  if(millis() <= getIPTimer + getIPTimerDelay) return;
  getIPTimer = millis();
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
