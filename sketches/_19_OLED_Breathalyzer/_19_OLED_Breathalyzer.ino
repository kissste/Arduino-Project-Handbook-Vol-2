// Re-created with kind permission from Nick Koumaris educ8s.tv
// Call the SPI, Wire, Adafruit_GFX, and Adafruit_SDD1306 libraries
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 4 // Define the OLED screen
int TIME_UNTIL_WARMUP = 4; // Time for the warm-up delay in minutes
unsigned long time;
int analogPin = 0; // Set analog pin as A0
int val = 0; // Set a value to read from the analog pin
Adafruit_SSD1306 display(OLED_RESET);
void setup() { // Set up the OLED screen
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
}
void loop() { // Take the reading and show it onscreen
  delay(100);
  val = readAlcohol();
  printTitle();
  printWarming();
  time = millis() / 1000;
  time /= 60;
  if (time <= TIME_UNTIL_WARMUP) { // If warm-up is less than 4 minutes
    time = map(time, 0, TIME_UNTIL_WARMUP, 0, 100); // Show countdown
    display.drawRect(10, 50, 110, 10, WHITE); //Empty Bar
    display.fillRect(10, 50, time, 10, WHITE);
  } else // When warm-up time has passed
    // the value and message are printed on the screen
  {
    printTitle();
    printAlcohol(val);
    printAlcoholLevel(val);
  }
  display.display();
}
void printTitle() { // Position and text of title on the screen
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(22, 0);
  display.println("Breath Analyzer");
}
void printWarming() { // Warm-up message
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(30, 24);
  display.println("Warming up");
}
void printAlcohol(int value) { // Print alcohol value to screen
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(50, 10);
  display.println(val);
}
void printAlcoholLevel(int value) { // Print message to screen
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(20, 25);
  if (value < 200) { // If value read is less than 200, you are sober
    display.println("You are sober...");
  }
  if (value >= 200 && value < 280) { // If value read is between 200
    // and 280, print "You had a beer?"
    display.println("You had a beer?");
  }
  if (value >= 280 && value < 350) {
    display.println("Two or more beers.");
  }
  if (value >= 350 && value < 450) {
    display.println("I smell VODKA!");
  }
  if (value > 450) {
    display.println("You are drunk!");
  }
}
// Finds average by summing 3 readings and dividing by 3
// for better accuracy
int readAlcohol() {
  int val = 0;
  int val1;
  int val2;
  int val3;
  display.clearDisplay();
  val1 = analogRead(analogPin);
  delay(10);
  val2 = analogRead(analogPin);
  delay(10);
  val3 = analogRead(analogPin);
  val = (val1 + val2 + val3) / 3;
  return val;
}
