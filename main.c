#include<util/delay.h>
#include"cubelib.h"

void setup() {
    init_spi();

}

void loop() {
    for (int i = 0;i<9;i++) {
        for (int j = 0;j<3;j++) {
            set_pixel(i,j);
            write_out();
            PORTD = 0xFF;
            _delay_ms(50);
            PORTD = 0x00;
            unset_pixel(i,j);
        }
    }    
}

void main() {
    DDRB |= (1<<PB0);
    PORTB &= ~(1<<PB0);
    sei();
    DDRD = 0xFF;
    PORTD = 0xFF;
    _delay_ms(1000);
    PORTD = 0x00;
    _delay_ms(1000);
    PORTD = 0xFF;
    setup();
    PORTD = 0x00;
    while(1)
        loop();
}
