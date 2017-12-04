# makefile configuration
COMMON_OBJECTS  = 
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -I../h
LDFLAGS		= -L/opt/ti/msp430_gcc/include

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-gcc -mcu=${CPU} -c

all: shapemotion.elf

#additional rules for files
pong.elf: ${COMMON_OBJECTS} pong.o wdt_handler.o buzzer.o projectmain.o
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -L../lib -;Timer -lLcd -lShape -lCircle -lp2sw

load: pong.elf
	mspdebug rf2500 "prog $^"

clean:
	rm -f *.o *.elf
