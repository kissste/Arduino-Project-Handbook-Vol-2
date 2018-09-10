// Code by brainy-bits.com and used with kind permission
// https://brainy-bits.com/tutorials/find-your-way-using-the-hmc5883l/

#include <Wire.h>
#include "FastLED.h"
#include <HMC5883L.h>

#define NUM_LEDS 16  // Number of LEDs on Ring
#define DATA_PIN_RING 3 // Pin 3 connected to RGB Ring

CRGB leds_RING[NUM_LEDS];

HMC5883L compass;
int fixedHeadingDegrees; // Used to store Heading value

void setup()
{
  Serial.begin(9600);
  Wire.begin(); // Setup I2C
  // Set up the FastLED library with the neopixel ring data
  FastLED.addLeds<NEOPIXEL, DATA_PIN_RING>(leds_RING, NUM_LEDS);

  // Set measurement range
  compass.setRange(HMC5883L_RANGE_1_3GA);

  // Set measurement mode
  compass.setMeasurementMode(HMC5883L_CONTINOUS);

  // Set data rate
  compass.setDataRate(HMC5883L_DATARATE_30HZ);

  // Set number of samples averaged
  compass.setSamples(HMC5883L_SAMPLES_8);

  // Set calibration offset. See HMC5883L_calibration.ino
  compass.setOffset(13, -224);
}

void loop()
{
  Vector norm = compass.readNormalize();

  // Calculate heading
  float heading = atan2(norm.YAxis, norm.XAxis);

  // Set declination angle on your location and fix heading
  // You can find your declination on: http://magnetic-declination.com/
  // (+) Positive or (-) for negative
  // For Dumfries, Scotland declination angle is -2'26W (negative)
  // Formula: (deg + (min / 60.0)) / (180 / M_PI);
  float declinationAngle = (2.0 - (26.0 / 60.0)) / (180 / M_PI);
  heading -= declinationAngle;

  // Correct for heading < 0deg and heading > 360deg
  if (heading < 0)
  {
    heading += 2 * PI;
  }

  if (heading > 2 * PI)
  {
    heading -= 2 * PI;
  }

  // Convert to degrees
  float headingDegrees = heading * 180 / M_PI;

  // To Fix rotation speed of HMC5883L Compass module
  if (headingDegrees >= 1 && headingDegrees < 240)
  {
    fixedHeadingDegrees = map (headingDegrees * 100, 0, 239 * 100, 0, 179 * 100) / 100.00;
  }
  else {
    if (headingDegrees >= 240)
    {
      fixedHeadingDegrees = map (headingDegrees * 100, 240 * 100, 360 * 100, 180 * 100, 360 * 100) / 100.00;
    }
  }

  int headvalue = fixedHeadingDegrees / 18;
  int ledtoheading = map(headvalue, 0, 15, 15, 0);

  // Clear the ring
  FastLED.clear();

  // New heading
  if (ledtoheading == 0) {
    leds_RING[15] = CRGB::Red;
    leds_RING[0] = CRGB::Green;
    leds_RING[14] = CRGB::Green;
  }
  else {
    if (ledtoheading == 15) {
      leds_RING[0] = CRGB::Red;
      leds_RING[15] = CRGB::Green;
      leds_RING[1] = CRGB::Green;
    }
    else {
      leds_RING[ledtoheading] = CRGB::Red;
      leds_RING[ledtoheading + 1] = CRGB::Green;
      leds_RING[ledtoheading - 1] = CRGB::Green;
    }
  }

  FastLED.setBrightness(50);
  FastLED.show();
  delay(100);
}
