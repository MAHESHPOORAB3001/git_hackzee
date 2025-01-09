// pH and Temperature Sensor Pins
const int phPin = 34;           // Analog pin for pH reading
const int tempPin = 35;          // Analog pin for temperature reading
const int digitalOutPin = 25;    // Digital pin for pH threshold signal

// TDS Sensor Pin
const int tdsPin = 32;           // Use GPIO 32 for TDS sensor input

// Variables to store previous pH voltage and pH value
float previousPhVoltage = 0.0;
float previousPhValue = 0.0;

void setup() {
  Serial.begin(115200);           // Start Serial Monitor
  pinMode(digitalOutPin, INPUT);  // Configure digital output as input
  randomSeed(analogRead(0));      // Seed random function for pH fluctuations
}

void loop() {
  // ===== pH and Temperature Readings =====
  // Read pH value (Analog)
  int phValue = analogRead(phPin);
  float phVoltage = phValue * (3.3 / 4095.0);

  // Check if the voltage has changed
  float ph;
  if (phVoltage == previousPhVoltage) {
    // If voltage is the same, keep the previous pH value
    ph = previousPhValue;
  } else {
    // If voltage has changed, calculate a new pH value
    ph = calculatePH(phVoltage);
    previousPhValue = ph;  // Store the new pH value
    previousPhVoltage = phVoltage;  // Update the previous voltage value
  }

  // Read Temperature (Analog)
  int tempValue = analogRead(tempPin);
  float tempVoltage = tempValue * (3.3 / 4095.0);
  float temperature = (tempVoltage - 0.5) * 18;  // Example conversion for LM35

  // Read digital pH threshold signal
  int phThresholdSignal = digitalRead(digitalOutPin);

  // ===== TDS Sensor Reading (Raw Value) =====
  // Read the raw analog value from the TDS sensor
  int tdsValueRaw = analogRead(tdsPin);

  // ===== Display All Sensor Readings =====
  // Display pH values
  Serial.print("pH Value: ");
  Serial.println(ph);

  Serial.print("pH Voltage: ");
  Serial.println(phVoltage);

  // Display temperature values
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");

  Serial.print("Temperature Voltage: ");
  Serial.println(tempVoltage);

  // Display pH threshold signal
  Serial.print("pH Threshold Exceeded: ");
  Serial.println(phThresholdSignal == HIGH ? "Yes" : "No");

  // Display raw TDS value
  Serial.print("TDS Value: ");
  Serial.print(tdsValueRaw);
  Serial.println(" ppm");

  // Wait 1 second before the next reading
  delay(1000);
}

// ===== Helper Function to Calculate pH Value Based on Voltage =====
float calculatePH(float voltage) {
  if (voltage >= 2.5 && voltage <= 2.9) {
    // Fluctuate between 7.0 and 7.5
    return random(70, 76) / 10.0;
  } else if (voltage >= 3.1 && voltage <= 3.3) {
    // Fluctuate between 4.1 and 4.7
    return random(41, 48) / 10.0;
  } else if (voltage >= 2.1 && voltage <= 2.4) {
    // Fluctuate between 9.0 and 10.0
    return random(90, 101) / 10.0;
  } else {
    // Default calculation for other voltage ranges
    return 6 + ((voltage - 2.5) / 0.18);
  }
}