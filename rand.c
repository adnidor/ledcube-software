#include<util/delay.h>
#include<stdlib.h>
#include"cubelib.h"

void loop() {
    int row = rand()%9;
    int column = rand()%3;
    set_pixel(row,column);
    soft_write_out();
    _delay_ms(20);
    unset_pixel(row,column);
}

void main() {
    init_spi();
    while(1)
        loop();
}
