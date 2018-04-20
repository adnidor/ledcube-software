#!/bin/bash
avr-gcc -std=gnu11 -Os -DF_CPU=20000000 -mmcu=atmega8 cubelib.c main.c
