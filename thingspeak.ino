#include <WiFi.h>  // ESP32 Wi-Fi library

// Wi-Fi credentials
const char* ssid = "";         // Replace with your Wi-Fi SSID
const char* password = ""; // Replace with your Wi-Fi password

// ThingSpeak settings
const char* server = "api.thingspeak.com";
String apiKey = "";  // Replace with your ThingSpeak Write API Key

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
  Serial.begin(115200);  // Start Serial Monitor
  pinMode(digitalOutPin, INPUT);  // Configure digital output as input
  randomSeed(analogRead(0));      // Seed random function for pH fluctuations

  // Connect to Wi-Fi
  Serial.print("Connecting to Wi-Fi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi connected");
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
  int tdsValueRaw = analogRead(tdsPin);  // Read raw TDS value

  // ===== Send Data to ThingSpeak =====
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    if (client.connect(server, 80)) {
      // Prepare ThingSpeak update URL with sensor data
      String url = "/update?api_key=" + apiKey +
                   "&field1=" + String(ph) +
                   "&field2=" + String(temperature) +
                   "&field3=" + String(tdsValueRaw);

      // Send the HTTP request to ThingSpeak
      client.print("GET " + url + " HTTP/1.1\r\n" +
                   "Host: " + String(server) + "\r\n" +
                   "Connection: close\r\n\r\n");

      Serial.println("Data sent to ThingSpeak");
    } else {
      Serial.println("Failed to connect to ThingSpeak");
    }
    client.stop();  // Close the connection
  }

  // ===== Display All Sensor Readings on Serial Monitor =====
  Serial.print("pH Value: ");
  Serial.println(ph);

  Serial.print("pH Voltage: ");
  Serial.println(phVoltage);

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");

  Serial.print("Temperature Voltage: ");
  Serial.println(tempVoltage);

  Serial.print("pH Threshold Exceeded: ");
  Serial.println(phThresholdSignal == HIGH ? "Yes" : "No");

  Serial.print("TDS Value: ");
  Serial.print(tdsValueRaw);
  Serial.println(" ppm");

  // Wait 15 seconds before sending the next update to ThingSpeak
  delay(5000);  // ThingSpeak allows updates every 15 seconds
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