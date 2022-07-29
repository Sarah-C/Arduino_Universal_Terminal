
// Demo using oneBitDisplay and the ESP32-C3 0.42"OLED by 01Space.
// https://github.com/01Space/ESP32-C3-0.42LCD
// https://github.com/bitbank2/OneBitDisplay

#include <OneBitDisplay.h>
#include "Universal_terminal.h"

#define USE_BACKBUFFER
#define SDA_PIN 5
#define SCL_PIN 6
#define RESET_PIN -1
#define OLED_ADDR -1
#define FLIP180 0
#define INVERT 0
#define USE_HW_I2C 1

#define MY_OLED OLED_72x40
#define OLED_WIDTH 72
#define OLED_HEIGHT 40

OBDISP obd;
Universal_terminal ut;

void setup() {
  int rc;
  ut.begin(callbackPrint, callbackClearDisplay, 11, 5);
  // obdI2CInit(OBDISP *, type, oled_addr, rotate180, invert, bWire, SDA_PIN, SCL_PIN, RESET_PIN, speed) 
  rc = obdI2CInit(&obd, MY_OLED, OLED_ADDR, FLIP180, INVERT, USE_HW_I2C, SDA_PIN, SCL_PIN, RESET_PIN, 800000L); // use standard I2C bus at 400Khz
  if (rc != OLED_NOT_FOUND) {
    char *msgs[] = {(char *)"SSD1306,3C", (char *)"SSD1306,3D",(char *)"SH1106,3C",(char *)"SH1106,3D"};
    obdFill(&obd, 0, 1);
    obdSetContrast(&obd, 1);
    obdWriteString(&obd, 0, 0, 0, msgs[rc], FONT_6x8, 0, 1);
    //obdSetBackBuffer(&obd, ucBackBuffer);
    delay(2000);
    obdFill(&obd, 0x0, 1);
  }
}

void callbackClearDisplay(void){
  // This is only needed if the display system doesn't clear a text character when a [space] is printed.
  // If a space does clear out the character beneath, any short rows are filled with spaces, reducing
  // flicker of the whole display by avoiding a full screen clear down.
  obdFill(&obd, 0x0, 1);
}

void callbackPrint(const char character, uint16_t columnPixels, uint16_t rowPixels){
  columnPixels *= 6;
  rowPixels = (rowPixels * 7) + 7;
  char str[] = {character, '\0'};
  //obdWriteString(OBDISP *pOBD, int iScroll, int x, int y, char *szMsg, int iSize, int bInvert, int bRender)
  obdWriteString(&obd, 0, columnPixels, rowPixels, (char *)str, FONT_6x8, 0, 1);
}

char c = 32;

void loop() {
  ut.print(++c);
  if(c == 127) c = 32;
  delay(50);
}
