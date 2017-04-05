all: libp2sw.a

CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -Os -I../h 
LDFLAGS		= -L../lib -L/opt/ti/msp430_gcc/include/ 

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-as
AR              = msp430-elf-ar

OBJECTS         = p2switches.o

libp2sw.a: $(OBJECTS)
	$(AR) crs $@ $^

$(OBJECTS): p2switches.h

install: libp2sw.a
	mkdir -p ../h ../lib
	mv $^ ../lib
	cp *.h ../h

clean:
	rm -f *.a *.o *.elf

switchdemo.elf: switchdemo.o libp2sw.a 
	$(CC) $(CFLAGS) ${LDFLAGS} -o $@ $^ -lTimer

load: switchdemo.elf
	mspdebug rf2500 "prog $^"

