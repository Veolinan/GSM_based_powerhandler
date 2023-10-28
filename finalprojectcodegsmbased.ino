#include <SoftwareSerial.h>
#include <SD.h>
#include <DS1302.h>  // Include the DS1302 RTC library

SoftwareSerial sim(10, 11);
const int analogPin = A0;
const int ledPin = 12;
const int threshold = 100;
const String number1 = "+254704358072";
const String number2 = "+254729938202";

bool ledOn = false;
bool callInProgress = false;
unsigned long callStartTime = 0;
const long callDuration = 20000;
const long callRedirectTime = 15000;
int currentNumber = 1;

File logFile;  // Declare an SD card file
DS1302 rtc(2, 3);  // Define the DS1302 RTC object (SCLK, IO)

void setup() {
  pinMode(analogPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  delay(7000);
  Serial.begin(9600);
  sim.begin(9600);
  delay(1000);

  // Initialize the DS1302 RTC
  rtc.begin();
  rtc.halt(false);
  rtc.writeProtect(false);

  // Initialize the SD card
  if (SD.begin()) {
    Serial.println("SD card initialized.");
    logFile = SD.open("log.txt", FILE_WRITE);  // Open the log file
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
    logFile.flush();
  }
}

String getFormattedDateTime() {
  DS1302::time_t currentTime = rtc.time();
  return String(currentTime.year) + "-" + formatTimeUnit(currentTime.mon) + "-" +
         formatTimeUnit(currentTime.mday) + " " + formatTimeUnit(currentTime.hour) + ":" +
         formatTimeUnit(currentTime.min) + ":" + formatTimeUnit(currentTime.sec);
}

String formatTimeUnit(byte value) {
  if (value < 10) {
    return "0" + String(value);
  } else {
    return String(value);
  }
}
