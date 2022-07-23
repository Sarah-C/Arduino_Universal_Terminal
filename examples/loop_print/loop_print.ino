#include <universal_terminal.h>

grove_terminal terminal;
int32_t        value = 0;
void setup() {
    terminal.begin();
}

void loop() {
    terminal.println(value);
    value += 1;
    delay(1000);
}
