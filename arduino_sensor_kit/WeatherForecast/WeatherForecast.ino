#include "Arduino_SensorKit.h"

// Time since program run
unsigned long seconds, minutes, hours;

// Time delay
unsigned long delayTime = 1000;

// Parameters for detecting forecast
// Store pressure values(Max 10)
int pressureArray[10] = {0};
// Store the minute of last recorded pressure
int lastRecPresMin = 0;
// Store the hour of last recorded pressure
int lastRecPresHr = 0;
// Counter for recorded pressure
int recPresCounter = 0;
// Current month (Ex: January = 1 & December = 12)
int monthNow = 1;
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

  // Start serial for debugging
  Serial.begin(9600);

  // Start OLED Display
  Oled.begin();
  // Set true to flip display if not false.
  Oled.setFlipMode(false);

  // Start DHT Temperature and Humidity Sensor
  Environment.begin();

  // Start Barometer pressure Sensor
  Pressure.begin();
}

void loop() {
  // put your main code here, to run repeatedly:

  // Get current time (Since program run)
  getTime();

  // Set OLED font type
  Oled.setFont(u8x8_font_chroma48medium8_r);
  // Set starting cursor (1st Line)
  Oled.setCursor(0, 0);
  // Print Weather Forecast header text
  Oled.print("Weather Forecast");

  // Display temperature to OLED Screen
  displayTemperature();

  // Display humidity to OLED Screen
  displayHumidity();

  // Display pressure to OLED Screen
  displayPressure();

  // Display altitude to OLED Screen
  displayAltitude();

  // Display time to OLED Screen (Since Program run)
  displayTime();

  // Display forecast
  getSeaPressure();

  // Update display
  Oled.refreshDisplay();

  delay(delayTime);
}

void getTime() {
  // Convert milliseconds to seconds.
  seconds = (millis() / 1000l) % 60;
  // Convert milliseconds to minutes.
  minutes = (millis() / (1000l * 60l)) % 60;
  // Convert milliseconds to hours.
  hours = (millis() / (1000l * 60l * 60l)) % 24;
}

void displayTemperature() {
  // Set cursor (2nd Line)
  Oled.setCursor(0, 1);
  // Get and print Barometer temperature sensor data (in Celcius).
  Oled.print("Temp: ");
  Oled.print(Pressure.readTemperature());
  Oled.print(" C");
}

void displayHumidity() {
  // Set cursor (3rd Line)
  Oled.setCursor(0, 2);
  // Get and Display DHT Humidity Sensor data.
  Oled.print("Humid: ");
  Oled.print(Environment.readHumidity());
  Oled.print(" %");
}

void displayPressure() {
  // Set cursor (4th Line)
  Oled.setCursor(0, 3);
  // Get and display Barometer atmospheric pressure sensor data (in hecto Pascal).
  Oled.print("Pre: ");
  // Get sea pressure
  int seapressure = stationToSeaLevel((Pressure.readPressure() / 100), Pressure.readAltitude(), Pressure.readTemperature());
  //  // Convert atmospheric pressure from pascal (Pa) to hecto pascal (hPa)
  //  float atmHpa = Pressure.readPressure() / 100;
  Oled.print(seapressure);
  Oled.print(" hPa");

}

void displayAltitude() {
  // Set cursor (5th Line)
  Oled.setCursor(0, 4);
  // Get and display altitude sensor data
  Oled.print("Alt: ");
  Oled.print(Pressure.readAltitude());
  Oled.print(" m");
}

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

/************************This is Zambretti Algorithm for weather forecasting.  *******************************/
/**
   For more information on the Zambretti Algorithm you may check this links:
   https://communities.sas.com/t5/SAS-Analytics-for-IoT/Zambretti-Algorithm-for-Weather-Forecasting/td-p/679487#

   This codes are base on and modified:
   https://github.com/fandonov/weatherstation/blob/master/weather-station/weather-station.ino
*/
void getSeaPressure() {
  // Store sea pressure every minute (if isCalibDoneSec is true storing will be in seconds)
  if (minutes != lastRecPresMin or isCalibDoneSec) {
    // Get sea pressure
    int seapressure = stationToSeaLevel((Pressure.readPressure() / 100), Pressure.readAltitude(), Pressure.readTemperature());
    
    // Store sea pressure
    if (recPresCounter >= 10) {
      doneCalibForecast = true;
      for (int i = 0; i < 9; i++) pressureArray[i] = pressureArray[i + 1];
      pressureArray[recPresCounter - 1] = seapressure;
    } else {
      pressureArray[recPresCounter] = seapressure;
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
    displayForecast(CALIBRATION);
  }
  // Forecast already calibrated
  else {
    // Get forecast number base on Zambretti Algorithm
    int Z = calculateZambretti((pressureArray[9] + pressureArray[8] + pressureArray[7]) / 3, (pressureArray[0] + pressureArray[1] + pressureArray[2]) / 3, monthNow);
    // Rising
    if (pressureArray[9] + pressureArray[8] + pressureArray[7] - pressureArray[0] - pressureArray[1] - pressureArray[2] >= 3) {
      if (Z < 3) displayForecast(SUN);
      else if (Z >= 3 and Z <= 9) displayForecast(SUN_CLOUD);
      else if (Z > 9 and Z <= 17) displayForecast(CLOUD);
      else if (Z > 17) displayForecast(RAIN);
    }
    // Falling
    else if (pressureArray[0] + pressureArray[1] + pressureArray[2] - pressureArray[9] - pressureArray[8] - pressureArray[7] >= 3) {
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
