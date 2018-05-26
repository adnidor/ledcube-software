#include<util/delay.h>
#include"cubelib.h"

void loop() {
    for (int i = 0;i<9;i++) {
        for (int j = 0;j<3;j++) {
            set_pixel(i,j);
            soft_write_out();
            _delay_ms(100);
            //unset_pixel(i,j);
        }
    }    
    clear_screen();
}

void main() {
    init_spi();
    while(1)
        loop();
}
