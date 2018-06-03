.PHONY: all clean

all: dice.bin fill.bin pattern.bin rand.bin playback.bin

clean:
	rm *.bin *.o

dice.bin: dice.c cubelib.o
	avr-gcc -g -std=gnu11 -Os -DF_CPU=1000000 -mmcu=atmega8 cubelib.o dice.c -o dice.bin

playback.bin: playback.c cubelib.o
	avr-gcc -g -std=gnu11 -Os -DF_CPU=1000000 -mmcu=atmega8 cubelib.o playback.c -o playback.bin

fill.bin: fill.c cubelib.o
	avr-gcc -g -std=gnu11 -Os -DF_CPU=1000000 -mmcu=atmega8 cubelib.o fill.c -o fill.bin

pattern.bin: pattern.c cubelib.o
	avr-gcc -g -std=gnu11 -Os -DF_CPU=1000000 -mmcu=atmega8 cubelib.o pattern.c -o pattern.bin

rand.bin: rand.c cubelib.o
	avr-gcc -g -std=gnu11 -Os -DF_CPU=1000000 -mmcu=atmega8 cubelib.o rand.c -o rand.bin

cubelib.o: cubelib.c
	avr-gcc -g -std=gnu11 -Os -DF_CPU=1000000 -mmcu=atmega8 cubelib.c -c -o cubelib.o
