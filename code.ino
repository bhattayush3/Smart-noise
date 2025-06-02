#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialize the LCD (I2C address may vary, commonly 0x27 or 0x3F)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pin definitions
const int soundSensorPin = A0;  // Sound sensor analog pin
const int buzzerPin = 9;        // Buzzer digital pin

// Variables
int soundValue = 0;
const int threshold = 80;  // Adjust this threshold as needed

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  
  // Initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Sound:");
  
  // Set buzzer pin as output
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);
}

void loop() {
  // Read sound sensor value
  soundValue = analogRead(soundSensorPin);
  
  // Display on LCD
  lcd.setCursor(0, 1);
  lcd.print("Value: ");
  lcd.print(soundValue);
  lcd.print("    ");  // Clear remaining characters
  
  // Print to serial monitor for debugging
  Serial.print("Sound:");
  Serial.println(soundValue);
  
  // Check if sound exceeds threshold
  if (soundValue > threshold) {
    lcd.setCursor(13, 0);
    lcd.clear();
    lcd.print("WARNING!");
    activateBuzzer();
  } else {
    lcd.setCursor(13, 0);
    lcd.print("   ");  // Clear "LOUD!" when quiet
    digitalWrite(buzzerPin, LOW);
  }
  
  delay(100);  // Small delay to stabilize readings
}

void activateBuzzer() {
  digitalWrite(buzzerPin, HIGH);
  delay(100);  // Buzzer on time
  digitalWrite(buzzerPin, LOW);
}
