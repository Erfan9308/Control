// Define pins

int soilMoisturePin = A0;  // Analog pin for soil moisture sensor
int relayPin = 7;          // Relay to control the water pump
int ledGreen = 8;          // Green LED for "wet" indicator
int ledRed = 9;            // Red LED for "dry" indicator
int buttonPin = 6;         // Button for manual pump control (manual override)

// Threshold value for soil moisture level
int moistureThreshold = 400;  // Adjust this value based on your sensor's readings

void setup() {
  // Set up pins
  pinMode(relayPin, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(buttonPin, INPUT);

  // Start with the water pump off
  digitalWrite(relayPin, LOW);

  // Initialize serial communication for monitoring (optional)
  Serial.begin(9600);
}

void loop() {
  // Read soil moisture sensor value
  int soilMoistureValue = analogRead(soilMoisturePin);

  // Read button state for manual override
  int buttonState = digitalRead(buttonPin);

  // Print moisture value to the serial monitor (for debugging)
  Serial.print("Soil Moisture Value: ");
  Serial.println(soilMoistureValue);

  // Check if soil is dry (moisture value below threshold) or if manual button is pressed
  if (soilMoistureValue < moistureThreshold || buttonState == HIGH) {
    // If soil is dry or button is pressed, turn on the water pump
    digitalWrite(relayPin, HIGH);
    // Turn on the red LED (dry status)
    digitalWrite(ledRed, HIGH);
    // Turn off the green LED (wet status)
    digitalWrite(ledGreen, LOW);
  } else {
    // If soil is wet, turn off the water pump
    digitalWrite(relayPin, LOW);
    // Turn on the green LED (wet status)
    digitalWrite(ledGreen, HIGH);
    // Turn off the red LED (dry status)
    digitalWrite(ledRed, LOW);
  }

  // Delay for 1 second before the next sensor reading
  delay(1000);
}
