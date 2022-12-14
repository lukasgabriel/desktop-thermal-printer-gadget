/***************************************************
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/

#include "Adafruit_EPD.h"

#define EPD_MISO     16
//#define EDP_MISO     12

#define EPD_MOSI     19
//#define EPD_MOSI     11

#define EPD_SCLK     18
//#define EPD_SCLK      10

#define EPD_CS     17
//#define EPD_CS     13

#define EPD_DC      26
//#define EPD_DC      14

#define SRAM_CS     22
//#define SRAM_CS     15

#define EPD_RESET   21 // can set to -1 and share with microcontroller Reset!
//#define EPD_RESET   20 // can set to -1 and share with microcontroller Reset!

#define EPD_BUSY    -1 // can set to -1 to not use a pin (will wait a fixed delay)

// Uncomment the following line if you are using 1.54" EPD with IL0373
//Adafruit_IL0373 display(152, 152, EPD_DC, EPD_RESET, EPD_CS, SRAM_CS, EPD_BUSY);
// Uncomment the following line if you are using 1.54" EPD with SSD1680
//Adafruit_SSD1680 display(152, 152, EPD_DC, EPD_RESET, EPD_CS, SRAM_CS, EPD_BUSY);
// Uncomment the following line if you are using 1.54" EPD with SSD1608
//Adafruit_SSD1608 display(200, 200, EPD_DC, EPD_RESET, EPD_CS, SRAM_CS, EPD_BUSY);
// Uncomment the following line if you are using 1.54" EPD with SSD1681
//Adafruit_SSD1681 display(200, 200, EPD_DC, EPD_RESET, EPD_CS, SRAM_CS, EPD_BUSY);
// Uncomment the following line if you are using 1.54" EPD with UC8151D
//Adafruit_UC8151D display(152, 152, EPD_DC, EPD_RESET, EPD_CS, SRAM_CS, EPD_BUSY);


//Uncomment the following line if you are using 2.13" EPD with SSD1680
Adafruit_SSD1680 display(250, 122, EPD_MOSI, EPD_SCLK, EPD_DC, EPD_RESET, EPD_CS, SRAM_CS, EPD_MISO, EPD_BUSY);

// Uncomment the following line if you are using 2.13" EPD with SSD1675
//Adafruit_SSD1675 display(250, 122, EPD_DC, EPD_RESET, EPD_CS, SRAM_CS, EPD_BUSY);

// Uncomment the following line if you are using 2.13" EPD with SSD1675B
//Adafruit_SSD1675B display(250, 122, EPD_DC, EPD_RESET, EPD_CS, SRAM_CS, EPD_BUSY);

// Uncomment the following line if you are using 2.13" EPD with UC8151D
//Adafruit_UC8151D display(212, 104, EPD_DC, EPD_RESET, EPD_CS, SRAM_CS, EPD_BUSY);

//Uncomment the following line if you are using 2.13" EPD with IL0373
//Adafruit_IL0373 display(212, 104, EPD_DC, EPD_RESET, EPD_CS, SRAM_CS, EPD_BUSY);
//#define FLEXIBLE_213


//Uncomment the following line if you are using 2.7" EPD with IL91874
//Adafruit_IL91874 display(264, 176, EPD_DC, EPD_RESET, EPD_CS, SRAM_CS);

// Uncomment the following line if you are using 2.7" EPD with EK79686
//Adafruit_EK79686 display(264, 176, EPD_DC, EPD_RESET, EPD_CS, SRAM_CS, EPD_BUSY);


// Uncomment the following line if you are using 2.9" EPD with IL0373
//Adafruit_IL0373 display(296, 128, EPD_DC, EPD_RESET, EPD_CS, SRAM_CS, EPD_BUSY);
//#define FLEXIBLE_290

// Uncomment the following line if you are using 2.9" EPD with SSD1680
//Adafruit_SSD1680 display(296, 128, EPD_DC, EPD_RESET, EPD_CS, SRAM_CS, EPD_BUSY);

// Uncomment the following line if you are using 2.9" EPD with UC8151D
//Adafruit_UC8151D display(296, 128, EPD_DC, EPD_RESET, EPD_CS, SRAM_CS, EPD_BUSY);


#define COLOR1 EPD_BLACK
#define COLOR2 EPD_RED


void setup() {
  Serial.begin(9600);
  //while (!Serial) { delay(10); }
  Serial.println("Adafruit EPD test");
  
  display.begin();

#if defined(FLEXIBLE_213) || defined(FLEXIBLE_290)
  // The flexible displays have different buffers and invert settings!
  display.setBlackBuffer(1, false);
  display.setColorBuffer(1, false);
#endif

  // large block of text
  display.clearBuffer();
  testdrawtext("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur adipiscing ante sed nibh tincidunt feugiat. Maecenas enim massa, fringilla sed malesuada et, malesuada sit amet turpis. Sed porttitor neque ut ante pretium vitae malesuada nunc bibendum. Nullam aliquet ultrices massa eu hendrerit. Ut sed nisi lorem. In vestibulum purus a tortor imperdiet posuere. ", COLOR1);
  display.display();

  delay(5000);

  display.clearBuffer();
  for (int16_t i=0; i<display.width(); i+=4) {
    display.drawLine(0, 0, i, display.height()-1, COLOR1);
  }

  for (int16_t i=0; i<display.height(); i+=4) {
    display.drawLine(display.width()-1, 0, 0, i, COLOR2);  // on grayscale this will be mid-gray
  }
  display.display();
}

void loop() {
  //don't do anything!
}


void testdrawtext(const char *text, uint16_t color) {
  display.setCursor(0, 0);
  display.setTextColor(color);
  display.setTextWrap(true);
  display.print(text);
}
