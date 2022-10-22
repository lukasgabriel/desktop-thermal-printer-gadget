// All Tests


// SHARP DISPLAY SETUP
#include <Adafruit_GFX.h>
#include <Adafruit_SharpMem.h>

#define SHARP_SCK 10
#define SHARP_MOSI 12
#define SHARP_SS 11

Adafruit_SharpMem display(SHARP_SCK, SHARP_MOSI, SHARP_SS, 400, 240);

#define BLACK 0
#define WHITE 1
#define MAX_LINE_LENGTH 32

int minorHalfSize;

void SharpInit() {
  Serial.println("Initializing SHARP display...");
  display.begin();
  display.clearDisplay();

  minorHalfSize = min(display.width(), display.height()) / 2;

  display.setRotation(0);
  display.clearDisplay();

  //display.setTextWrap(false);
  display.setTextSize(2);
  display.setTextColor(BLACK);
  display.setCursor(5, 5);
  display.println("Hello, world!");

  display.refresh();
}

void printBoth(char* val) {
  display.clearDisplay();
  display.setCursor(5, 5);
  Serial.println(val);
  display.println(val);
  display.refresh();
}
// ----------


// BUTTON TEST
#define switchL 3
#define switchM 0
#define switchR 1

void ButtonTest() {
  bool lWorks = false;
  bool mWorks = false;
  bool rWorks = false;

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(switchL, INPUT);
  pinMode(switchM, INPUT);
  pinMode(switchR, INPUT);

  digitalWrite(LED_BUILTIN, HIGH);

  printBoth("Running Button Test to test Interface Button Functionality...");
  printBoth("Please press all 3 Buttons to proceed. Tests will continue once all buttons have been pressed.");

  while (!(lWorks && mWorks && rWorks)) {
    if ((digitalRead(switchL) == HIGH) && !lWorks) {
      printBoth("Button L Pressed");
      lWorks = true;
    }
    if ((digitalRead(switchM) == HIGH) && !mWorks) {
      printBoth("Button M Pressed");
      mWorks = true;
    }
    if ((digitalRead(switchR) == HIGH) && !rWorks) {
      printBoth("Button R Pressed");
      rWorks = true;
    }
  }
  digitalWrite(LED_BUILTIN, LOW);
  printBoth("All Button Presses were registered! Continuing...");
}
// ---------


// LED TEST
#include <Adafruit_NeoPixel.h>
#define ledPIN 6
#define NUMPIXELS 1
Adafruit_NeoPixel pixels(NUMPIXELS, ledPIN, NEO_GRB + NEO_KHZ800);

void LEDTest() {
  printBoth("Running LED Test to test Indicator LED Functionality.");

  printBoth("First Loop: RED -> GREEN -> BLUE");

  int rVal = 0;
  int gVal = 0;
  int bVal = 0;
  printBoth("Increasing RED Value...");
  while (rVal < 255) {
    rVal++;
    pixels.setPixelColor(0, pixels.Color(gVal, rVal, bVal));
    pixels.show();
    delay(5);
  }
  printBoth("Increasing GREEN Value...");
  while (gVal < 255) {
    gVal++;
    pixels.setPixelColor(0, pixels.Color(gVal, rVal, bVal));
    pixels.show();
    delay(5);
  }
  printBoth("Increasing BLUE Value...");
  while (bVal < 255) {
    bVal++;
    pixels.setPixelColor(0, pixels.Color(gVal, rVal, bVal));
    pixels.show();
    delay(5);
  }

  printBoth("Second Loop: BLUE -> RED -> GREEN");

  rVal = 0;
  gVal = 0;
  bVal = 0;
  printBoth("Increasing BLUE Value...");
  while (bVal < 255) {
    bVal++;
    pixels.setPixelColor(0, pixels.Color(gVal, rVal, bVal));
    pixels.show();
    delay(5);
  }
  printBoth("Increasing RED Value...");
  while (rVal < 255) {
    rVal++;
    pixels.setPixelColor(0, pixels.Color(gVal, rVal, bVal));
    pixels.show();
    delay(5);
  }
  printBoth("Increasing GREEN Value...");
  while (gVal < 255) {
    gVal++;
    pixels.setPixelColor(0, pixels.Color(gVal, rVal, bVal));
    pixels.show();
    delay(5);
  }

  printBoth("Third Loop: GREEN -> BLUE -> RED");

  rVal = 0;
  gVal = 0;
  bVal = 0;
  printBoth("Increasing GREEN Value...");
  while (gVal < 255) {
    gVal++;
    pixels.setPixelColor(0, pixels.Color(gVal, rVal, bVal));
    pixels.show();
    delay(5);
  }
  printBoth("Increasing BLUE Value...");
  while (bVal < 255) {
    bVal++;
    pixels.setPixelColor(0, pixels.Color(gVal, rVal, bVal));
    pixels.show();
    delay(5);
  }
  printBoth("Increasing RED Value...");
  while (rVal < 255) {
    rVal++;
    pixels.setPixelColor(0, pixels.Color(gVal, rVal, bVal));
    pixels.show();
    delay(5);
  }

  pixels.clear();
  pixels.show();
  printBoth("LED Test finished. Continuing...");
}
// ---------


