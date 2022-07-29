#include "Arduino.h"

#include "Universal_terminal.h"
#include "stdio.h"
#include "string.h"
#include <stdlib.h>
#include <cstdarg>

namespace {
    Callback_Print callbackPrint;
    Callback_ClearDisplay callbackClearDisplay;
    char *displayBuffer = nullptr;
    uint16_t cursorColumn = 0;
    uint16_t cursorRow = 0;
    uint16_t displayColumns = 0;
    uint16_t displayRows = 0;
    uint16_t displayBufferSize = 0;
}

// For debugging. 
void Universal_terminal::serialDisplayBuffer(void){
    Serial.println("Buffer content:");
    for(uint16_t row = 0; row < displayRows; row++){
        for(uint16_t column = 0; column < displayColumns; column++){
            Serial.print(displayBuffer[column + (row * displayColumns)]);
        }
        Serial.println("");
    }
}

void Universal_terminal::begin(Callback_Print cp, Callback_ClearDisplay cd, uint16_t columns, uint16_t rows) {
    Serial.println("Begining UT.");
    displayColumns = columns;
    displayRows = rows;
    displayBufferSize = (displayColumns) * displayRows;
    displayBuffer = new char[displayBufferSize]; 
    std::fill(displayBuffer, displayBuffer + displayBufferSize, 33);
    callbackPrint = cp;
    callbackClearDisplay = cd;
    Serial.println((String) "Buffer size " + displayBufferSize + " bytes.");
    serialDisplayBuffer();
}

void Universal_terminal::displayRow(uint16_t row) {
    uint16_t startOfRowIndex = row * displayColumns;
    for(uint16_t column = 0; column < displayColumns; column++){
        char character = displayBuffer[startOfRowIndex + column];
        callbackPrint(character, column, row);
    }
}

void Universal_terminal::print(const char* str) {
    print(str, strlen(str));
}

void Universal_terminal::scrollUp(void) {
    //Serial.println("Before");
    //serialDisplayBuffer();
    memcpy(displayBuffer, displayBuffer + displayColumns, displayBufferSize - displayColumns);
    memset(displayBuffer + displayBufferSize - displayColumns, 32, displayColumns);
    //Serial.println("After");
    //serialDisplayBuffer();
    callbackClearDisplay();
    for(uint8_t row = 0; row < displayRows; row++){
        displayRow(row);
    }
}

void Universal_terminal::scroll(void) {
    if(cursorRow + 1 == displayRows){
        scrollUp();                
    }else{
        cursorRow++;
    }
}

void Universal_terminal::moveToNextColumn(void) {
    cursorColumn++;
    if(cursorColumn == displayColumns){
        cursorColumn = 0;
        scroll();
    }
}


void Universal_terminal::print(const char* str, uint32_t stringLength) {
    for(uint16_t index = 0; index < stringLength; index++){
        unsigned char character = str[index];
        switch (character) {
            case '\t':
            case '\v':
                continue;
            case '\r':
                cursorColumn = 0;
                break;
            case '\n':
                scroll();
                break;
            default:
                displayBuffer[cursorColumn + (cursorRow * displayColumns)] = character;
                callbackPrint(str[index], cursorColumn, cursorRow);
                moveToNextColumn();
                break;
        } // End switch (character)
    } // End for index
} // End print

//##################################################################

void Universal_terminal::print(double value, uint8_t precison) {
    char fmt[10];
    char buf[33];
    sprintf(fmt, "%%.%uf", precison);
    sprintf(buf, fmt, value);
    print(buf);
}
void Universal_terminal::print(char value) {
    char buf[] = { value, '\0' };
    print(buf);
}
void Universal_terminal::println(double value, uint8_t precison) {
    print(value, precison);
    print("\n");
}
void Universal_terminal::println(char value) {
    char buf[] = { value, '\n', '\0' };
    print(buf);
}
void Universal_terminal::println(const char* str) {
    print(str);
    print("\n");
}
void Universal_terminal::println(const char* str, uint32_t length) {
    print(str, length);
    print("\n");
}
void Universal_terminal::printf(const char* fmt, ...) {
    char buf[128];
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, sizeof(buf), fmt, ap);
    print(buf);
    va_end(ap);
}
//##################################################################








