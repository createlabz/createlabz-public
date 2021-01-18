/************************ GPS Initialization Setup *******************************/
#include <LGPS.h>
#include "GPSWaypoint.h"
#include "GPS_functions.h"
GPSWaypoint* gpsPosition;

/************************ Device Connection Setup *******************************/
// Set true if using GPRS (Sim Card) connection
// Set false if using WiFI connection
#define useGPRSConn true

// GPRS (Sim Card) connection initialization
#include <LGPRS.h>
#include <LGPRSClient.h>
#define APN "YOUR_SIM_APN"
#define APN_USER "YOUR_SIM_APN_USER"
#define APN_PASS "YOUR_SIM_APN_PASS"
LGPRSClient gprsClient;


// WiFi connection initialization
#include "LWiFi.h"
#include "LWiFiClient.h"
#define WIFI_SSID "YOUR_WIFI_SSID"
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"
#define WIFI_AUTH LWIFI_WPA  // choose from LWIFI_OPEN, LWIFI_WPA, or LWIFI_WEP.
LWiFiClient wifiClient;

// Mediatek Site URL
#define SITE_URL "api.mediatek.com"

// Client time checking
unsigned long responseTime;
const unsigned long max_response_time = 15000;

// Mediatek parameters
#define DEVICE_ID "D0r48ArZ"
#define DEVICE_KEY "0lu95lCEu50FBSh0"
#define GPS_DATA_ID "gps01"

// Link-It-One LED built in pin
#define LED_BUILT_IN 13

void setup()
{
  // Initialize Serial
  Serial.begin(9600);

  // Initialize built in LED
  pinMode(LED_BUILT_IN, OUTPUT);

  // keep retrying until connected to AP
  if (useGPRSConn) {
    Serial.print("Connecting to GPRS:");
    while (!LGPRS.attachGPRS(APN, APN_USER, APN_PASS))
    {
      delay(500);
    }
  } else {
    Serial.println("Connecting to WiFI.. ");
    while (0 == LWiFi.connect(WIFI_SSID, LWiFiLoginInfo(WIFI_AUTH, WIFI_PASSWORD)))
    {
      delay(1000);
      Serial.println("Reconnecting to WiFI.. ");
    }
  }

  // Initialize GPS
  LGPS.powerOn();
  Serial.println("LGPS Power on, and waiting ...");
  delay(3000);

  Serial.println("Success");
}

void loop()
{
  // Get GPS Data
  char GPS_formatted[] = "GPS fixed";
  gpsPosition = new GPSWaypoint();
  gpsSentenceInfoStruct gpsDataStruct;
  // Get GPS data and upload location and speed
  getGPSData(gpsDataStruct, GPS_formatted, gpsPosition);
  // Set latitude
  char* buffer_latitude = new char[30];
  sprintf(buffer_latitude, "%2.6f", gpsPosition->latitude);
  // Set longitude
  char* buffer_longitude = new char[30];
  sprintf(buffer_longitude, "%2.6f", gpsPosition->longitude);

  // Check number of satellites
  Serial.print("GPS Satellite:");
  Serial.println(gpsPosition->satellites);
  if ((gpsPosition->satellites) > 0) digitalWrite(13, HIGH);
  else digitalWrite(13, LOW);

  // Mediatek GPS format data
  // GPS data
  String upload_GPS =  String(buffer_latitude) + "," + String(buffer_longitude) + "," + "0" + "\n" + "latitude,," + buffer_latitude + "\n" + "longitude,," + buffer_longitude;
  // Dummy data
  //  String upload_GPS =  String(7.190708) + "," + String(125.455338) + "," + "0" + "\n" + "latitude,," + 7.190708 + "\n" + "longitude,," + 125.455338;

  // Check if using GPRS connection
  if (useGPRSConn) {
    Serial.println("Uploading data via GPRS Connection...");
    uploadData(DEVICE_ID, DEVICE_KEY, GPS_DATA_ID, upload_GPS, gprsClient);
  }
  // Check if using WiFi connection
  else {
    Serial.println("Uploading data via WIFI Connection...");
    uploadData(DEVICE_ID, DEVICE_KEY, GPS_DATA_ID, upload_GPS, wifiClient);
  }
}

template<class T>
void uploadData(const char* deviceID, const char* deviceKey, const char* dataKey, String valueForKey, T &client) {
  // Connect to Sie URL
  while (!client.connect(SITE_URL, 80)) {
    Serial.print(".");
    delay(500);
  }

  // Post GPS data to Site
  String postString = "POST /mcs/v2/devices/" + String(deviceID) + "/datapoints.csv HTTP/1.1";
  client.println(postString);
  String data = String(dataKey) + ",," + valueForKey;
  int dataLength = data.length();
  client.println("Host: api.mediatek.com");
  String deviceKeyString = "deviceKey: " + String(deviceKey);
  client.println(deviceKeyString);
  client.print("Content-Length: ");
  client.println(dataLength);
  client.println("Content-Type: text/csv");
  client.println("Connection: close");
  client.println();
  client.println(data);

  // Set current response time
  responseTime = millis();

  while (true) {
    // Check if client is available
    if (client.available()) {
      // Read client data
      char c = client.read();
      // Check if have response
      if (c < 0) break;
      // Print if have response
      else Serial.print(c);
    }
    // If client is not available
    else
    {
      // Check when to stop base on max response time
      if ((millis() - responseTime) > max_response_time) {
        // Stop client
        Serial.println("stop Client");
        client.stop();
        break;
      }
    }
  }
}
