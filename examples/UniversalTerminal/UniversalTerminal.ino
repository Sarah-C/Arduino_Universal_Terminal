
//#include "Arduino.h"
#include <Wire.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"
#include "Universal_terminal.h"

// 0X3C+SA0 - 0x3C or 0x3D
#define I2C_ADDRESS 0x3C

SSD1306AsciiWire oled;
Universal_terminal ut;

// Universal Terminal uses these callback functions to update the relevant display.
void callbackClearDisplay(void){
  oled.clear();
}

void callbackPrint(const char character, uint16_t columnPixels, uint16_t rowCharacter){
  columnPixels *= 8;
  oled.setCursor((uint8_t) columnPixels, (uint8_t) rowCharacter);
  oled.write(character);
}

//#####################

void setup() {
  Wire.begin();
  Wire.setClock(400000L);
  Serial.begin(115200);
  ut.begin(callbackPrint, callbackClearDisplay, 16, 8); // 16 characters wide, by 8 high
  oled.begin(&Adafruit128x64, I2C_ADDRESS);
  oled.setFont(font8x8);
  // Complicated demo...
  char buffer[40];
  int freq = 123456;
  float freqkHz = freq / 1000.0;
  sprintf(buffer, "%.2f kHz...", freqkHz);
  ut.print(buffer);
}

void loop() {
  ut.print("123");
  delay(200);
}
