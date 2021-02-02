#include "Arduino_SensorKit.h"

unsigned long delayTime = 1000; // 1 second delay time

float temperature, airPressure, altitude, humidity, seaPressure;

// Time since program run
unsigned long seconds, minutes, hours;

// Parameters for detecting forecast
// Store pressure values(Max 10)
int seaPressureArray[10] = {0};
// Store the minute of last recorded pressure
int lastRecPresMin = 0;
// Store the hour of last recorded pressure
int lastRecPresHr = 0;
// Counter for recorded pressure
int recPresCounter = 0;
// Current month (Ex: January = 1 & December = 12)
int monthNow = 1; // Current month is january
// Identifier if first calibration is already done
bool doneCalibForecast = false;
// Set true if calibration is done in seconds
// Set false if calibration is done in minutes
bool isCalibDoneSec = true;

// Weather forecast types
#define CALIBRATION 0
#define SUN 1
#define SUN_CLOUD 2
#define CLOUD 3
#define RAIN 4
#define THUNDER 5

void setup() {
  // put your setup code here, to run once:
  // Initialize OLED diplay
  Oled.begin();
  // Set OLED Display mode
  Oled.setFlipMode(true); // If true rotates the display to 180 degrees

  // Initialize Air Pressure Sensor
  Pressure.begin();

  // Initialize DHT temperature and humidity sensor
  Environment.begin();
}

void loop() {
  // put your main code here, to run repeatedly:

  // Get time since boot
  getTime();

  // OLED Font type
  Oled.setFont(u8x8_font_chroma48medium8_r);

  // Set starting cursor
  Oled.setCursor(0,0);

  // Print header
  Oled.print("Weather Forecast");

  // Get Sensors data
  getSensorsData();

  // Get sea pressure and forecast, and display to OLED display
  getSeaPressure();

  // Display Temperature data to OLED display
  displayTemperature();

  // Display Air Pressure to OLED display
  displayPressure();

  // Display Altitude to OLED display
  displayAltitude();

  // Display humidity to OLED display
  displayHumidity();

  // Display time to OLED display
  displayTime();

  // Updates OLED display
  Oled.refreshDisplay();

  delay(delayTime);

}

void getSensorsData(){
  temperature = Pressure.readTemperature(); // Temperature in celcius
  airPressure = Pressure.readPressure() / 100; // Air pressure in hecto pascal (hPa)
  altitude = Pressure.readAltitude(); // Altitude in meter
  humidity = Environment.readHumidity(); // Humidity in percentage
}

void displayTemperature(){
  Oled.setCursor(0,1); // Set cursor on 2nd line
  Oled.print("Temp: "); // Print label
  Oled.print(temperature); // Print temperature in celcius
  Oled.print(" C"); // Print unit
}

void displayPressure(){
  Oled.setCursor(0,2); // Set cursor on 3rd line
  Oled.print("Pre: "); // Print label
//  Oled.print(airPressure); // Print air pressure in hecto pascal (hPa)
  Oled.print(seaPressure); // Print sea pressure in hecto pascal (hPa)
  Oled.print(" hPa"); // Print unit
}

void displayAltitude(){
  Oled.setCursor(0,3); // Set cursor on 4th line
  Oled.print("Alt: "); // Print label
  Oled.print(altitude); // Print altitude in meter
  Oled.print(" m"); // Print unit
}

void displayHumidity(){
  Oled.setCursor(0,4); // Set cursor on 5th line
  Oled.print("Humid: "); // Print label
  Oled.print(humidity); // Print humidity in percentage
  Oled.print(" %"); // Print unit
}

/************************This is Zambretti Algorithm for weather forecasting.  *******************************/
/**
   For more information on the Zambretti Algorithm you may check this links:
   https://communities.sas.com/t5/SAS-Analytics-for-IoT/Zambretti-Algorithm-for-Weather-Forecasting/td-p/679487#
   This codes are base on and modified:
   https://github.com/fandonov/weatherstation/blob/master/weather-station/weather-station.ino
*/
// Time Since boot
void getTime() {
  // Convert milliseconds to seconds.
  seconds = (millis() / 1000l) % 60;
  // Convert milliseconds to minutes.
  minutes = (millis() / (1000l * 60l)) % 60;
  // Convert milliseconds to hours.
  hours = (millis() / (1000l * 60l * 60l)) % 24;
}

