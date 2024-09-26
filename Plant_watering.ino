// Define pins for sensors, relays, and other components
int pirPinLeft = 2;   // Left PIR sensor connected to pin 2
int pirPinRight = 3;  // Right PIR sensor connected to pin 3
int relayPin = 7;     // Relay for the water pump connected to pin 7


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
