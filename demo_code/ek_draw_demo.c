/*
 * ek_draw_demo.c
 *
 *  Created on: Aug 30, 2014
 *      Author: RobG
 */
#include "ek_draw_demo.h"
#include "utils.h"
#include "msp430.h"
#include "edukit.h"

void configureDrawDemo() {

	//nothing to do here
}

void runDrawDemo() {

	while (1) {
		setColor(COLOR_RED);
		//drawPixel(50,50);
		//break;
		//clearScreen(COLOR_YELLOW);

		drawString(0, 10, FONT_SM, "small font red");
		__delay_cycles(8000000);
		setColor(COLOR_BLUE);
		drawString(0, 25, FONT_MD, "medium blue");
		__delay_cycles(8000000);
		setColor(COLOR_GREEN);
		drawString(0, 45, FONT_LG, "large green");
		__delay_cycles(8000000);
		setColor(COLOR_DARK_ORANGE);
		drawString(0, 70, FONT_SM, "1234 ORANGE");
		__delay_cycles(8000000);
		setColor(COLOR_MEDIUM_PURPLE);
		drawString(0, 85, FONT_MD, "1234 M PURPLE");
		__delay_cycles(8000000);
		setColor(COLOR_BLUE);
		drawString(0, 105, FONT_LG, "1234 BLUE");
		break;
		__delay_cycles(16000000);
		setColor(COLOR_WHITE);
		drawString(0, 0, FONT_MD, "drawPixel");
		char c = 0;

		for (c = 0; c < 32; c++) {
			drawPixel(10 + c * 3, 20 + c * 4);
		}

		__delay_cycles(16000000);
		clearScreen(BLACK);

		setColor(COLOR_WHITE);
		drawString(0, 0, FONT_MD, "drawLine");

		for (c = 0; c < 32; c++) {
			setColor(colors[c]);
			char y = 20 + c * 4;
			drawLine(10 + c * 3, y, 120, y);
		}

		__delay_cycles(16000000);
		clearScreen(BLACK);

		setColor(COLOR_WHITE);
		drawString(0, 0, FONT_MD, "drawRect");

		for (c = 0; c < 16; c++) {
			setColor(colors[c]);
			drawRect(5 + c * 3, 20 + c * 3, 75 + c * 3, 120 - c * 3);
		}

		__delay_cycles(16000000);
		clearScreen(BLACK);

		setColor(COLOR_WHITE);
		drawString(0, 0, FONT_MD, "drawCircle");

		for (c = 0; c < 12; c++) {
			setColor(colors[c]);
			drawCircle(50 + c * 2, 80 + c * 2, 50 - c * 4);
		}

		__delay_cycles(16000000);
		clearScreen(BLACK);

		setColor(COLOR_WHITE);
		drawString(0, 0, FONT_MD, "fillRect");

		for (c = 0; c < 16; c++) {
			setColor(colors[c]);
			fillRect(5 + c * 4, 20 + c * 4, 120 - c * 3, 120 - c * 2);
		}

		__delay_cycles(16000000);
		clearScreen(BLACK);

		setColor(COLOR_WHITE);
		drawString(0, 0, FONT_MD, "fillCircle");

		for (c = 0; c < 12; c++) {
			setColor(colors[c]);
			fillCircle(50 + c * 2, 80 + c * 2, 50 - c * 4);
		}

		__delay_cycles(16000000);
		clearScreen(BLACK);

	}
}

