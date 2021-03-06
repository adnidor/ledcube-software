#include<avr/interrupt.h>
#include<avr/io.h>
#include<util/delay.h>
#include<inttypes.h>
#include"cubelib.h"

uint8_t framebuffer[4];
volatile uint8_t transfer_in_progress = 0;
volatile uint8_t spi_transfer_index = 0;

void set_pixel(int row, int column) {
    if (row == 8) {
        framebuffer[3] |= (128>>column);
        return;
    }

    framebuffer[column] |= (128>>row);
}
    
void unset_pixel(int row, int column) {
    if (row == 8) {
        framebuffer[3] &= ~(128>>column);
        return;
    }

    framebuffer[column] &= ~(128>>row);
}

void set_raw_framebuffer(uint32_t content) {
    framebuffer[0] = content;
    framebuffer[1] = content>>8;
    framebuffer[2] = content>>16;
    framebuffer[3] = content>>24;
}

void clear_screen() {
    set_raw_framebuffer(0);
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
    uint8_t tmp_SREG = SREG;
    cli();
    // SCK == PB5
    // MOSI == PB3

    #define SCK_ON PORTB |= (1<<PB5);
    #define SCK_OFF PORTB &= ~(1<<PB5);
    #define MOSI_ON PORTB |= (1<<PB3);
    #define MOSI_OFF PORTB &= ~(1<<PB3);

    for (int i = 4; i>0; i--) {
        for (int j = 0; j<8; j++) {
            if ((framebuffer[i-1] & (1<<j)) != 0)
                MOSI_ON
            else
                MOSI_OFF
            SCK_ON
            SCK_OFF
        }
    }
    //toggle RCLK after completion
    PORTB |= (1<<PB0);
    //_delay_us(10);
    PORTB &= ~(1<<PB0);

    SREG = tmp_SREG;

}
