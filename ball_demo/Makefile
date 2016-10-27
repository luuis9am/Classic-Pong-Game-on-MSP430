# makfile configuration
CPU             	= msp430g2553
CFLAGS          	= -mmcu=${CPU} -Os -I../h -I../h

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-gcc -mmcu=${CPU} -c

all: main.elf

#additional rules for files
main.elf: ${COMMON_OBJECTS} switches.o main.o ../lib/libTimer.a ../lib/libLcd.a wdt_handler.o
	${CC} -mmcu=${CPU} -o $@ $^

load: main.elf
	mspdebug rf2500 "prog $^"

clean:
	rm -f *.o *.elf
