/*
 * ek_switch_demo.c
 *
 *  Created on: Aug 30, 2014
 *      Author: RobG
 */
#include "msp430.h"
#include "utils.h"
#include "ek_switch_demo.h"
#include "edukit.h"

static int s1 = 0;
static int s2 = 0;
static int s3 = 0;
static int s4 = 0;

void configureSwitchDemo() {

	P2OUT |= BIT0 + BIT1 + BIT2 + BIT3;
	P2REN |= BIT0 + BIT1 + BIT2 + BIT3;
	P2IES |= BIT0 + BIT1 + BIT2 + BIT3;
	P2IFG = 0;
	P2IE |= BIT0 + BIT1 + BIT2 + BIT3;

	_bis_SR_register(GIE);      // enable interrupts
}

void runSwitchDemo() {

	setColor(COLOR_BLUE);
	drawString(5, 5, FONT_MD, "With debounce");
	setColor(COLOR_GREEN);
	drawString(5, 25, FONT_LG, "S1:");
	drawString(5, 45, FONT_LG, "S2:");
	setColor(COLOR_BLUE);
	drawString(5, 65, FONT_MD, "No debounce");
	setColor(COLOR_GREEN);
	drawString(5, 85, FONT_LG, "S3:");
	drawString(5, 105, FONT_LG, "S4:");

	setColor(COLOR_ORANGE_RED);

	while (1) {
		char array[6] = { 0, };
		int2ASCII(s1, array, 0);
		drawString(50, 25, FONT_LG_BKG, array);
		int2ASCII(s2, array, 0);
		drawString(50, 45, FONT_LG_BKG, array);
		int2ASCII(s3, array, 0);
		drawString(50, 85, FONT_LG_BKG, array);
		int2ASCII(s4, array, 0);
		drawString(50, 105, FONT_LG_BKG, array);
	}
}

//#pragma vector=PORT2_VECTOR
//__interrupt void
interrupt(PORT2_VECTOR) Port_2(void) {

	if (P2IFG & BIT0) {
		s1++;
		P2IFG &= ~BIT0;
	}

	if (P2IFG & BIT1) {
		s2++;
		P2IFG &= ~BIT1;
	}

	if (P2IFG & BIT2) {
		s3++;
		P2IFG &= ~BIT2;
	}

	if (P2IFG & BIT3) {
		s4++;
		P2IFG &= ~BIT3;
	}
}

