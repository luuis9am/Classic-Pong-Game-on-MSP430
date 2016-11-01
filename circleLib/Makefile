all: libCircle.a

CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -Os -I../h

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-as
AR              = msp430-elf-ar

abCircle.h libCircle.a: makeCircles.c abCircle.o _abCircle.h Makefile
	cc -o makeCircles makeCircles.c
	rm -rf circles; mkdir circles
	(cd circles; ../makeCircles; $(CC) $(CFLAGS) -I../../h -c *.c)
	echo "// Automatically generated file.  (c) Eric Freudenthal, 2016" > abCircle.h
	cat _abCircle.h circles/*.h >> abCircle.h
	$(AR) crs libCircle.a circles/*.o abCircle.o

abCircle.o: _abCircle.h abCircle.c

install: libCircle.a abCircle.h
	mkdir -p ../h ../lib
	cp libCircle.a ../lib
	cp abCircle.h ../h


clean:
	rm -f libCircle.a abCircle.h *.o *.elf
	rm -rf circles

circledemo.elf: circledemo.o libCircle.a
	$(CC) $(CFLAGS) $^ -L../lib -lLcd -lTimer -lShape -o $@

load: circledemo.elf
	mspdebug rf2500 "prog $^"


