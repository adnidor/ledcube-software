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
    //SPCR = (1<<SPE)|(1<<SPIE)|(1<<MSTR);
    //SPSR = (1<<SPI2X);

    DDRB |= (1<<PB0);
    PORTB &= ~(1<<PB0);
}

void write_out() {
    //write framebuffer to shift registers
    if (transfer_in_progress)
        return;

    transfer_in_progress = 1;
    spi_transfer_index = 0;

    SPDR = framebuffer[spi_transfer_index];
}

void soft_write_out() {
    // SCK == PB5
    // MOSI == PB3

    #define SCK_ON PORTB |= (1<<PB5);
    #define SCK_OFF PORTB &= ~(1<<PB5);
    #define MOSI_ON PORTB |= (1<<PB3);
    #define MOSI_OFF PORTB &= ~(1<<PB3);

    for (int i = 0; i<4; i++) {
        for (int j = 0; j<8; j++) {
            if (framebuffer[i] & (1<<j) != 0)
                MOSI_ON
            else
                MOSI_OFF
            _delay_us(10);
            SCK_ON
            _delay_ms(1);
            SCK_OFF
            _delay_ms(1);
        }
    }
}
