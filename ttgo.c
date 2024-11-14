#include <Arduino.h>
#include <TFT_eSPI.h> // TFT library for TTGO T-Display

#define PIR_PIN 13  // GPIO 13 for PIR sensor
#define LED_PIN 2   // Built-in LED for feedback

TFT_eSPI tft = TFT_eSPI(); // Create TFT display object

void setup() {
  // Initialize serial communication
  Serial.begin(115200);

  // Set up the PIR sensor pin and LED
  pinMode(PIR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  // Initialize the TFT display
  tft.init();
  tft.setRotation(3); // Set rotation for correct orientation
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(2);
  tft.setCursor(0, 0);

  // Display an initial message
  tft.println("Motion Detector");
  delay(2000);  // Wait for 2 seconds
  tft.fillScreen(TFT_BLACK);
}

void loop() {
  // Read the PIR sensor
  int motionDetected = digitalRead(PIR_PIN);

  if (motionDetected) {
    // Motion detected, turn on LED and display message on the screen
    digitalWrite(LED_PIN, HIGH);
    tft.fillScreen(TFT_RED);  // Red screen to indicate motion detected
    tft.setCursor(0, 50);
    tft.println("Motion detected!");
    Serial.println("Motion detected!");
    delay(500);  // Keep the LED on for a brief moment
  } else {
    // No motion, turn off LED and display a message
    digitalWrite(LED_PIN, LOW);
    tft.fillScreen(TFT_BLACK);  // Clear screen
    tft.setCursor(0, 50);
    tft.println("No motion detected.");
  }

  delay(100);  // Check the sensor every 100ms
}