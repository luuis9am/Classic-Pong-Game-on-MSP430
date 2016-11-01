# makfile configuration
CPU             	= msp430g2553
CFLAGS          	= -mmcu=${CPU} -Os -I../h -I../h

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-gcc -mmcu=${CPU} -c

all:shapemotion.elf

#additional rules for files
shapemotion.elf: ${COMMON_OBJECTS} shapemotion.o wdt_handler.o
	${CC} -mmcu=${CPU}   -o $@ $^ -L../lib -lTimer -lLcd -lShape -lCircle -lp2sw

load: shapemotion.elf
	mspdebug rf2500 "prog $^"

clean:
	rm -f *.o *.elf
