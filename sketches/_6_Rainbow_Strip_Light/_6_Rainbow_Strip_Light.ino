/* PololuLedStrip Library Copyright (c) 2012 Pololu Corporation.
For more information, see http://www.pololu.com/ ; http://forum.
pololu.com/
Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation files
(the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge,
publish, distribute, sublicense, and/or sell copies of the Software,
and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:
The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON
INFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
LedStripRainbow: Example Arduino sketch that shows how to make a
moving rainbow pattern on an Addressable RGB LED Strip from Pololu.
To use this, you will need to plug an Addressable RGB LED strip from
Pololu into pin 12. After uploading the sketch, you should see a
moving rainbow. */
#include <PololuLedStrip.h>
// Create an ledStrip object and specify the pin it will use.
PololuLedStrip<12> ledStrip;
// Create a buffer for holding the colors (3 bytes per color).
#define LED_COUNT 32
rgb_color colors[LED_COUNT];
void setup() {
}
// Converts a color from HSV to RGB.
// h is hue, as a number between 0 and 360.
// s is saturation, as a number between 0 and 255.
// v is value, as a number between 0 and 255.
rgb_color hsvToRgb(uint16_t h, uint8_t s, uint8_t v) {
  uint8_t f = (h % 60) * 255 / 60;
  uint8_t p = (255 - s) * (uint16_t)v / 255;
  uint8_t q = (255 - f * (uint16_t)s / 255) * (uint16_t)v / 255;
  uint8_t t = (255 - (255 - f) * (uint16_t)s / 255) * (uint16_t)v / 255;
  uint8_t r = 0, g = 0, b = 0;
  switch ((h / 60) % 6) {
    case 0: r = v; g = t; b = p; break;
    case 1: r = q; g = v; b = p; break;
    case 2: r = p; g = v; b = t; break;
    case 3: r = p; g = q; b = v; break;
    case 4: r = t; g = p; b = v; break;
    case 5: r = v; g = p; b = q; break;
  }
  return (rgb_color) {
    r, g, b
  };
}
void loop() {
  // Update the colors.
  uint16_t time = millis() >> 2;
  for (uint16_t i = 0; i < LED_COUNT; i++) {
    byte x = (time >> 2) - (i << 3);
    colors[i] = hsvToRgb((uint32_t)x * 359 / 256, 255, 255);
  }
  // Write the colors to the LED strip.
  ledStrip.write(colors, LED_COUNT);
  delay(10);
}
