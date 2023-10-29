#include <SoftwareSerial.h>

SoftwareSerial sim(2, 3);
const int analogPin = A0;
const int ledPin = 12;
const int threshold = 100; // Set the threshold value as per your requirement
const String number1 = "+254704358072";     // Your first number
const String number2 = "+254769189571"; // Your second number
const String number3 = "+254785303908"; // Your third number

bool ledOn = false; // Track the LED state
bool callInProgress = false; // Track if a call is in progress
bool callRedirected = false; // Track if a call has been redirected
unsigned long callStartTime = 0; // Track the start time of the call
const long callDuration = 30000; // Call duration in milliseconds (20 seconds)
const long callRedirectTime = 1500; // Time before redirecting the call in milliseconds (15 seconds)
int currentNumber = 1; // 1 for the first number, 2 for the second number, 3 for the third number

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
    currentNumber = 1; // Always start from the first number when A0 is low
    callNumber();
    ledOn = true; // Turn on the LED
    callRedirected = false; // Reset the redirected flag when a new call is initiated
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
      callRedirected = false; // Reset the redirected flag when a new cycle starts
    } else if (!callRedirected && currentMillis - callStartTime >= callRedirectTime) {
      // Redirect the call to the other number after callRedirectTime only once per cycle
      redirectCall();
      callRedirected = true; // Set the redirected flag after redirecting a call
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
   String targetNumber;
   
   switch(currentNumber) {
     case 1:
       targetNumber = number1;
       break;
     case 2:
       targetNumber = number2;
       break;
     case 3:
       targetNumber = number3;
       break;
     default:
       return; 
   }
   
   sim.print("ATD");
   sim.print(targetNumber);
   sim.print(";\r\n");
   delay(100); 

   callInProgress = true;
   callStartTime = millis();
}

void hangUpCall() {
   sim.println("ATH\r");
   delay(20000);
   callInProgress = false; 
}

void redirectCall() {
   cycleNumbers(); 
   if(currentNumber ==2){
     sendSMS(number2,"Power out, send maintenance");
   }
   else if(currentNumber ==3){
     sendSMS(number3,"Kilo India Victor Unserviceable is initiated");
   }
   callNumber(); 
}

void cycleNumbers() {
   currentNumber++;
   
   if(currentNumber > 3) {
     currentNumber =1;
}
}

void sendSMS(String number, String message){
   sim.println("AT+CMGF=1"); 
   delay(100);
   sim.println("AT+CMGS=\""+number+"\"");
   delay(100);
   sim.println(message); 
   delay(100);
   sim.println((char)26); 
}
