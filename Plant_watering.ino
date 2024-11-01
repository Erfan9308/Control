// Define pins

int soilMoisturePin = A0;  // Analog pin for soil moisture sensor
int relayPin = 7;          // Relay to control the water pump
int ledGreen = 8;          // Green LED for "wet" indicator
int ledRed = 9;            // Red LED for "dry" indicator
int buttonPin = 6;         // Button for manual pump control (manual override)
// Threshold value for soil moisture level
int moistureThreshold = 400;  // Adjust this value based on the sensor's readings

void setup() {
  // Set pin modes
  pinMode(pirPinLeft, INPUT);
  pinMode(pirPinRight, INPUT);
  pinMode(relayPin, OUTPUT);

  // Initialize any other setups
  Serial.begin(9600);  // Begin serial communication for debugging

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
  if (!isWatering && (soilMoistureValue < moistureThreshold || buttonState == HIGH)) {
    // Start watering
    digitalWrite(relayPin, HIGH);
    digitalWrite(ledRed, HIGH);
    digitalWrite(ledGreen, LOW);
    isWatering = true;
    wateringStartTime = millis(); // Record start time
  }

  // Check if watering time has passed
  if (isWatering && millis() - wateringStartTime >= wateringDuration) {
    digitalWrite(relayPin, LOW); // Stop watering
    digitalWrite(ledRed, LOW);
    digitalWrite(ledGreen, HIGH);
    isWatering = false;
  }

  delay(1000);
}
