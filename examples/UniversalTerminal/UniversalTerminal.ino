
#include <Arduino.h>
#include <U8g2lib.h>
#include <Universal_terminal.h>

#include <Wire.h>
#define SDA_PIN 5
#define SCL_PIN 6
U8G2_SSD1306_72X40_ER_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);   // EastRising 0.42" OLED

/*
#define LCD_HEIGHT                  (72)
#define LCD_WIDTH                   (40)
#define LCD_PRINT_LINE_HEIGHT       (8)
#define LCD_PRINT_LINE_WIDTH        (8)*/
Universal_terminal ut;

void setup(void) {
  Wire.begin(SDA_PIN, SCL_PIN);
  u8g2.begin();
  u8g2.setFont(u8g2_font_ncenB08_tr);
  ut.begin(drawChar);
}

void drawChar(const char str, unsigned char x, unsigned char y) {
  char aStr[] = {str, '\0'};
  u8g2.drawStr(x, y, aStr);
}

void loop(void) {
  u8g2.clearBuffer();
  ut.print("Testing...");
  u8g2.sendBuffer();
  delay(1000);
}
