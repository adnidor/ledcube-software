#include<avr/interrupt.h>
#include<avr/io.h>
#include<util/delay.h>

#ifndef CUBELIB
#define CUBELIB

void set_pixel(int , int ) ;
    
void unset_pixel(int , int ) ;

void wait_for_transfer() ;

void init_spi() ;

void write_out() ;

void soft_write_out() ;
#endif
