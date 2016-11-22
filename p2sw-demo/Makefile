all: p2sw-demo.elf

CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -Os -I../h

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-as
AR              = msp430-elf-ar

p2sw-demo.elf: p2sw-demo.o
	$(CC) $(CFLAGS) -o $@ $^ -L../lib -lLcd -lp2sw -lTimer

clean:
	rm -f *.a *.o *.elf

load: p2sw-demo.elf
	mspdebug rf2500 "prog $^"

