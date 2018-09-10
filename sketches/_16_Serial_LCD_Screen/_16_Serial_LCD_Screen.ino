#include <Wire.h> // Call the wire library
#include <LiquidCrystal_I2C.h> // Call the I2C library
LiquidCrystal_I2C lcd(0x27, 16, 2); // Set LCD address to 0x27 for a
// 16-character and 2-line display
void setup() {
  lcd.begin(); // Initialize the lcd
  lcd.backlight();
  lcd.print("Arduino Handbook"); // Print a message to the LCD
}
void loop() { // Loop around again
}
