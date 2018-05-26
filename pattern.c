#include<util/delay.h>
#include"cubelib.h"

const int anim_leds[] = { 0, 3, 6, 7, 8, 5, 2, 1 };
const int anim_leds_rev[] = { 0,1,2,5,8,7,6,3 };

void loop() {
    for (int i = 0; i<(sizeof(anim_leds)/sizeof(int)); i++) {
        clear_screen();
        set_pixel(anim_leds_rev[i],2);
        set_pixel(anim_leds[i],1);
        set_pixel(anim_leds_rev[i],0);
        soft_write_out();
        _delay_ms(100);
    }
}

void main() {
    init_spi();
    while(1)
        loop();
}
