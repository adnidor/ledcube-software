#include<avr/interrupt.h>
#include<avr/io.h>
#include<util/delay.h>
#include"cubelib.h"

uint8_t framebuffer[4];
volatile uint8_t transfer_in_progress = 0;
volatile uint8_t spi_transfer_index = 0;

inline void set_pixel(int row, int column) {
    if (row == 8) {
        framebuffer[3] |= (1<<column);
        return;
    }

    framebuffer[column] |= (1<<row);
}
    
inline void unset_pixel(int row, int column) {
    if (row == 8) {
        framebuffer[3] &= ~(1<<column);
        return;
    }

    framebuffer[column] &= ~(1<<row);
}

ISR(SPI_STC_vect) {
    spi_transfer_index++;

    if (spi_transfer_index= 4) { //transfer complete
        transfer_in_progress = 0;
        //spi_transfer_index = 0;

        //toggle RCLK after completion
        PORTB |= (1<<PB0);
        _delay_ms(10);
        PORTB &= ~(1<<PB0);
        
        return;
    }

    SPDR = framebuffer[spi_transfer_index];
}

void wait_for_transfer() {
    while(transfer_in_progress) asm("nop");
}

void init_spi() {
    DDRB |= (1<<PB3)|(1<<PB5)|(1<<PB0);
    SPCR = (1<<SPE)|(1<<SPIE)|(1<<MSTR);
    SPSR = (1<<SPI2X);
}

void write_out() {
    //write framebuffer to shift registers
    if (transfer_in_progress)
        return;

    transfer_in_progress = 1;
    spi_transfer_index = 0;

    SPDR = framebuffer[spi_transfer_index];
}
