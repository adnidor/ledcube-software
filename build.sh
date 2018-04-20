#!/bin/bash
avr-gcc -Os -DF_CPU=20000000 -mmcu=atmega8 cubelib.c main.c
