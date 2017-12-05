# makfile configuration
CPU             	= msp430g2553
CFLAGS          	= -mmcu=${CPU} -Os -I../h -I../h
LDFLAGS	                = -L../lib -L/opt/ti/msp430_gcc/include/

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-gcc -mmcu=${CPU} -c

all: pong_game.elf

#additional rules for files
pong_game.elf: ${COMMON_OBJECTS} pong_game.o wdt_handler.o buzzer.o
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer -lLcd -lShape -lCircle -lp2sw

load: pong_game.elf
	mspdebug rf2500 "prog $^"

clean:
	rm -f *.o *.elf
