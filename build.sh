#!/bin/bash
avr-gcc -std=gnu11 -Os -DF_CPU=1000000 -mmcu=atmega8 cubelib.c main.c
gcc -std=gnu11 -lcunit tests.c -o tests
