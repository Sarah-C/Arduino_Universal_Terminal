# Arduino: Universal Terminal        
This library for the Arduino IDE provides a printing function similar to that of the Linux terminal, Windows console, DOS mode, for any Arduino display.             
Based a little on https://github.com/Seeed-Studio/Seeed_Arduino_Terminal for printing datatypes, though the print function is entirely re-written.              

If you just want to Print, Print, Print status updates to the display like a log on any display, THIS library is for you!

Not every OLED/LCD display library and display combination offer support for terminal-like scrolling, and some that do don't offer a large range of printing options such as exapnsive data types along with printf, println.
This library fills this niche! If your display library has a command to print a character at a co-ordinate, you're good to go.

Using a callback for the display of characters, and clearing the screen any display can be used with this library when you write the two relevant functions using your librarys own commands.         

The callback funtion you write is passed the (x, y, text) to be sent to the display, your own code calls your relevant display libraries own function.          
All the ones I've seen have a drawString(x, y, character) type function, so it should be easy.          

That's it! 

### Restrictions:
-The library supports only one font size at a time.          
........You supply the width/height in pixels for the display, and the columns/rows count for the text at the start.          
-Colors have to be implemented by yourself in the callback function if you want them.             
........The library knows nothing about color. It deals only with text and its position.               



### Work remaining:          
-Write some callback functions for several graphics libraries.                   
-Update this readme with the examples for a few graphics libraries like g8u2, OneBitDisplay, etc...                  
-Add a flashing cursor?         

Thanks to all the original writers for the original code, saved me hours.
