#include <Arduino.h>
#include <TFT_eSPI.h>   // Library for screen communication
#include <DHT.h>        // Library for DHT sensors
#include <SD.h>         // Library for SD card functionality

// Initialize TFT Screen
TFT_eSPI tft = TFT_eSPI();  // Create TFT object

// DHT Sensor Setup (adjust pin and type as needed)
#define DHTPIN 21      // Pin connected to the DHT sensor
#define DHTTYPE DHT22  // DHT 22 (AM2302), DHT 11, etc.
DHT dht(DHTPIN, DHTTYPE);

// Setup for I2S audio output
#define I2S_DATA_PIN 26    // I2S data output pin (change as needed)
#define I2S_LRCK_PIN 25    // I2S left-right clock pin (change as needed)
#define I2S_BCLK_PIN 22    // I2S bit clock pin (change as needed)

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  delay(1000);  // Allow time for Serial Monitor to connect

  Serial.println("=== ESP32 Board Information ===");

  // ESP32 Chip Information
  Serial.printf("Chip ID: %08X\n", ESP.getEfuseMac());
  Serial.printf("Chip Revision: %d\n", ESP.getChipRevision());
  Serial.printf("Flash Size: %d bytes\n", ESP.getFlashChipSize());
  Serial.printf("Free Heap: %d bytes\n", ESP.getFreeHeap());

  // TFT Screen Initialization
  Serial.println("\n=== Screen Information ===");
  tft.init();  // Initialize TFT screen

  // Fill screen with color to confirm the screen is working
  tft.fillScreen(TFT_BLUE);
  Serial.println("Screen initialized");

  // Check TF Card (microSD card) functionality
  Serial.println("\n=== TF Card (microSD) Slot ===");
  if (!SD.begin()) {
    Serial.println("SD card initialization failed.");
  } else {
    Serial.println("SD card detected. Listing files:");
    File root = SD.open("/");
    while (true) {
      File entry = root.openNextFile();
      if (!entry) break;  // No more files
      Serial.print("  - ");
      Serial.print(entry.name());
      if (entry.isDirectory()) {
        Serial.println(" (directory)");
      } else {
        Serial.print(" (file, ");
        Serial.print(entry.size());
        Serial.println(" bytes)");
      }
      entry.close();
    }
    root.close();
  }

  // Initialize DHT Sensor
  Serial.println("\n=== Temperature and Humidity Sensor ===");
  dht.begin();
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  if (isnan(temp) || isnan(hum)) {
    Serial.println("DHT sensor not detected or not functioning correctly.");
  } else {
    Serial.printf("Temperature: %.2f°C\n", temp);
    Serial.printf("Humidity: %.2f%%\n", hum);
  }
}

void loop() {
  // Nothing in loop for now
}