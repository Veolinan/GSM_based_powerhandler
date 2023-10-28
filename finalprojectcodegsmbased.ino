
#include <SoftwareSerial.h>

SoftwareSerial sim(10, 11);
const int analogPin = A0;
const int ledPin = 12;
const int threshold = 100; // Set the threshold value as per your requirement
const String number1 = "+254704358072";     // Your first number
const String number2 = "+254729938202"; // Your second number

bool ledOn = false; // Track the LED state
bool callInProgress = false; // Track if a call is in progress
unsigned long callStartTime = 0; // Track the start time of the call
const long callDuration = 20000; // Call duration in milliseconds (20 seconds)
const long callRedirectTime = 15000; // Time before redirecting the call in milliseconds (15 seconds)
int currentNumber = 1; // 1 for the first number, 2 for the second number

void setup() {
  pinMode(analogPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); // Ensure the LED is initially off
  delay(7000); // Delay for 7 seconds to ensure the modules get the signal
  Serial.begin(9600);
  sim.begin(9600);
  delay(1000);
  Serial.println("System Started...");
  Serial.println("Type 's' to send an SMS, 'r' to receive an SMS, and 'c' to make a Call");
}

void loop() {
  int sensorValue = analogRead(analogPin);
  
  if (sensorValue < threshold && !callInProgress) {
    // A0 is low, initiate the call and start blinking the LED
    callNumber();
    ledOn = true; // Turn on the LED
  } else if (sensorValue >= threshold) {
    // A0 is high, terminate the call and stop blinking the LED
    if (callInProgress) {
      hangUpCall();
    }
    ledOn = false; // Turn off the LED
  }

  if (callInProgress) {
    // Check if the call duration has elapsed
    unsigned long currentMillis = millis();
    if (currentMillis - callStartTime >= callDuration) {
      // Call duration has elapsed, hang up the call
      hangUpCall();
      cycleNumbers(); // Cycle to the next number
    } else if (currentMillis - callStartTime >= callRedirectTime) {
      // Redirect the call to the other number after callRedirectTime
      redirectCall();
    }
  }

  if (sim.available() > 0) {
    Serial.write(sim.read());
  }

  // Blink the LED if it's on
  if (ledOn) {
    digitalWrite(ledPin, !digitalRead(ledPin)); // Toggle the LED state
    delay(500); // Blink interval of 0.5 seconds
  } else {
    digitalWrite(ledPin, LOW); // Ensure the LED is off when not blinking
  }
}

void callNumber() {
  String targetNumber = (currentNumber == 1) ? number1 : number2;
  // Make the call to the current target number
  sim.print("ATD");
  sim.print(targetNumber);
  sim.print(";\r\n");
  delay(1000); // Wait for 10 seconds (adjust as needed)

  // Mark the call as in progress
  callInProgress = true;
  callStartTime = millis();
}

void hangUpCall() {
  // Hang up the call
  sim.println("ATH\r");
  delay(20000);
  callInProgress = false; // Mark the call as no longer in progress
}

void redirectCall() {
  String targetNumber = (currentNumber == 1) ? number1 : number2;
  // Redirect the call to the other target number
  sim.print("ATD");
  sim.print(targetNumber);
  sim.print(";\r\n");
  delay(1000); // Wait for 10 seconds (adjust as needed)
}

void cycleNumbers() {
  // Cycle to the next number (1 to 2 or 2 to 1)
  currentNumber = (currentNumber == 1) ? 2 : 1;
}
