# makfile configuration
COMMON_OBJECTS         	= edukit.o 
CPU             	= msp430g2553
CFLAGS          	= -mmcu=${CPU} -Os

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-as

all: main.elf

#additional rules for files
main.elf: ${COMMON_OBJECTS} main.o ball.o arena.o ../lib/libTimer.a
	${CC} -mmcu=${CPU} -o $@ $^

install: main.elf
	mspdebug rf2500 "prog $^"

clean:
	rm -f *.o *.elf


#project dependencies

edukit.o: edukit.c edukit.h

ball.o: ball.c

arena.o: arena.c
