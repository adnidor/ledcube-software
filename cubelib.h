#include<stdlib.h>

#ifndef CUBELIB
#define CUBELIB

void set_pixel(int , int ) ;
    
void unset_pixel(int , int ) ;

void set_raw_framebuffer(uint32_t) ;

void clear_screen() ;

void wait_for_transfer() ;

void init_spi() ;

void write_out() ;

void hard_write_out() ;

void soft_write_out() ;
#endif