// Display time since boot
void displayTime() {
  // Set cursor (6th Line)
  Oled.setCursor(0, 5);
  // Display time since boot
  Oled.print("Time: ");
  // Display hour
  if (hours < 10) Oled.print("0");
  Oled.print(hours);
  Oled.print(":");
  // Display minutes
  if (minutes < 10) Oled.print("0");
  Oled.print(minutes);
  Oled.print(":");
  // Display seconds
  if (seconds < 10) Oled.print("0");
  Oled.print(seconds);
}


void getSeaPressure() {
  // Store sea pressure every minute (if isCalibDoneSec is true storing will be in seconds)
  if (minutes != lastRecPresMin or isCalibDoneSec) {
    // Get sea pressure
    seaPressure = stationToSeaLevel((Pressure.readPressure() / 100), Pressure.readAltitude(), Pressure.readTemperature());
    
    // Store sea pressure
    if (recPresCounter >= 10) {
      doneCalibForecast = true;
      for (int i = 0; i < 9; i++) seaPressureArray[i] = seaPressureArray[i + 1];
      seaPressureArray[recPresCounter - 1] = seaPressure;
    } else {
      seaPressureArray[recPresCounter] = seaPressure;
      recPresCounter++;
    }
    
    // Get forecast and display
    getDisplayForecast();

    // Store current minute
    lastRecPresMin = minutes;
  }
}

void getDisplayForecast() {
  // Forecast not yet calibrated
  if (!doneCalibForecast) {
    displayForecast(CALIBRATION); // Records 10 sea pressure to finish calibration..
  }
  // Forecast already calibrated
  else {
    // Get forecast number base on Zambretti Algorithm
    int Z = calculateZambretti((seaPressureArray[9] + seaPressureArray[8] + seaPressureArray[7]) / 3, (seaPressureArray[0] + seaPressureArray[1] + seaPressureArray[2]) / 3, monthNow);
    // Rising
    if (seaPressureArray[9] + seaPressureArray[8] + seaPressureArray[7] - seaPressureArray[0] - seaPressureArray[1] - seaPressureArray[2] >= 3) {
      if (Z < 3) displayForecast(SUN);
      else if (Z >= 3 and Z <= 9) displayForecast(SUN_CLOUD);
      else if (Z > 9 and Z <= 17) displayForecast(CLOUD);
      else if (Z > 17) displayForecast(RAIN);
    }
    // Falling
    else if (seaPressureArray[0] + seaPressureArray[1] + seaPressureArray[2] - seaPressureArray[9] - seaPressureArray[8] - seaPressureArray[7] >= 3) {
      if (Z < 4) displayForecast(SUN);
      else if (Z >= 4 and Z < 14) displayForecast(SUN_CLOUD);
      else if (Z >= 14 and Z < 19)displayForecast(THUNDER);
      else if (Z >= 19 and Z < 21) displayForecast(CLOUD);
      else if (Z >= 21) displayForecast(RAIN);
    }
    // Steady
    else {
      if (Z < 5) displayForecast(SUN);
      else if (Z >= 5 and Z <= 11) displayForecast(SUN_CLOUD);
      else if (Z > 11 and Z < 14) displayForecast(CLOUD);
      else if (Z >= 14 and Z < 19) displayForecast(THUNDER);
      else if (Z > 19) displayForecast(RAIN);
    }
  }
}

// Display Weather Forecast
void displayForecast(int weatherType) {
  // Set cursor (7th Line)
  Oled.setCursor(0, 6);
  // Clear 7th line
  Oled.clearLine(6);

  // Check weather type
  switch (weatherType) {
    case CALIBRATION:
      Oled.print("Calibrating..");
      break;
    case SUN:
      Oled.print("Sunny");
      break;
    case SUN_CLOUD:
      Oled.print("Sunny Cloudy");
      break;
    case CLOUD:
      Oled.print("Cloudy");
      break;
    case RAIN:
      Oled.print("Rainy");
      break;
    case THUNDER:
      Oled.print("Thunderstorms");
      break;
  }
}

