// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library

#include <Adafruit_NeoPixel.h>

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN 6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 1

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


void setup() {
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
}

void loop() {

  int rVal = 0;
  int gVal = 0;
  int bVal = 0;
  while (rVal < 255) {
    rVal++;
    pixels.setPixelColor(0, pixels.Color(gVal, rVal, bVal));
    pixels.show();
    delay(5);
  }
  while (gVal < 255) {
    gVal++;
    pixels.setPixelColor(0, pixels.Color(gVal, rVal, bVal));
    pixels.show();
    delay(5);
  }
    while (bVal < 255) {
    bVal++;
    pixels.setPixelColor(0, pixels.Color(gVal, rVal, bVal));
    pixels.show();
    delay(5);
  }

  rVal = 0;
  gVal = 0;
  bVal = 0;
    while (bVal < 255) {
    bVal++;
    pixels.setPixelColor(0, pixels.Color(gVal, rVal, bVal));
    pixels.show();
    delay(5);
  }
  while (rVal < 255) {
    rVal++;
    pixels.setPixelColor(0, pixels.Color(gVal, rVal, bVal));
    pixels.show();
    delay(5);
  }
    while (gVal < 255) {
    gVal++;
    pixels.setPixelColor(0, pixels.Color(gVal, rVal, bVal));
    pixels.show();
    delay(5);
  }

  rVal = 0;
  gVal = 0;
  bVal = 0;
    while (gVal < 255) {
    gVal++;
    pixels.setPixelColor(0, pixels.Color(gVal, rVal, bVal));
    pixels.show();
    delay(5);
  }
  while (bVal < 255) {
    bVal++;
    pixels.setPixelColor(0, pixels.Color(gVal, rVal, bVal));
    pixels.show();
    delay(5);
  }
    while (rVal < 255) {
    rVal++;
    pixels.setPixelColor(0, pixels.Color(gVal, rVal, bVal));
    pixels.show();
    delay(5);
  }
}
