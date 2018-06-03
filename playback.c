#include<util/delay.h>
#include<avr/io.h>
#include"cubelib.h"
#include<stdlib.h>
#include<avr/interrupt.h>
#include<inttypes.h>
#include<stdbool.h>

const uint32_t movie[] = { 0x00005500, 0x80220080, 0x802a5580, 0xa0a200a2, 0xa0a255a2, 0xe0a2a2a2 };

#define DELAY_MS 1000

void main() {
    init_spi();

    size_t length = sizeof(movie)/sizeof(uint32_t);

    int i = 0;

    while (true) {
        set_raw_framebuffer(movie[i]);
        soft_write_out();
        _delay_ms(DELAY_MS);
        i++;
        if (i == length) i = 0;
    }
}
