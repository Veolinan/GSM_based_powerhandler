#include <SoftwareSerial.h>
#include <SD.h>  // Include the SD card library

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

void setup() {
  pinMode(analogPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  delay(7000);
  Serial.begin(9600);
  sim.begin(9600);
  delay(1000);

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
    logMessage("Call initiated");  // Log the call initiation
  } else if (sensorValue >= threshold) {
    if (callInProgress) {
      hangUpCall();
    }
    ledOn = false;
    logMessage("Call terminated");  // Log the call termination
  }

  if (callInProgress) {
    unsigned long currentMillis = millis();
    if (currentMillis - callStartTime >= callDuration) {
      hangUpCall();
      logMessage("Call duration elapsed");  // Log the call duration
      cycleNumbers();
    } else if (currentMillis - callStartTime >= callRedirectTime) {
      redirectCall();
      logMessage("Call redirected");  // Log the call redirection
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
    String timestamp = getTimeStamp();
    logFile.print(timestamp + " - " + message + "\n");
    logFile.flush();  // Flush the data to the SD card
  }
}

String getTimeStamp() {
  char timestamp[20];
  unsigned long currentTime = millis();
  unsigned long seconds = currentTime / 1000;
  unsigned long minutes = seconds / 60;
  unsigned long hours = minutes / 60;

  sprintf(timestamp, "%02lu:%02lu:%02lu", hours % 24, minutes % 60, seconds % 60);
  return String(timestamp);
}
