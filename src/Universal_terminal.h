#pragma once
#include <stdint.h>
#include"itoa_plus.h"
#define gen_print(type,...)                     \
    void print(type value, uint8_t base = 10){  \
        char buf[65];                           \
        itoa_plus(buf, value, type(base));      \
        print(buf);                             \
    }

#define gen_println(type,...)                   \
    void println(type value, uint8_t base = 10){\
        char buf[65];                           \
        itoa_plus(buf, value, type(base));      \
        println(buf);                           \
    }

typedef void (*Callback_Print)(const char str, uint16_t, uint16_t); 
typedef void (*Callback_ClearDisplay)(void); 

class Universal_terminal {
  public:
    void begin(Callback_Print, Callback_ClearDisplay, uint16_t columns, uint16_t rows);
    void serialDisplayBuffer(void);
    void displayRow(uint16_t row);
    void scrollUp(void);
    void scroll(void);
    void moveToNextColumn(void);
    void clearRowBuffer(uint16_t row);
    void clearRow(uint16_t row);
    void setCursorRow(uint16_t row);
    void setCursorColumn(uint16_t column);
    void setCursor(uint16_t row, uint16_t column);
    gen_print(uint8_t);
    gen_print(uint16_t);
    gen_print(uint32_t);
    gen_print(uint64_t);
    gen_print(int8_t);
    gen_print(int16_t);
    gen_print(int32_t);
    gen_print(int64_t);
    void print(char value);
    void print(const char* str);
    void print(const char* str, uint32_t length);
    void print(double value, uint8_t precison = 2);
    gen_println(uint8_t);
    gen_println(uint16_t);
    gen_println(uint32_t);
    gen_println(uint64_t);
    gen_println(int8_t);
    gen_println(int16_t);
    gen_println(int32_t);
    gen_println(int64_t);
    void println(char value);
    void println(double value, uint8_t precison = 2);
    void println(const char* str);
    void println(const char* str, uint32_t length);
    void printf(const char* fmt, ...);
};

#undef gen_print
#undef gen_println
