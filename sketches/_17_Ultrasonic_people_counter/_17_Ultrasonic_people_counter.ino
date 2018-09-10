#include <LiquidCrystal_I2C.h> // Call on the libraries
#include <NewPing.h>
#include <Wire.h>

#define TRIGGER_PIN 7 // Ultrasonic sensor trig to Arduino pin 7
#define ECHO_PIN 8 // Ultrasonic sensor echo to Arduino pin 8
#define MAX_DISTANCE 200

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
int LEDPin = 13; // Set LED to pin 13
int distance; // Variable for distance
int people = 0; // Variable for number of people
boolean count = false; // State for counting
LiquidCrystal_I2C lcd(0x27, 16, 2);
void setup() { // Run once to set up the LCD screen and LED
  lcd.begin();
  lcd.backlight();
  pinMode(LEDPin, OUTPUT); // Set the LED as an output
  lcd.print("People:"); // Print People: to the LCD screen
}
void loop() { // This loops forever to check for number of people
  delay(50);
  distance = sonar.ping_cm();// Ping every 50 milliseconds
  // If more than 100cm away, don't count
  if ( distance > 100 && count ) {
    count = false;
    digitalWrite(LEDPin, LOW);
  }
  // If less than 100cm away, count 1
  if ( distance < 100 && distance != 0 && !count) {
    count = true;
    people ++; // Keep adding 1 per count
    digitalWrite(LEDPin, HIGH);
    lcd.setCursor(10, 0);
    lcd.print(people); // Print number of people to LCD screen
  }
}
