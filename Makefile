#
# Makefile - blink.elf
#
# @author Adrian Veliz
# @author Eric Freudenthal
# @version 0.1.20130815
#


# makfile configuration
COMMON_OBJECTS         	= edukit.o ek_switch_demo.o ek_draw_demo.o
CPU             	= msp430g2553
CFLAGS          	= -mmcu=${CPU} -Os

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-as

all: main.elf

#additional rules for files
main.elf: ${COMMON_OBJECTS} main.o
	${CC} -mmcu=${CPU} -o $@ $^

install_main: main.elf
	mspdebug rf2500 "prog $^"

clean:
	rm -f *.o *.elf


#project dependencies

edukit.o: edukit.c edukit.h

ek_switch_demo.o: ek_switch_demo.c ek_switch_demo.h

ek_draw_demo.o: ek_draw_demo.c ek_draw_demo.h