// PIEZO TEST
#include <ezBuzzer.h>
const int BUZZER_PIN = 2;
int noteLength;
ezBuzzer buzzer(BUZZER_PIN);
int melody[] = {
  NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_G5, NOTE_C5, NOTE_D5,
  NOTE_E5,
  NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5,
  NOTE_F5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_D5, NOTE_D5, NOTE_E5,
  NOTE_D5, NOTE_G5
};
int noteDurations[] = {
  8, 8, 4,
  8, 8, 4,
  8, 8, 8, 8,
  2,
  8, 8, 8, 8,
  8, 8, 8, 16, 16,
  8, 8, 8, 8,
  4, 4
};
void PiezoTest() {
  printBoth("Running Piezo Test to test Piezo Buzzer functionality.");
  printBoth("Buzzer should play a melody...");

  noteLength = sizeof(noteDurations) / sizeof(int);
  int i = 2;
  while (i > 0) {
    buzzer.loop();
    if (buzzer.getState() == BUZZER_IDLE) {
      buzzer.playMelody(melody, noteDurations, noteLength);
      i--;
    }
  }
  buzzer.stop();

  printBoth("Piezo Test finished. Continuing...");
}
// ---------


// NOKIA DISPLAY TEST
#include <SPI.h>
#include "LCD_Functions.h"
char xkcdSandwich[] = {
  0xFF,
  0x8D,
  0x9F,
  0x13,
  0x13,
  0xF3,
  0x01,
  0x01,
  0xF9,
  0xF9,
  0x01,
  0x81,
  0xF9,
  0xF9,
  0x01,
  0xF1,
  0xF9,
  0x09,
  0x09,
  0xFF,
  0xFF,
  0xF1,
  0xF9,
  0x09,
  0x09,
  0xF9,
  0xF1,
  0x01,
  0x01,
  0x01,
  0x01,
  0x01,
  0xF9,
  0xF9,
  0x09,
  0xF9,
  0x09,
  0xF9,
  0xF1,
  0x01,
  0xC1,
  0xE9,
  0x29,
  0x29,
  0xF9,
  0xF1,
  0x01,
  0xFF,
  0xFF,
  0x71,
  0xD9,
  0x01,
  0x01,
  0xF1,
  0xF9,
  0x29,
  0x29,
  0xB9,
  0xB1,
  0x01,
  0x01,
  0x01,
  0xF1,
  0xF1,
  0x11,
  0xF1,
  0xF1,
  0xF1,
  0xE1,
  0x01,
  0xE1,
  0xF1,
  0x51,
  0x51,
  0x71,
  0x61,
  0x01,
  0x01,
  0xC1,
  0xF1,
  0x31,
  0x31,
  0xF1,
  0xFF,
  0xFF,
  0x00,
  0x01,
  0x01,
  0x01,
  0x01,
  0x60,
  0xE0,
  0xA0,
  0x01,
  0x01,
  0x81,
  0xE1,
  0x61,
  0x60,
  0xC0,
  0x01,
  0xE1,
  0xE1,
  0x21,
  0x21,
  0xE0,
  0xC1,
  0x01,
  0xC1,
  0xE1,
  0x20,
  0x20,
  0xFC,
  0xFC,
  0xE0,
  0xE0,
  0xC1,
  0xE1,
  0xE0,
  0xC1,
  0xE0,
  0xE1,
  0x01,
  0xFC,
  0xFC,
  0x21,
  0x21,
  0xE1,
  0xC1,
  0xE5,
  0xE4,
  0x01,
  0xC1,
  0xE0,
  0x20,
  0x21,
  0x20,
  0x00,
  0x01,
  0xFD,
  0xFD,
  0x21,
  0x20,
  0xE0,
  0x00,
  0x00,
  0x01,
  0x01,
  0xC0,
  0x61,
  0x31,
  0x31,
  0x21,
  0x20,
  0xC0,
  0x81,
  0x01,
  0x01,
  0x01,
  0x00,
  0x00,
  0x00,
  0x00,
  0x01,
  0x01,
  0x01,
  0x01,
  0xFF,
  0xFF,
  0x00,
  0x00,
  0x00,
  0x00,
  0x01,
  0x03,
  0x02,
  0x03,
  0x01,
  0x00,
  0x01,
  0x03,
  0xF2,
  0x1A,
  0x0B,
  0x08,
  0x0B,
  0x1B,
  0x10,
  0x60,
  0xE3,
  0x03,
  0x00,
  0x01,
  0x03,
  0x02,
  0x02,
  0x03,
  0x03,
  0x00,
  0x03,
  0x03,
  0x00,
  0x00,
  0x03,
  0x03,
  0x00,
  0x00,
  0x03,
  0x03,
  0x00,
  0x00,
  0x03,
  0x03,
  0x03,
  0x03,
  0x00,
  0x01,
  0x03,
  0x02,
  0x02,
  0x03,
  0x01,
  0x00,
  0x03,
  0x03,
  0x00,
  0x00,
  0x03,
  0x00,
  0x00,
  0x00,
  0x3E,
  0x63,
  0x80,
  0x80,
  0x80,
  0x80,
  0x60,
  0x3F,
  0x07,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0xFF,
  0xFF,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0xFE,
  0x01,
  0x01,
  0x01,
  0x02,
  0x03,
  0x3E,
  0xE8,
  0xF8,
  0xF0,
  0xD0,
  0x90,
  0x18,
  0x0F,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0xC0,
  0x38,
  0xFF,
  0x0C,
  0x38,
  0xE0,
  0x80,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0xFF,
  0xFF,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x1F,
  0xF0,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x33,
  0x5F,
  0x8F,
  0x84,
  0x05,
  0x07,
  0x06,
  0x0C,
  0x0E,
  0x0E,
  0x0C,
  0x14,
  0x34,
  0x68,
  0x88,
  0xD8,
  0x70,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0xE0,
  0x10,
  0x10,
  0x10,
  0xF0,
  0xE0,
  0x00,
  0xF0,
  0xF0,
  0x00,
  0x80,
  0x80,
  0x00,
  0x00,
  0x80,
  0x80,
  0x80,
  0x80,
  0x00,
  0x80,
  0x80,
  0x00,
  0x80,
  0x00,
  0x00,
  0x20,
  0x38,
  0x0E,
  0x01,
  0xC0,
  0x3F,
  0xE0,
  0x00,
  0x00,
  0x03,
  0x0E,
  0x08,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0xFF,
  0xFF,
  0x80,
  0x80,
  0x80,
  0x80,
  0x80,
  0x80,
  0x80,
  0xB6,
  0xED,
  0xC0,
  0xC0,
  0xC0,
  0xE0,
  0xA0,
  0xA0,
  0xA0,
  0xA0,
  0xA1,
  0xA1,
  0xA1,
  0xA1,
  0xA1,
  0xA1,
  0xA1,
  0xE1,
  0xE1,
  0xC1,
  0xEF,
  0xBB,
  0x83,
  0x86,
  0x88,
  0xB0,
  0x80,
  0x80,
  0x80,
  0x8F,
  0x90,
  0x90,
  0x90,
  0x9F,
  0x8F,
  0x80,
  0x9F,
  0x9F,
  0x87,
  0x8D,
  0x98,
  0x80,
  0x8C,
  0x9E,
  0x92,
  0x92,
  0x9F,
  0xC0,
  0xC7,
  0xFF,
  0xB8,
  0x8F,
  0x80,
  0x90,
  0x90,
  0xC0,
  0xF0,
  0x8E,
  0x81,
  0x80,
  0x81,
  0x8F,
  0xB8,
  0xE0,
  0x80,
  0x80,
  0x80,
  0x80,
  0x80,
  0x80,
  0x80,
  0x80,
  0x80,
  0x80,
  0x80,
  0xFF,
};
char sparkfunLogo[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // (0,0)->(11,7) ~ These 12 bytes cover an 8x12 block in the left corner of the display
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // (12,0)->(23,7)
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0,  // (24,0)->(35,7)
  0xF0, 0xF8, 0xFC, 0xFC, 0xFE, 0xFE, 0xFE, 0xFE, 0x1E, 0x0E, 0x02, 0x00,  // (36,0)->(47,7)
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // (48,0)->(59,7)
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // (60,0)->(71,7)
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // (72,0)->(83,7)
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // (0,8)->(11,15)
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // (12,8)->(23,15)
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03,  // (24,8)->(35,15)
  0x0F, 0x1F, 0x3F, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFC, 0xF8,  // (36,8)->(47,15)
  0xF8, 0xF0, 0xF8, 0xFE, 0xFE, 0xFC, 0xF8, 0xE0, 0x00, 0x00, 0x00, 0x00,  // (48,8)->(59,15)
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // (60,8)->(71,15)
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // (72,8)->(83,15)
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // (0,16)->(11,23)
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // (12,16)->(23,23)
  0x00, 0x00, 0xF8, 0xFC, 0xFE, 0xFE, 0xFF, 0xFF, 0xF3, 0xE0, 0xE0, 0xC0,  // (24,16)->(35,23)
  0xC0, 0xC0, 0xE0, 0xE0, 0xF1, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  // (36,16)->(47,23)
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x3E, 0x00, 0x00, 0x00,  // (48,16)->(59,23)
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // (60,16)->(71,23)
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // (72,16)->(83,23)
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // (0,24)->(11,31)
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // (12,24)->(23,31)
  0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  // (24,24)->(35,31)
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,  // (36,24)->(47,31)
  0xFF, 0xFF, 0xFF, 0x7F, 0x3F, 0x1F, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00,  // (48,24)->(59,31)
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // (60,24)->(71,31)
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // (72,24)->(83,31)
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // (0,32)->(11,39)
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // (12,32)->(23,39)
  0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x3F, 0x1F,  // (24,32)->(35,39)
  0x0F, 0x0F, 0x0F, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x03, 0x03,  // (36,32)->(47,39)
  0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // (48,32)->(59,39)
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // (60,32)->(71,39)
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // (72,32)->(83,39)
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // (0,40)->(11,47)
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // (12,40)->(23,47)
  0x00, 0x00, 0x3F, 0x1F, 0x0F, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00,  // (24,40)->(35,47)
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // (36,40)->(47,47)
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // (48,40)->(59,47)
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // (60,40)->(71,47)
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  // (72,40)->(83,47) !!! The bottom right pixel!
};
void NokiaTest() {
  printBoth("Running LCD Test to test LCD Display Functionality.");

  printBoth("Initializing Display on SPI0 (Testbench right)...");
  lcdBegin(0);
  delay(500);

  printBoth("Displaying Image on D0...");
  setBitmap(sparkfunLogo);
  updateDisplay(0);
  delay(500);

  printBoth("Setting D0 Contrast to 20...");
  setContrast(20, 0);
  delay(500);

  printBoth("Setting D0 Contrast to 40...");
  setContrast(20, 0);
  delay(500);

  printBoth("Setting D0 Contrast to 60...");
  setContrast(20, 0);
  delay(500);

  printBoth("Displaying Text on D0...");
  setStr("The quick brown fox jumped over the lazy dog. 0123456789!@#$%^&*()_+", 0, 0, true);
  updateDisplay(0);
  delay(500);

  printBoth("Dimming backlight on D0...");
  for (int i = 255; i >= 0; i -= 5) {
    analogWrite(blPin0, i);
    delay(20);
  }


  printBoth("Initializing Display on SPI1 (Testbench left)...");
  lcdBegin(1);
  delay(500);

  printBoth("Displaying Image on D1...");
  setBitmap(sparkfunLogo);
  updateDisplay(1);
  delay(500);

  printBoth("Setting D1 Contrast to 20...");
  setContrast(20, 1);
  delay(500);

  printBoth("Setting D1 Contrast to 40...");
  setContrast(20, 1);
  delay(500);

  printBoth("Setting D1 Contrast to 60...");
  setContrast(20, 1);
  delay(500);

  printBoth("Displaying Text on D1...");
  setStr("The quick brown fox jumped over the lazy dog. 0123456789!@#$%^&*()_+", 0, 0, true);
  updateDisplay(1);
  delay(500);

  printBoth("Dimming backlight on D1...");
  for (int i = 255; i >= 0; i -= 5) {
    analogWrite(blPin1, i);
    delay(20);
  }


  printBoth("LCD Test finished. Continuing...");
}
// ----------


