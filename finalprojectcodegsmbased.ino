#include <SoftwareSerial.h>

SoftwareSerial sim(3, 2);
const int analogPin = A0;
const int ledPin = 12;
const int threshold = 100; // Set the threshold value as per your requirement
const String number1 = "+254704358072";     // Your first number
const String number2 = "+254769189571"; // Your second number
const String number3 = "+254785303908"; // Your third number

#define BUZZER_PIN 5  // Define the buzzer pin as digital pin 5

// Morse code timing
#define DOT_DURATION 250   // Duration of a dot in milliseconds
#define DASH_DURATION 1000 // Duration of a dash in milliseconds
#define SYMBOL_SPACE 250   // Gap between dots and dashes within a character
#define LETTER_SPACE 500   // Gap between letters
#define WORD_SPACE 1000    // Gap between words

bool ledOn = false; // Track the LED state
bool callInProgress = false; // Track if a call is in progress
unsigned long callStartTime = 0; // Track the start time of the call
const long callDuration = 30000; // Call duration in milliseconds (30 seconds)
const long callRedirectTime = 15000; // Time before redirecting the call in milliseconds (15 seconds)
int currentNumber = 1; // 1 for the first number, 2 for the second number, 3 for the third number

void setup() {
  pinMode(analogPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT); // Set the buzzer pin as an output
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
    sendSMSAndCall();
    playMorseCode("KIV"); // Play Morse code when sensorValue is below the threshold
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

void sendSMSAndCall() {
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
   
   // Send an SMS before making the call
   sendSMS(targetNumber);

   sim.print("ATD");
   sim.print(targetNumber);
   sim.print(";\r\n");
   delay(100); 

   callInProgress = true;
   callStartTime = millis();
}

void sendSMS(String targetNumber) {
  // Select the SMS storage
  sim.println("AT+CMGF=1"); // Set SMS mode to text
  delay(100);

  // Compose the SMS and send it
  sim.print("AT+CMGS=\"");
  sim.print(targetNumber);
  sim.println("\"");
  delay(100);
  sim.print("Power out"); // Your SMS message
  sim.print((char)26); // Ctrl+Z to send SMS
  delay(100);
}

void hangUpCall() {
   sim.println("ATH\r");
   delay(20000);
   callInProgress = false; 
}

void redirectCall() {
   cycleNumbers(); 
   sendSMSAndCall(); 
}

void cycleNumbers() {
   currentNumber++;
   
   if(currentNumber > 3) {
     currentNumber=1;
   }
}

void playMorseCode(String morseCode) {
  for (int i = 0; i < morseCode.length(); i++) {
    if (morseCode[i] == '.')
      playDot();
    else if (morseCode[i] == '-')
      playDash();
    delay(SYMBOL_SPACE); // Gap between dots and dashes within a character
  }
  delay(LETTER_SPACE - SYMBOL_SPACE); // Gap between letters
}

void playDot() {
  tone(BUZZER_PIN, 2000, DOT_DURATION); // Increase frequency to make it louder
  delay(DOT_DURATION);
  noTone(BUZZER_PIN);
}

void playDash() {
  tone(BUZZER_PIN, 2000, DASH_DURATION); // Increase frequency to make it louder
  delay(DASH_DURATION);
  noTone(BUZZER_PIN);
}
