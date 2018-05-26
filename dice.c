#include<util/delay.h>
#include<avr/io.h>
#include"cubelib.h"
#include<stdlib.h>
#include<avr/interrupt.h>
#include<inttypes.h>
#include<stdbool.h>

const uint32_t dice[] = { 0x00005500, 0x80220080, 0x802a5580, 0xa0a200a2, 0xa0a255a2, 0xe0a2a2a2 };

volatile bool button_pressed = false;

void main() {
    init_spi();
    DDRD &= ~(1<<PD2);
    PORTD |= (1<<PD2);

    GIMSK = (1<<INT0);

    sei();

    int i = 0;
    while (!button_pressed) {
        set_raw_framebuffer(dice[i]);
        soft_write_out();
        _delay_ms(10);
        i++;
        if (i == 6) i = 0;
    }
}

ISR(INT0_vect) {
    button_pressed = true;
}
