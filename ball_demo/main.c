#include "msp430.h"
#include "edukit.h"
#include "arena.h"

void main(void) {
	configureClocks();				/* setup master oscillator, CPU & peripheral clocks */
	enableWDTInterrupts();			/* enable periodic interrupt */
	setUpSPIforLCD(); 				/* setup LCD's SPI */
	initLCD();						/* init LCD */
	clearScreen(BLACK);				/* clear screen */
	
	or_sr(0x18);	/* CPU off, GIE on */
}