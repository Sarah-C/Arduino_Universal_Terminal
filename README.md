# Arduino_Universal_Terminal [Work in progress! Don't use yet]        
This library provides a printing function similar to that of the Linux terminal, Windows console, DOS mode, for any Arduino display.             
Based heavily on https://github.com/Seeed-Studio/Seeed_Arduino_Terminal              

If you just want to Print, Print, Print status updates to the display like a log on any display, THIS library is for you!

Using a callback for the display of characters, any display can be used with this library, not just TFT_eSPI.         

The callback funtion you write is passed the (x, y, text) to be sent to the display, your own code calls your relevant display libraries own function.          
All the ones I've seen have a drawString(x, y, character) type function, so it should be easy.          

That's it! 

Work remaining:          
-Add the callback!       
-Write some callback functions for several graphics libraries.                   
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
