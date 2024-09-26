#include <Servo.h>

// Define pins for the PIR sensors
int pirPinLeft = 2;   // Left PIR sensor connected to pin 2
int pirPinRight = 3;  // Right PIR sensor connected to pin 3
int pirPinCenter = 4; // Center PIR sensor connected to pin 4

// Define pin for the relay to control the fan motor
int relayPin = 5;     // Relay to turn on/off the fan

// Initialize variables to store the PIR sensor states
int pirStateLeft = LOW;
int pirStateRight = LOW;
int pirStateCenter = LOW;

// Servo motor object
Servo fanServo;

// Variable for the last position
int lastDetectedPosition = 90; // Starting at the center (90 degrees)


void setup() {
  // Set up PIR sensor pins as inputs
  pinMode(pirPinLeft, INPUT);
  pinMode(pirPinRight, INPUT);
  pinMode(pirPinCenter, INPUT);
  
  // Set up relay pin as output
  pinMode(relayPin, OUTPUT);

  // Attach the servo motor to pin 9
  fanServo.attach(9);

  // Initialize the fan at the center position
  fanServo.write(lastDetectedPosition);

  
  digitalWrite(relayPin, LOW); // Keep the fan motor off initially

}

void loop() {
 // Read the state of the PIR sensors
  pirStateLeft = digitalRead(pirPinLeft);
  pirStateRight = digitalRead(pirPinRight);
  pirStateCenter = digitalRead(pirPinCenter);

  // Check which PIR sensor detects motion
  if (pirStateLeft == HIGH) {
    lastDetectedPosition = 45;  // Turn the fan to the left (45 degrees)
    digitalWrite(relayPin, HIGH); // Turn on the fan motor 
  } else if (pirStateRight == HIGH) {
    lastDetectedPosition = 135;  // Turn the fan to the right (135 degrees)
    digitalWrite(relayPin, HIGH); // Turn on the fan motor 
  } else if (pirStateCenter == HIGH) {
    lastDetectedPosition = 90;   // Keep the fan at the center (90 degrees)
    digitalWrite(relayPin, HIGH); // Turn on the fan motor 
  } 

  // Move the fan to the last detected position
  fanServo.write(lastDetectedPosition);

  // Small delay to smooth out
  delay(100);

}
