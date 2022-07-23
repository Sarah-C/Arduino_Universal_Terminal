#include "universal_terminal.h"
#include "stdio.h"
#include "string.h"

#define LCD_HEIGHT                  (240)
#define LCD_WIDTH                   (320)
#define LCD_PRINT_LINE_HEIGHT       (12)
#define LCD_PRINT_LINE_WIDTH        (8)
#define LCD_PRINT_ROW_COUNT         (LCD_HEIGHT / LCD_PRINT_LINE_HEIGHT)
#define LCD_PRINT_COLUMN_COUNT      (LCD_WIDTH / LCD_PRINT_LINE_WIDTH)

namespace {
    bool       is_full_row;
    bool       auto_flush = true;
    char       buffer[LCD_PRINT_ROW_COUNT * (1 + LCD_PRINT_COLUMN_COUNT)];
    uint8_t    column_count[LCD_PRINT_ROW_COUNT];
    uint16_t   lcd_print_row_count;
    uint16_t   lcd_print_column_count;
    uint16_t   current_row;
    uint16_t   current_column;
    uint16_t   fore = TFT_GREEN;
    uint16_t   back = TFT_BLACK;
    TFT_eSPI   tft;
    static char* get_row(uint32_t index) {
        return buffer + (index * lcd_print_column_count);
    }
    static char* break_row() {
        current_column = 0;
        current_row++;
        if (current_row == lcd_print_row_count) {
            is_full_row = true;
            current_row = 0;
        }
        auto row = get_row(current_row);
        row[0] = '\0';
        return row;
    }
}
void universal_terminal::begin(void) {
    current_row = 0;
    current_column = 0;   
    lcd_print_row_count = LCD_PRINT_ROW_COUNT;
    lcd_print_column_count = LCD_PRINT_COLUMN_COUNT;
}
void universal_terminal::print(const char* str) {
    print(str, strlen(str));
}
void universal_terminal::print(const char* str, uint32_t length) {
    char* row = current_column == lcd_print_column_count ? break_row() : get_row(current_row);
    for (uint32_t i = 0; str[i] != '\0' && i < length; i++) {
        switch (str[i]) {
            case '\t':
            case '\v':
                continue;
            case '\r':
                if (str[i + 1] == '\n') {
                    i += 1;
                }
            //no break
            case '\n':
                row[current_column] = '\0';
                current_column = lcd_print_column_count;
                break;
            default:
                row[current_column++] = str[i];
                break;
        }
        if (current_column == lcd_print_column_count) {
            if (str[i] != '\n') {
                row[lcd_print_column_count] = '\0';
            }
            if (str[i + 1] != '\0' || str[i] == '\n') {
                row = break_row();
            }
        }
    }
    row[current_column] = '\0';

    if (::auto_flush) {
        flush();
    }
}

void universal_terminal::print(double value, uint8_t precison) {
    char fmt[10];
    char buf[33];
    sprintf(fmt, "%%.%uf", precison);
    sprintf(buf, fmt, value);
    print(buf);
}
void universal_terminal::print(char value) {
    char buf[] = { value, '\0' };
    print(buf);
}
void universal_terminal::println(double value, uint8_t precison) {
    print(value, precison);
    print("\n");
}
void universal_terminal::println(char value) {
    char buf[] = { value, '\n', '\0' };
    print(buf);
}
void universal_terminal::println(const char* str) {
    print(str);
    print("\n");
}
void universal_terminal::println(const char* str, uint32_t length) {
    print(str, length);
    print("\n");
}
void universal_terminal::printf(const char* fmt, ...) {
    char buf[128];
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, sizeof(buf), fmt, ap);
    print(buf);
    va_end(ap);
}
void universal_terminal::auto_flush(bool enable) {
    ::auto_flush = enable;
}
void universal_terminal::flush() {
    uint32_t i = 0;
    uint32_t index = 0;
    uint32_t height = 0;
    uint32_t row_count = current_row + 1;
    if (is_full_row) {
        index = current_row + 1;
        row_count = lcd_print_row_count;
    }
    while (i < row_count) {
        if (index == lcd_print_row_count) {
            index = 0;
        }
        auto start = get_row(index), p = start;
        auto width = 0;
        for (; p[0]; p++, width += LCD_PRINT_LINE_WIDTH) {
            //  CALLBACK!     tft.drawChar(p[0], width, height, 1);
        }
        for (uint32_t ws = p - start; ws < column_count[i]; ws++, width += LCD_PRINT_LINE_WIDTH) {
            // CALLBACK!      tft.drawChar(' ', width, height, 1);
        }
        column_count[i] = p - start;
        height += LCD_PRINT_LINE_HEIGHT;
        index += 1;
        i += 1;
    }
}

