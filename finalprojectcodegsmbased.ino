#include <SoftwareSerial.h>
#include <SD.h>
#include <DS1302.h>
#include <TimeLib.h>// Install this library

SoftwareSerial sim(10, 11); // SoftwareSerial for the SIM module
const int analogPin = A0;
const int ledPin = 12;
const int threshold = 100;
const String number1 = "+254704358072";
const String number2 = "+254729938203";

bool ledOn = false;
bool callInProgress = false;
unsigned long callStartTime = 0;
const long callDuration = 20000;
const long callRedirectTime = 15000;
int currentNumber = 1;

DS1302 rtc(6, 5, 4); // DS1302 RTC object with CE, IO, and SCLK pins

File logFile; // SD card log file

void setup() {
  pinMode(analogPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  delay(7000);
  Serial.begin(9600);
  sim.begin(9600);
  delay(1000);

  // Enable write protection on the DS1302
  rtc.writeProtect(true);

  // Generate a unique log file name based on the current date and time
  String logFileName = getFormattedDateTimeForFileName() + ".log";

  // Initialize the SD card module
  if (SD.begin(10)) { // Pin 10 is the chip select for the SD card module
    Serial.println("SD card initialized.");
    logFile = SD.open(logFileName, FILE_WRITE); // Open the log file for writing
    if (logFile) {
      Serial.println("Log file opened: " + logFileName);
    } else {
      Serial.println("Error opening log file.");
    }
  } else {
    Serial.println("Error initializing SD card.");
  }

  Serial.println("System Started...");
  Serial.println("Type 's' to send an SMS, 'r' to receive an SMS, and 'c' to make a Call");
}

void loop() {
  int sensorValue = analogRead(analogPin);

  if (sensorValue < threshold && !callInProgress) {
    callNumber();
    ledOn = true;
    logMessage("Call initiated");
  } else if (sensorValue >= threshold) {
    if (callInProgress) {
      hangUpCall();
    }
    ledOn = false;
    logMessage("Call terminated");
  }

  if (callInProgress) {
    unsigned long currentMillis = millis();
    if (currentMillis - callStartTime >= callDuration) {
      hangUpCall();
      logMessage("Call duration elapsed");
      cycleNumbers();
    } else if (currentMillis - callStartTime >= callRedirectTime) {
      redirectCall();
      logMessage("Call redirected");
    }
  }

  if (sim.available() > 0) {
    Serial.write(sim.read());
  }

  if (ledOn) {
    digitalWrite(ledPin, !digitalRead(ledPin));
    delay(500);
  } else {
    digitalWrite(ledPin, LOW);
  }
}

void callNumber() {
  String targetNumber = (currentNumber == 1) ? number1 : number2;
  sim.print("ATD");
  sim.print(targetNumber);
  sim.print(";\r\n");
  delay(1000);

  callInProgress = true;
  callStartTime = millis();
  logMessage("Calling " + targetNumber);
}

void hangUpCall() {
  sim.println("ATH\r");
  delay(20000);
  callInProgress = false;
  logMessage("Call hung up");
}

void redirectCall() {
  String targetNumber = (currentNumber == 1) ? number1 : number2;
  sim.print("ATD");
  sim.print(targetNumber);
  sim.print(";\r\n");
  delay(1000);

  logMessage("Call redirected to " + targetNumber);
}

void cycleNumbers() {
  currentNumber = (currentNumber == 1) ? 2 : 1;
}

void logMessage(String message) {
  if (logFile) {
    String timestamp = getFormattedDateTime();
    logFile.print(timestamp + " - " + message + "\n");
    logFile.flush(); // Flush the data to the SD card
  }
}

String getFormattedDateTime() {
  time_t currentTime = now();
  return String(year(currentTime)) + "-" + formatTimeUnit(month(currentTime)) +
         "-" + formatTimeUnit(day(currentTime)) + " " + formatTimeUnit(hour(currentTime)) + ":" +
         formatTimeUnit(minute(currentTime)) + ":" + formatTimeUnit(second(currentTime));
}

String getFormattedDateTimeForFileName() {
  time_t currentTime = now();
  return String(year(currentTime)) + formatTimeUnit(month(currentTime)) +
         formatTimeUnit(day(currentTime)) + formatTimeUnit(hour(currentTime)) +
         formatTimeUnit(minute(currentTime)) + formatTimeUnit(second(currentTime));
}

String formatTimeUnit(int value) {
  if (value < 10) {
    return "0" + String(value);
  } else {
    return String(value);
  }
}
5f 6