#define F_CPU 1000000

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
            _delay_ms(50);
            unset_pixel(i,j);
        }
    }    
}

void main() {
    setup();
    while(1)
        loop();
}