// Get pressure at sea level
int stationToSeaLevel(int p, int height, int t) {
  return (double) p * pow(1 - 0.0065 * (double)height / (t + 0.0065 * (double)height + 273.15), -5.275);
}

// Zambretti calculation
int calculateZambretti(int curr_pressure, int prev_pressure, int mon) {
  if (curr_pressure < prev_pressure) {
    //FALLING
    if (mon >= 4 and mon <= 9)
      //summer
    {
      if (curr_pressure >= 1030)
        return 2;
      else if (curr_pressure >= 1020 and curr_pressure < 1030)
        return 8;
      else if (curr_pressure >= 1010 and curr_pressure < 1020)
        return 18;
      else if (curr_pressure >= 1000 and curr_pressure < 1010)
        return 21;
      else if (curr_pressure >= 990 and curr_pressure < 1000)
        return 24;
      else if (curr_pressure >= 980 and curr_pressure < 990)
        return 24;
      else if (curr_pressure >= 970 and curr_pressure < 980)
        return 26;
      else if (curr_pressure < 970)
        return 26;
    }
    else {
      //winter
      if (curr_pressure >= 1030)
        return 2;
      else if (curr_pressure >= 1020 and curr_pressure < 1030)
        return 8;
      else if (curr_pressure >= 1010 and curr_pressure < 1020)
        return 15;
      else if (curr_pressure >= 1000 and curr_pressure < 1010)
        return 21;
      else if (curr_pressure >= 990 and curr_pressure < 1000)
        return 22;
      else if (curr_pressure >= 980 and curr_pressure < 990)
        return 24;
      else if (curr_pressure >= 970 and curr_pressure < 980)
        return 26;
      else if (curr_pressure < 970)
        return 26;
    }
  }
  // RISING
  else if (curr_pressure > prev_pressure) {
    // Summer
    if (mon >= 4 and mon <= 9) {
      if (curr_pressure >= 1030)
        return 1;
      else if (curr_pressure >= 1020 and curr_pressure < 1030)
        return 2;
      else if (curr_pressure >= 1010 and curr_pressure < 1020)
        return 3;
      else if (curr_pressure >= 1000 and curr_pressure < 1010)
        return 7;
      else if (curr_pressure >= 990 and curr_pressure < 1000)
        return 9;
      else if (curr_pressure >= 980 and curr_pressure < 990)
        return 12;
      else if (curr_pressure >= 970 and curr_pressure < 980)
        return 17;
      else if (curr_pressure < 970)
        return 17;
    }
    // Winter
    else {
      if (curr_pressure >= 1030)
        return 1;
      else if (curr_pressure >= 1020 and curr_pressure < 1030)
        return 2;
      else if (curr_pressure >= 1010 and curr_pressure < 1020)
        return 6;
      else if (curr_pressure >= 1000 and curr_pressure < 1010)
        return 7;
      else if (curr_pressure >= 990 and curr_pressure < 1000)
        return 10;
      else if (curr_pressure >= 980 and curr_pressure < 990)
        return 13;
      else if (curr_pressure >= 970 and curr_pressure < 980)
        return 17;
      else if (curr_pressure < 970)
        return 17;
    }
  }
  else {
    if (curr_pressure >= 1030)
      return 1;
    else if (curr_pressure >= 1020 and curr_pressure < 1030)
      return 2;
    else if (curr_pressure >= 1010 and curr_pressure < 1020)
      return 11;
    else if (curr_pressure >= 1000 and curr_pressure < 1010)
      return 14;
    else if (curr_pressure >= 990 and curr_pressure < 1000)
      return 19;
    else if (curr_pressure >= 980 and curr_pressure < 990)
      return 23;
    else if (curr_pressure >= 970 and curr_pressure < 980)
      return 24;
    else if (curr_pressure < 970)
      return 26;
  }
}
