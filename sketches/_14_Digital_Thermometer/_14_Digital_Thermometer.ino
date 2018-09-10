#include <LiquidCrystal.h> // Call the LCD library
#define sensor A0 // Pin connected to LM35 sensor (A0)
int Vin; // Reads the value from the Arduino pin
float Temperature; // Receives the voltage value converted to temp
float TF; // Receives the converted value in °F
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // Pins connected the LCD
void setup() {
  lcd.begin(16, 2); // The display is 16x2
  lcd.print("Temperature: "); // Sends text to the LCD
}
void loop() {
  Vin = analogRead (sensor); // Reads the A0 pin and
  // stores the value in Vin
  Temperature = (500 * Vin) / 1023; // Converts voltage value into
  // temperature and stores value
  // in Temperature (in °C)
  TF = ((9 * Temperature) / 5) + 32; // Changes °C to °F
  lcd.setCursor(0, 1); // Move cursor of LCD to next line
  lcd.print(TF); // Display the temperature on the LCD screen
  lcd.print(" F"); // Write F for the Fahrenheit scale
  delay(1000); // Wait for a second before reading the pin again
}
