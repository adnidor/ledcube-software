#!/bin/bash
avr-gcc -g -std=gnu11 -Os -DF_CPU=1000000 -mmcu=atmega8 cubelib.c main.c -o ledcube.bin
#gcc -std=gnu11 -lcunit tests.c -o tests
