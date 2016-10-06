/*
 * main.c
 *
 *  Created on: May 6, 2013
 *      Author: RobG
 */
#include "msp430.h"
#include "utils.h"
#include "edukit.h"
#include "ek_switch_demo.h"
#include "ek_draw_demo.h"
//#include "ek_buzzer_demo.h"

void main(void) {

	//
	// required
	//
	WDTCTL = WDTPW + WDTHOLD;	// disable WDT
	initMSP430();				// init MSP430's clock
	__delay_cycles(16000000);	// wait for LCD to reset
	setUpSPIforLCD(); 			// set up LCD's SPI
	initLCD();					// init LCD
	intro();					// run intro

	//
	// main code
	//
	// Draw demo
	configureDrawDemo();
	runDrawDemo();
	//
	// Switch demo
	// install s1 and s2 and remove s3 and s4 jumpers
	// configureSwitchDemo();
	// runSwitchDemo();
	//
	// Buzzer demo
	//configureBuzzerDemo();
	//runBuzzerDemo();
}

