# makfile configuration
CPU             	= msp430g2553
CFLAGS          	= -mmcu=${CPU} -Os -I../h -I../h

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-as

all: main.elf

#additional rules for files
main.elf: ${COMMON_OBJECTS} main.o ../lib/libTimer.a ../lib/libLcd.a
	${CC} -mmcu=${CPU} -o $@ $^

load: main.elf
	mspdebug rf2500 "prog $^"

clean:
	rm -f *.o *.elf