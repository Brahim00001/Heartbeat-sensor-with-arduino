#include <LiquidCrystal.h>

// Pin configuration for LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Pulse sensor pin
const int pulsePin = A0;

// Variables for pulse sensing
int sensorValue = 0;
int pulseCount = 0;
unsigned long lastTime = 0;
int bpm = 0;  // Beats per minute
bool pulseDetected = false;

void setup() {
  // Set up the LCD
  lcd.begin(16, 2);  // Initialize the 16x2 LCD display
  lcd.print("Heart Rate:");

  // Initialize Serial Monitor for debugging
  Serial.begin(9600);
}

void loop() {
  // Read the pulse sensor value
  sensorValue = analogRead(pulsePin);

  // Check if the pulse sensor detects a heartbeat
  if (sensorValue > 500 && !pulseDetected) {
    pulseDetected = true;
    pulseCount++;
    
    // Calculate BPM based on pulse count and elapsed time
    unsigned long currentTime = millis();
    if (currentTime - lastTime >= 1000) {  // Every 1 second
      bpm = pulseCount * 60;  // Convert to beats per minute
      pulseCount = 0;  // Reset count
      lastTime = currentTime;
    }

    // Display the BPM on the LCD
    lcd.setCursor(0, 1);  // Move to second row
    lcd.print("BPM: ");
    lcd.print(bpm);

    // Also print BPM to the Serial Monitor for debugging
    Serial.print("BPM: ");
    Serial.println(bpm);
  }

  // Reset pulse detection when the signal goes low
  if (sensorValue < 500 && pulseDetected) {
    pulseDetected = false;
  }

  delay(10);  // Small delay for sensor stability
}