// THERMAL PRINTER TEST
#include "Adafruit_Thermal.h"
#include "tests/test_lena.h"
#include "tests/adaqrcode.h"
#include "SoftwareSerial.h"
#define TX_PIN 8
#define RX_PIN 9
#define CTS_PIN 7
SoftwareSerial mySerial(RX_PIN, TX_PIN);
Adafruit_Thermal printer(&mySerial, CTS_PIN);
void PrinterTest() {
  printBoth("Running Printer Test to test Thermal Printer Functionality.");
  printBoth("Initializing Printer on UART1...");

  mySerial.begin(9600);
  printer.begin();

  // Font options
  printer.setFont('B');
  printBoth("Printing Text B ...");
  printer.println("FontB");
  printer.println("ABCDEFGHIJKLMNOPQRSTUVWXYZ");

  printer.setFont('A');
  printBoth("Printing Text A ...");
  printer.println("FontA (default)");
  printer.println("ABCDEFGHIJKLMNOPQRSTUVWXYZ");

  // Test inverse on & off
  printer.inverseOn();
  printBoth("Printing INVERSE Text ...");
  printer.println(F("Inverse ON"));
  printer.inverseOff();

  // Test character double-height on & off
  printer.doubleHeightOn();
  printBoth("Printing DOUBLE Height Text ...");
  printer.println(F("Double Height ON"));
  printer.doubleHeightOff();

  // Set text justification (right, center, left) -- accepts 'L', 'C', 'R'
  printer.justify('R');
  printBoth("Printing RIGHT justified Text ...");
  printer.println(F("Right justified"));
  printer.justify('C');
  printBoth("Printing CENTER justified Text ...");
  printer.println(F("Center justified"));
  printer.justify('L');
  printBoth("Printing LEFT justified Text ...");
  printer.println(F("Left justified"));

  // Test more styles
  printer.boldOn();
  printBoth("Printing BOLD Text ...");
  printer.println(F("Bold text"));
  printer.boldOff();

  printer.underlineOn();
  printBoth("Printing UNDERLINED Text ...");
  printer.println(F("Underlined text"));
  printer.underlineOff();

  printer.setSize('L');  // Set type size, accepts 'S', 'M', 'L'
  printBoth("Printing LARGE Text ...");
  printer.println(F("Large"));
  printer.setSize('M');
  printBoth("Printing MEDIUM Text ...");
  printer.println(F("Medium"));
  printer.setSize('S');
  printBoth("Printing SMALL Text ...");
  printer.println(F("Small"));

  printer.justify('C');
  printBoth("Printing NORMALSPACE Text ...");
  printer.println(F("normal\nline\nspacing"));
  printer.setLineHeight(50);
  printBoth("Printing TALLSPACE Text ...");
  printer.println(F("Taller\nline\nspacing"));
  printer.setLineHeight();  // Reset to default
  printer.justify('L');

  // Barcode examples:
  // CODE39 is the most common alphanumeric barcode:
  printBoth("Printing CODE39 Barcode ...");
  printer.printBarcode("ADAFRUT", CODE39);
  printer.setBarcodeHeight(100);
  // Print UPC line on product barcodes:
  printBoth("Printing UPC_A Barcode ...");
  printer.printBarcode("123456789123", UPC_A);

  // Print the 75x75 pixel logo in adalogo.h:
  printBoth("Printing Test BITMAP ...");
  printer.printBitmap(512, 512, lena_gray);

  // Print the 135x135 pixel QR code in adaqrcode.h:
  printBoth("Printing QR Code ...");
  printer.printBitmap(adaqrcode_width, adaqrcode_height, adaqrcode_data);

  printBoth("Printer Tests DONE!");
  printer.println(F("DONE!  :)"));

  printBoth("Feeding 6 LINES ...");
  printer.feed(6);

  printer.sleep();       // Tell printer to sleep
  delay(3000L);          // Sleep for 3 seconds
  printer.wake();        // MUST wake() before printing again, even if reset
  printer.setDefault();  // Restore printer to defaults

  printBoth("Printer Test finished. Continuing...");
}
// ----------


// WiFi & MQTT TEST

// ----------


void setup() {
  Serial.begin(9600);
  Serial.println("Hello World!");
  pixels.begin();
  SharpInit();
}

void loop() {
  printBoth("Beginning Test Suite of all components.");

  ButtonTest();
  delay(1000);

  LEDTest();
  delay(1000);

  PiezoTest();
  delay(1000);

  NokiaTest();
  delay(1000);

  PrinterTest();
  delay(1000);

  printBoth("Test Suite finished. Restarting in 5 Seconds. Builtin LED will light up when the first test is ready.");
  delay(5000);
}