# Smart Home Security System Using TTGO (ESP32)

This project implements a motion detection-based smart home security system using a TTGO ESP32 board and a PIR (Passive Infrared) sensor. The system detects motion, activates a visual indicator (LED), and displays a notification on the TTGO's TFT display to alert the user of any movement in the monitored area.

## Features
- Motion Detection: Detects movement using a PIR sensor.
- Real-Time Feedback: Displays "Motion Detected" or "No Motion" on the TTGO’s TFT display.
- Visual Indicator: Built-in LED lights up when motion is detected.
- Wireless Connectivity: Powered by the ESP32, which can be expanded for wireless notifications or cloud integration.
- Low Power Consumption: Ideal for long-term use with battery power.

## Components Required
- **TTGO ESP32 Development Board** (e.g., TTGO T-Display or TTGO T-Call)
- **PIR Sensor** (e.g., HC-SR501 or similar)
- **LED** (Optional for visual indication)
- **Jumper Wires**
- **Breadboard** (Optional for prototyping)
- **Power Supply** (Battery or USB for the TTGO)

## Wiring Diagram
- **PIR Sensor**:
  - VCC → 3V (or 5V depending on your PIR sensor model)
  - GND → GND
  - OUT → GPIO 13 (or any other available GPIO pin on the TTGO)
  
- **LED** (Optional for visual feedback):
  - Anode → GPIO 2 (or any other available GPIO pin)
  - Cathode → GND

## Software Requirements
- **Arduino IDE** or **PlatformIO**
- **ESP32 Board Support** in Arduino IDE

### Steps to Set Up the Environment
1. **Install Arduino IDE** (if not already installed).
2. **Add ESP32 Board**:
   - Go to `File` → `Preferences` in Arduino IDE.
   - In the "Additional Boards Manager URLs" field, add:
     ```
     https://dl.espressif.com/dl/package_esp32_index.json
     ```
   - Go to `Tools` → `Board` → `Boards Manager`, search for **ESP32**, and install it.
   
3. **Select the Correct Board**:
   - Go to `Tools` → `Board` and select your TTGO ESP32 board (e.g., `ESP32 Dev Module`).
   
4. **Install Libraries**:
   - **TFT_eSPI** for TTGO’s TFT display:
     - Go to `Sketch` → `Include Library` → `Manage Libraries`.
     - Search for `TFT_eSPI` and install it.
   
5. **Upload the Code**: Connect your TTGO board to your computer, select the correct **COM port**, and upload the sketch.

## Code

```cpp
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
```

### Explanation of Code:
1. **PIR Sensor**: Reads motion data from the PIR sensor connected to GPIO 13.
2. **TFT Display**: Displays motion status ("Motion detected" or "No motion detected") on the TFT screen.
3. **LED**: A visual indicator to light up when motion is detected.
4. **Serial Monitor**: Outputs motion status for debugging.

## Uploading the Code
1. Connect the **TTGO ESP32** to your computer via USB.
2. In **Arduino IDE**, select the correct **board** (e.g., ESP32 Dev Module) and **port**.
3. Click **Upload** to upload the code to the TTGO board.

## Future Enhancements
- **Wi-Fi Notifications**: Send motion alerts to a mobile app or server via Wi-Fi.
- **Sound Alarm**: Add a buzzer to activate when motion is detected.
- **Cloud Integration**: Log data to the cloud (e.g., AWS, ThingSpeak) for remote monitoring.
- **Camera Integration**: Capture photos or videos when motion is detected using a compatible camera module.
- **Battery Operation**: Power the TTGO and sensors via battery for portable use.

## Contributing
Feel free to fork the repository, open issues, or submit pull requests for enhancements or bug fixes.

## License
This project is licensed under the MIT License.
