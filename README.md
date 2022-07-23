# Arduino_Universal_Terminal [Work in progress! Don't use yet]        
This library provides a printing function similar to that of the terminal for any Arduino display.             
Based heavily on https://github.com/Seeed-Studio/Seeed_Arduino_Terminal              

Using a callback for the display of characters, any display can be used with this library, not just TFT_eSPI.         

Work remaining:          
-Add the callback!       
-Update this readme with the examples for a few graphics libraries like g8u2, OneBitDisplay, etc...
-Add a flashing cursor?         

Thanks to all the original writers for the original code, saved me hours.
________________                  
Old info:

### Reference
- Based on [Seeed_Arduino_LCD](https://github.com/Seeed-Studio/Seeed_Arduino_LCD)

### Feature
- Print decimal, hex, bin number and string
- Set the screen orientation
- Set background and foreground color

### Get Start
- Download those libraries.
```bash
cd Arduino/libraries
git clone https://github.com/Seeed-Studio/Seeed_Arduino_LCD
git clone https://github.com/Seeed-Studio/Seeed_Arduino_Terminal
```

- Hello world, YES!
```C++
#include<grove_terminal.h>

grove_terminal terminal;
void setup(){
    terminal.begin();
    terminal.println("Hello world!");
}

void loop(){
    
}
```
