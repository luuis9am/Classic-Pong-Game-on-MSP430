/*
 * edukit.c
 *
 *  Created on: Aug 20, 2014
 *      Author: RobG
 */

#include "edukit.h"
#include "msp430.h"
//
// Private variables
u_char _colorLowByte = 0;
u_char _colorHighByte = 0;
u_char _bgColorLowByte = 0;
u_char _bgColorHighByte = 0;

//u_char _xPos = 0;
//u_char _yPos = 0;

u_char _orientation = 0;

/**
 * Initialize MSP430
 **/
/* void initMSP430() { */

/* 	BCSCTL1 = CALBC1_16MHZ; // Set DCO clock to 16MHz */
/* 	DCOCTL = CALDCO_16MHZ; */

/* } */

/**
 * Set up onboard LCD's SPI and control pins
 **/
void setUpSPIforLCD() {

	LCD_DC_OUT |= LCD_DC_PIN;
	LCD_DC_DIR |= LCD_DC_PIN;

	LCD_CS_OUT |= LCD_CS_PIN;
	LCD_CS_DIR |= LCD_CS_PIN;

	LCD_SPI_OUT |= LCD_SCLK_PIN;
	LCD_SPI_DIR |= LCD_SCLK_PIN;
	LCD_SPI_OUT |= LCD_MOSI_PIN;
	LCD_SPI_DIR |= LCD_MOSI_PIN;
	LCD_SPI_SEL |= LCD_SCLK_PIN + LCD_MOSI_PIN;
	LCD_SPI_SEL2 |= LCD_SCLK_PIN + LCD_MOSI_PIN;

	UCB0CTL1 |= UCSWRST;
	UCB0CTL0 = UCCKPH + UCMSB + UCMST + UCSYNC; // 3-pin, 8-bit SPI master
	UCB0CTL1 |= UCSSEL_2; // SMCLK
	UCB0BR0 |= 0x01; // 1:1
	UCB0BR1 = 0;
	UCB0CTL1 &= ~UCSWRST;
	LCD_SELECT();
}

/**
 * Get screen dimensions
 **/
u_char getScreenWidth() {
	if (_orientation == ORIENTATION_VERTICAL
			|| _orientation == ORIENTATION_VERTICAL_ROTATED)
		return SHORT_EDGE_PIXELS;
	else
		return LONG_EDGE_PIXELS;
}

u_char getScreenHeight() {
	if (_orientation == ORIENTATION_VERTICAL
			|| _orientation == ORIENTATION_VERTICAL_ROTATED)
		return LONG_EDGE_PIXELS;
	else
		return SHORT_EDGE_PIXELS;
}

/**
 * Write data to LCD (private)
 **/
// code duplication, but we are saving clock cycles by not passing dataCommand
void _writeData(u_char data) 
{
  while (UCB0STAT & UCBUSY);	/* wait for previous transfer to complete */
  LCD_DC_HI();			/* specify sending data */
  UCB0TXBUF = data;		/* send data */
}

/**
 * Write command to LCD (private)
 **/
// code duplication, but we are saving clock cycles by not passing dataCommand
void _writeCommand(u_char command) 
{
  while (UCB0STAT & UCBUSY);	/* wait for previous transfer to complete */
  LCD_DC_LO();			/* specify sending a command */
  UCB0TXBUF = command;		/* send command */
}

/**
 * Long delay (private)
 **/
void _delay(u_char x10ms) {
	while (x10ms > 0) {
		__delay_cycles(160000);
		x10ms--;
	}
}

/**
 * Set area to draw to (private)
 **/
void _setArea(u_char xStart, u_char yStart, u_char xEnd, u_char yEnd) {

	_writeCommand(CASETP);
	_writeData(0);
	_writeData(xStart);
	_writeData(0);
	_writeData(xEnd);
	_writeCommand(PASETP);
	_writeData(0);
	_writeData(yStart);
	_writeData(0);
	_writeData(yEnd);
	_writeCommand(RAMWRP);
}

/**
 * Adjust gamma (private)
 * Gamma correction is needed for accurate color but is not necessary.
 **/
void _gammaAdjustment() {
	u_char numOfParams;

#if defined ILI9163
	numOfParams = 15;
	const u_char gmctrp1[] = { 0x3F, 0x25, 0x1C, 0x1E, 0x20, 0x12, 0x2A, 0x90,
			0x24, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00 };
	const u_char gmctrn1[] = { 0x20, 0x20, 0x20, 0x20, 0x05, 0x15, 0x00, 0xA7,
			0x3D, 0x18, 0x25, 0x2A, 0x2B, 0x2B, 0x3A };
	//const u_char gmctrp1[] = { 0x36, 0x29, 0x12, 0x22, 0x1C, 0x15, 0x42, 0xB7, 0x2F, 0x13, 0x12, 0x0A, 0x11, 0x0B, 0x06 };
	//const u_char gmctrn1[] = { 0x09, 0x16, 0x2D, 0x0D, 0x13, 0x15, 0x40, 0x48, 0x53, 0x0C, 0x1D, 0x25, 0x2E, 0x34, 0x39 };
#endif
#if defined ST7735
	numOfParams = 16;
	const u_char gmctrp1[] = {0x02, 0x1c, 0x07, 0x12, 0x37, 0x32, 0x29, 0x2d,
		0x29, 0x25, 0x2B, 0x39, 0x00, 0x01, 0x03, 0x10};
	const u_char gmctrn1[] = {0x03, 0x1d, 0x07, 0x06, 0x2E, 0x2C, 0x29, 0x2D,
		0x2E, 0x2E, 0x37, 0x3F, 0x00, 0x00, 0x02, 0x10};
#endif

	u_char c = 0;
	_writeCommand(GMCTRP1); // gamma adjustment (+ polarity)
	while (c < numOfParams) {
		_writeData(gmctrp1[c]);
		c++;
	}
	c = 0;
	_writeCommand(GMCTRN1); // gamma adjustment (- polarity)
	while (c < numOfParams) {
		_writeData(gmctrn1[c]);
		c++;
	}
}

/**
 * Initialize onboard LCD
 **/
void initLCD() 
{
  _writeCommand(SWRESET); //software reset
  _delay(20);
  _writeCommand(SLEEPOUT); //exit sleep
  _delay(20);
  _writeCommand(COLMOD); //Set Color Format 16bit
  _writeData(0x05);
  //_gammaAdjustment();
  _writeCommand(DISPON); //display ON
  setOrientation(ORIENTATION_VERTICAL_ROTATED);
}

/**
 * Intro
 **/
void intro()
{
  clearScreen(COLOR_BLACK);
  
  setColor(COLOR_GREEN);
  drawString(28, 5, FONT_LG, "Edu");
  setColor(COLOR_ORANGE_RED);
  drawString(64, 5, FONT_LG, "Kit");
  setColor(COLOR_WHITE);
  drawString(20, 24, FONT_MD, "BoosterPack");
  setColor(COLOR_BLUE);
  drawString(50, 40, FONT_SM, "UTEP");
  setColor(COLOR_YELLOW);
  drawString(5, 55, FONT_LG, "Learn and");
  drawString(20, 75, FONT_LG, "have fun!");
  
  setColor(COLOR_GREEN);
  drawCircle(64, 130, 25);
  drawLine(39, 130, 52, 130);
  setColor(COLOR_BLACK);
  fillRect(84, 110, 90, 150);
  setColor(COLOR_ORANGE_RED);
  drawLine(58, 118, 58, 142);
  drawLine(58, 130, 73, 145);
  drawLine(58, 130, 73, 115);
  drawLine(71, 143, 69, 138);
  drawLine(71, 143, 66, 141);
  
  __delay_cycles(48000000);
  
  clearScreen(COLOR_BLACK);
}

/**
 * Change LCD's orientation
 * One of 4 possible values:
 * ORIENTATION_VERTICAL, ORIENTATION_HORIZONTAL, 
 * ORIENTATION_VERTICAL_ROTATED, ORIENTATION_HORIZONTAL_ROTATED
 **/
void setOrientation(u_char orientation) 
{
  _writeCommand(MADCTL);
  switch (orientation) {
  case ORIENTATION_HORIZONTAL:
    _writeData(0x68);
    break;
  case ORIENTATION_VERTICAL_ROTATED:
    _writeData(0x08);
    break;
  case ORIENTATION_HORIZONTAL_ROTATED:
    _writeData(0xA8);
    break;
  default:
    _writeData(0xC8);
  }
  _orientation = orientation;
}

u_int rgbToBgr(u_int rgbColor)
{
  u_int bgrColor = rgbColor & COLOR_GREEN; /* g in same bits! */
  bgrColor |= rgbColor >> 11; 	/* r to b */
  bgrColor |= (rgbColor << 11);	/* b to r */
  return bgrColor;
}

/**
 * Set colors, foreground and background
 * 16 bit color, 5/6/5 BGR format
 **/
void setColor(u_int rgbColor) {
  // colors are brg not rgb
  u_int bgrColor = rbgToBgr(rgbColor);
  _colorLowByte = bgrColor;
  _colorHighByte = bgrColor >> 8;
}

void setBackgroundColor(u_int rgbColor) {
  u_int bgrColor = rbgToBgr(rgbColor);
  _bgColorLowByte = bgrColor;
  _bgColorHighByte = bgrColor >> 8;
}

/**
 * Clear screen (fill with color)
 **/
void clearScreen(u_int color) {
  u_char w = getScreenWidth();
  u_char h = getScreenHeight();
  _setArea(0, 0, w - 1, h - 1);
  setBackgroundColor(color);
  
  while (h != 0) {
    while (w != 0) {
      _writeData(_bgColorHighByte);
      _writeData(_bgColorLowByte);
      w--;
    }
    w = getScreenWidth();
    h--;
  }
}

/**
 * Draw single pixel at x,y
 **/
void drawPixel(u_char x, u_char y) {
  _setArea(x, y, x, y);
  _writeData(_colorHighByte);
  _writeData(_colorLowByte);
}

/**
 * Draw string at x,y
 * Type:
 * FONT_SM - small (5x8,) FONT_MD - medium (8x12,) FONT_LG - large (11x16)
 * FONT_SM_BKG, FONT_MD_BKG, FONT_LG_BKG - as above, but with background color
 **/
void drawString(u_char x, u_char y, char type, char *string) {
  u_char xs = x;
  switch (type) {
  case FONT_SM:
    while (*string) {
      drawCharSm(xs, y, *string++);
      xs += 6;
    }
    break;
  case FONT_MD:
    while (*string) {
      drawCharMd(xs, y, *string++);
      xs += 8;
    }
    break;
  case FONT_LG:
    while (*string) {
      drawCharLg(xs, y, *string++);
      xs += 12;
    }
    break;
  case FONT_SM_BKG:
    while (*string) {
      drawCharSmBkg(xs, y, *string++);
      xs += 6;
    }
    break;
  case FONT_MD_BKG:
    while (*string) {
      drawCharMdBkg(xs, y, *string++);
      xs += 8;
    }
    break;
  case FONT_LG_BKG:
    while (*string) {
      drawCharLgBkg(xs, y, *string++);
      xs += 12;
    }
    break;
  }
}

/////////////////////////////////////////////////////////////
// 5x7 font - this function does not draw background pixels
/////////////////////////////////////////////////////////////
u_char 
drawCharSm(u_char x, u_char y, char c) {
  u_char col = 0;
  u_char row = 0;
  u_char bit = 0x01;
  u_char oc = c - ' ';
  while (row < 8) {
    while (col < 5) {
      if (font_5x7[oc][col] & bit)
	drawPixel(x + col, y + row);
      col++;
    }
    col = 0;
    bit <<= 1;
    row++;
  }
  return x + 5;
}

//////////////////////////////////////////////////////
// 5x7 font - this function draws background pixels
//////////////////////////////////////////////////////
void drawCharSmBkg(u_char x, u_char y, char c) {
	u_char col = 0;
	u_char row = 0;
	u_char bit = 0x01;
	u_char oc = c - 0x20;
	_setArea(x, y, x + 4, y + 7); // if you want to fill column between chars, change x + 4 to x + 5

	while (row < 8) {
		while (col < 5) {
			if (font_5x7[oc][col] & bit) {
				//foreground
				_writeData(_colorHighByte);
				_writeData(_colorLowByte);
			} else {
				//background
				_writeData(_bgColorHighByte);
				_writeData(_bgColorLowByte);
			}
			col++;
		}
		// if you want to fill column between chars, writeData(bgColor) here
		col = 0;
		bit <<= 1;
		row++;
	}
}

///////////////////////////////////////////////////////////////
// 11x16 font - this function does not draw background pixels
///////////////////////////////////////////////////////////////
void drawCharLg(u_char x, u_char y, char c) {
	u_char col = 0;
	u_char row = 0;
	u_int bit = 0x0001;
	u_char oc = c - 0x20;
	while (row < 16) {
		while (col < 11) {
			if (font_11x16[oc][col] & bit)
				drawPixel(x + col, y + row);
			col++;
		}
		col = 0;
		bit <<= 1;
		row++;
	}
}

///////////////////////////////////////////////////////////
// 11x16 font - this function draws background pixels
///////////////////////////////////////////////////////////
void drawCharLgBkg(u_char x, u_char y, char c) {
	u_char col = 0;
	u_char row = 0;
	u_int bit = 0x0001;
	u_char oc = c - 0x20;
	_setArea(x, y, x + 10, y + 15);
	while (row < 16) {
		while (col < 11) {
			if (font_11x16[oc][col] & bit) {
				//foreground
				_writeData(_colorHighByte);
				_writeData(_colorLowByte);
			} else {
				//background
				_writeData(_bgColorHighByte);
				_writeData(_bgColorLowByte);
			}
			col++;
		}
		col = 0;
		bit <<= 1;
		row++;
	}
}

//////////////////////////////////////////////////////////////
// 8x12 font - this function does not draw background pixels
//////////////////////////////////////////////////////////////
void drawCharMd(u_char x, u_char y, char c) {
	u_char col = 0;
	u_char row = 0;
	u_char bit = 0x80;
	u_char oc = c - 0x20;
	while (row < 12) {
		while (col < 8) {
			if (font_8x12[oc][row] & bit)
				drawPixel(x + col, y + row);
			bit >>= 1;
			col++;
		}
		bit = 0x80;
		col = 0;
		row++;
	}
}

////////////////////////////////////////////////////////
// 8x12 font - this function draws background pixels
////////////////////////////////////////////////////////
void drawCharMdBkg(u_char x, u_char y, char c) {
	u_char col = 0;
	u_char row = 0;
	u_char bit = 0x80;
	u_char oc = c - 0x20;
	_setArea(x, y, x + 7, y + 11);
	while (row < 12) {
		while (col < 8) {
			if (font_8x12[oc][row] & bit) {
				//foreground
				_writeData(_colorHighByte);
				_writeData(_colorLowByte);
			} else {
				//background
				_writeData(_bgColorHighByte);
				_writeData(_bgColorLowByte);
			}
			bit >>= 1;
			col++;
		}
		bit = 0x80;
		col = 0;
		row++;
	}

}

////////////////////////
// Images
////////////////////////
//data is 16 bit color
void drawImage(u_char x, u_char y, u_char w, u_char h, u_int * data) {

}

// lut is used, ?0 means skip, sort of a mask?
void drawImageLut(u_char x, u_char y, u_char w, u_char h, u_char * data,
		u_int * lut) {

}

// each bit represents color, fg and bg colors are used, ?how about 0 as a mask?
void drawImageMono(u_char x, u_char y, u_char w, u_char h, u_char * data) {

}

////////////////////////////////////////////////
// Draw line from xStart,yStart to xEnd,yEnd
////////////////////////////////////////////////
void drawLine(u_char xStart, u_char yStart, u_char xEnd, u_char yEnd) {

	u_char x0, x1, y0, y1;
	u_char d = 0;

// handle direction
	if (yStart > yEnd) {
		y0 = yEnd;
		y1 = yStart;
	} else {
		y1 = yEnd;
		y0 = yStart;
	}

	if (xStart > xEnd) {
		x0 = xEnd;
		x1 = xStart;
	} else {
		x1 = xEnd;
		x0 = xStart;
	}

// check if horizontal
	if (y0 == y1) {
		d = x1 - x0 + 1;
		_setArea(x0, y0, x1, y1);
		while (d-- > 0) {
			_writeData(_colorHighByte);
			_writeData(_colorLowByte);
		}

	} else if (x0 == x1) { // check if vertical
		d = y1 - y0 + 1;
		_setArea(x0, y0, x1, y1);
		while (d-- > 0) {
			_writeData(_colorHighByte);
			_writeData(_colorLowByte);
		}

	} else { // angled
		char dx, dy;
		int sx, sy;

		if (xStart < xEnd) {
			sx = 1;
			dx = xEnd - xStart;
		} else {
			sx = -1;
			dx = xStart - xEnd;
		}

		if (yStart < yEnd) {
			sy = 1;
			dy = yEnd - yStart;
		} else {
			sy = -1;
			dy = yStart - yEnd;
		}

		int e1 = dx - dy;
		int e2;

		while (1) {
			drawPixel(xStart, yStart);
			if (xStart == xEnd && yStart == yEnd)
				break;
			e2 = 2 * e1;
			if (e2 > -dy) {
				e1 = e1 - dy;
				xStart = xStart + sx;
			}
			if (e2 < dx) {
				e1 = e1 + dx;
				yStart = yStart + sy;
			}
		}
	}
}

/////////////////////////////////////////////////////
// Draw rectangle
/////////////////////////////////////////////////////
void drawRect(u_char xStart, u_char yStart, u_char xEnd, u_char yEnd) {

	drawLine(xStart, yStart, xEnd, yStart);
	drawLine(xStart, yEnd, xEnd, yEnd);
	drawLine(xStart, yStart, xStart, yEnd);
	drawLine(xEnd, yStart, xEnd, yEnd);
}

///////////////////////////////////////////
// Draw circle
///////////////////////////////////////////
void drawCircle(u_char x, u_char y, u_char radius) {
	int dx = radius;
	int dy = 0;
	int xChange = 1 - 2 * radius;
	int yChange = 1;
	int radiusError = 0;
	while (dx >= dy) {
		drawPixel(x + dx, y + dy);
		drawPixel(x - dx, y + dy);
		drawPixel(x - dx, y - dy);
		drawPixel(x + dx, y - dy);
		drawPixel(x + dy, y + dx);
		drawPixel(x - dy, y + dx);
		drawPixel(x - dy, y - dx);
		drawPixel(x + dy, y - dx);
		dy++;
		radiusError += yChange;
		yChange += 2;
		if (2 * radiusError + xChange > 0) {
			dx--;
			radiusError += xChange;
			xChange += 2;
		}
	}
}

/////////////////////////
// Fill rectangle
/////////////////////////
void fillRect(u_char xStart, u_char yStart, u_char xEnd, u_char yEnd) {
	_setArea(xStart, yStart, xEnd, yEnd);
	u_int total = (xEnd - xStart + 1) * (yEnd - yStart + 1);
	u_int c = 0;
	while (c < total) {
		_writeData(_colorHighByte);
		_writeData(_colorLowByte);
		c++;
	}
}

////////////////////////////
// Fill circle
////////////////////////////
void fillCircle(u_char x, u_char y, u_char radius) {
	int dx = radius;
	int dy = 0;
	int xChange = 1 - 2 * radius;
	int yChange = 1;
	int radiusError = 0;
	while (dx >= dy) {
		drawLine(x + dy, y + dx, x - dy, y + dx);
		drawLine(x - dy, y - dx, x + dy, y - dx);
		drawLine(x - dx, y + dy, x + dx, y + dy);
		drawLine(x - dx, y - dy, x + dx, y - dy);
		dy++;
		radiusError += yChange;
		yChange += 2;
		if (2 * radiusError + xChange > 0) {
			dx--;
			radiusError += xChange;
			xChange += 2;
		}
	}
}

/////////////////////////////////////
// Converters
/////////////////////////////////////
void int2ASCII(u_int number, char * array, int scale) {
	__asm(" clr		R15");
	__asm(" rla		R12");
	__asm(" rla		R12");
	__asm(" rla		R12");
	__asm(" rla		R12");
	__asm(" rla		R12");
	__asm(" dadd	R15, R15");
	__asm(" rla		R12");
	__asm(" dadd	R15, R15");
	__asm(" rla		R12");
	__asm(" dadd	R15, R15");
	__asm(" rla		R12");
	__asm(" dadd	R15, R15");
	__asm(" rla		R12");
	__asm(" dadd	R15, R15");
	__asm(" rla		R12");
	__asm(" dadd	R15, R15");
	__asm(" rla		R12");
	__asm(" dadd	R15, R15");
	__asm(" rla		R12");
	__asm(" dadd	R15, R15");
	__asm(" rla		R12");
	__asm(" dadd	R15, R15");
	__asm(" rla		R12");
	__asm(" dadd	R15, R15");
	__asm(" rla		R12");
	__asm(" dadd	R15, R15");
	__asm(" rla		R12");
	__asm(" dadd	R15, R15");
	__asm(" mov.b	R15, 3(R13)");
	__asm(" swpb	R15");
	__asm(" mov.b	R15, 1(R13)");
	__asm(" rra		R15");
	__asm(" rra		R15");
	__asm(" rra		R15");
	__asm(" rra		R15");
	__asm(" mov.b	R15, 0(R13)");
	__asm(" swpb	R15");
	__asm(" mov.b	R15, 2(R13)");
	__asm(" and		#0x0F0F, 0(R13)");
	__asm(" and		#0x0F0F, 2(R13)");
	__asm(" add.b	#0x30, 3(R13)");
	__asm(" tst.b	0(R13)");
	__asm(" jnz l10");
	__asm(" cmp	#3, R14");
	__asm(" jge l10");
	__asm(" mov.b	#0x20, 0(R13)");
	__asm(" tst.b	1(R13)");
	__asm(" jnz l20");
	__asm(" cmp	#2, R14");
	__asm(" jge l20");
	__asm(" mov.b	#0x20, 1(R13)");
	__asm(" tst.b	2(R13)");
	__asm(" jnz l30");
	__asm(" cmp	#1, R14");
	__asm(" jge l30");
	__asm(" mov.b	#0x20, 2(R13)");
	__asm(" jmp l40");
	__asm("l10:");
	__asm(" add.b	#0x30, 0(R13)");
	__asm("l20:");
	__asm(" add.b	#0x30, 1(R13)");
	__asm("l30:");
	__asm(" add.b	#0x30, 2(R13)");

	__asm("l40:");
	__asm("	tst	R14");
	__asm(" jz l80");

	__asm(" dec R14");
	__asm(" mov.b	3(R13), 4(R13)");
	__asm("	tst	R14");
	__asm(" jnz l50");
	__asm(" mov.b	#0x2E, 3(R13)");
	__asm(" jmp l90");
	__asm("l50:");

	__asm(" dec R14");
	__asm(" mov.b	2(R13), 3(R13)");
	__asm("	tst	R14");
	__asm(" jnz l60");
	__asm(" mov.b	#0x2E, 2(R13)");
	__asm(" jmp l90");
	__asm("l60:");

	__asm(" dec R14");
	__asm(" mov.b	1(R13), 2(R13)");
	__asm("	tst	R14");
	__asm(" jnz l70");
	__asm(" mov.b	#0x2E, 1(R13)");
	__asm(" jmp l90");
	__asm("l70:");

	__asm(" dec R14");
	__asm(" mov.b	0(R13), 1(R13)");
	__asm(" mov.b	#0x2E, 0(R13)");
	__asm(" jmp l90");

	__asm("l80:");
	__asm(" mov.b	3(R13), 4(R13)");
	__asm(" mov.b	2(R13), 3(R13)");
	__asm(" mov.b	1(R13), 2(R13)");
	__asm(" mov.b	0(R13), 1(R13)");
	__asm(" mov.b	#0x20, 0(R13)");

	__asm("l90:");

	return;
}

/////////////////////////////////////
// Colors
/////////////////////////////////////
const unsigned int colors[43] = { COLOR_BLACK, COLOR_WHITE, COLOR_YELLOW,
COLOR_RED, COLOR_MAGENTA, COLOR_BLUE, COLOR_CYAN,
COLOR_GREEN, COLOR_ORANGE, COLOR_ORANGE_RED,
COLOR_DARK_ORANGE, COLOR_GRAY, COLOR_NAVY, COLOR_ROYAL_BLUE,
COLOR_SKY_BLUE, COLOR_TURQUOISE, COLOR_STEEL_BLUE,
COLOR_LIGHT_BLUE, COLOR_AQUAMARINE, COLOR_DARK_GREEN,
COLOR_DARK_OLIVE_GREEN, COLOR_SEA_GREEN, COLOR_SPRING_GREEN,
COLOR_PALE_GREEN, COLOR_GREEN_YELLOW, COLOR_LIME_GREEN,
COLOR_FOREST_GREEN, COLOR_KHAKI, COLOR_GOLD,
COLOR_GOLDENROD, COLOR_SIENNA, COLOR_BEIGE, COLOR_TAN,
COLOR_BROWN, COLOR_CHOCOLATE, COLOR_FIREBRICK,
COLOR_HOT_PINK, COLOR_PINK, COLOR_DEEP, COLOR_VIOLET,
COLOR_DARK_VIOLET, COLOR_PURPLE, COLOR_MEDIUM_PURPLE };

/////////////////////////////////////
// Fonts
/////////////////////////////////////


const unsigned int font_11x16[95][11] = { 		// offset 0x20
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0x0000,
  0x0000, 		//
  0x0000, 0x0000, 0x0000, 0x007C, 0x33FF, 0x33FF, 0x007C, 0x0000,
  0x0000, 0x0000,
  0x0000, 		// !
  0x0000, 0x0000, 0x003C, 0x003C, 0x0000, 0x0000, 0x003C, 0x003C,
  0x0000, 0x0000,
  0x0000, 		// "
  0x0200, 0x1E10, 0x1F90, 0x03F0, 0x027E, 0x1E1E, 0x1F90, 0x03F0,
  0x027E, 0x001E,
  0x0010, 		// #
  0x0000, 0x0478, 0x0CFC, 0x0CCC, 0x3FFF, 0x3FFF, 0x0CCC, 0x0FCC,
  0x0788, 0x0000,
  0x0000, 		// $
  0x3000, 0x3838, 0x1C38, 0x0E38, 0x0700, 0x0380, 0x01C0, 0x38E0,
  0x3870, 0x3838,
  0x001C, 		// %
  0x0000, 0x1F00, 0x3FB8, 0x31FC, 0x21C6, 0x37E2, 0x1E3E, 0x1C1C,
  0x3600, 0x2200,
  0x0000, 		// &
  0x0000, 0x0000, 0x0000, 0x0027, 0x003F, 0x001F, 0x0000, 0x0000,
  0x0000, 0x0000,
  0x0000, 		// '
  0x0000, 0x0000, 0x03F0, 0x0FFC, 0x1FFE, 0x3807, 0x2001, 0x2001,
  0x0000, 0x0000,
  0x0000, 		// (
  0x0000, 0x0000, 0x2001, 0x2001, 0x3807, 0x1FFE, 0x0FFC, 0x03F0,
  0x0000, 0x0000,
  0x0000, 		// )
  0x0000, 0x0C98, 0x0EB8, 0x03E0, 0x0FF8, 0x0FF8, 0x03E0, 0x0EB8,
  0x0C98, 0x0000,
  0x0000, 		// *
  0x0000, 0x0180, 0x0180, 0x0180, 0x0FF0, 0x0FF0, 0x0180, 0x0180,
  0x0180, 0x0000,
  0x0000, 		// +
  0x0000, 0x0000, 0x0000, 0xB800, 0xF800, 0x7800, 0x0000, 0x0000,
  0x0000, 0x0000,
  0x0000, 		// ,
  0x0000, 0x0180, 0x0180, 0x0180, 0x0180, 0x0180, 0x0180, 0x0180,
  0x0180, 0x0000,
  0x0000, 		// -
  0x0000, 0x0000, 0x0000, 0x3800, 0x3800, 0x3800, 0x0000, 0x0000,
  0x0000, 0x0000,
  0x0000, 		// .
  0x1800, 0x1C00, 0x0E00, 0x0700, 0x0380, 0x01C0, 0x00E0, 0x0070,
  0x0038, 0x001C,
  0x000E, 		// /
  0x07F8, 0x1FFE, 0x1E06, 0x3303, 0x3183, 0x30C3, 0x3063, 0x3033,
  0x181E, 0x1FFE,
  0x07F8, 		// 0
  0x0000, 0x0000, 0x300C, 0x300C, 0x300E, 0x3FFF, 0x3FFF, 0x3000,
  0x3000, 0x3000,
  0x0000, 		// 1
  0x301C, 0x381E, 0x3C07, 0x3E03, 0x3703, 0x3383, 0x31C3, 0x30E3,
  0x3077, 0x303E,
  0x301C, 		// 2
  0x0C0C, 0x1C0E, 0x3807, 0x30C3, 0x30C3, 0x30C3, 0x30C3, 0x30C3,
  0x39E7, 0x1F7E,
  0x0E3C, 		// 3
  0x03C0, 0x03E0, 0x0370, 0x0338, 0x031C, 0x030E, 0x0307, 0x3FFF,
  0x3FFF, 0x0300,
  0x0300, 		// 4
  0x0C3F, 0x1C7F, 0x3863, 0x3063, 0x3063, 0x3063, 0x3063, 0x3063,
  0x38E3, 0x1FC3,
  0x0F83, 		// 5
  0x0FC0, 0x1FF0, 0x39F8, 0x30DC, 0x30CE, 0x30C7, 0x30C3, 0x30C3,
  0x39C3, 0x1F80,
  0x0F00, 		// 6
  0x0003, 0x0003, 0x0003, 0x3003, 0x3C03, 0x0F03, 0x03C3, 0x00F3,
  0x003F, 0x000F,
  0x0003, 		// 7
  0x0F00, 0x1FBC, 0x39FE, 0x30E7, 0x30C3, 0x30C3, 0x30C3, 0x30E7,
  0x39FE, 0x1FBC,
  0x0F00, 		// 8
  0x003C, 0x007E, 0x30E7, 0x30C3, 0x30C3, 0x38C3, 0x1CC3, 0x0EC3,
  0x07E7, 0x03FE,
  0x00FC, 		// 9
  0x0000, 0x0000, 0x0000, 0x1C70, 0x1C70, 0x1C70, 0x0000, 0x0000,
  0x0000, 0x0000,
  0x0000, 		// :
  0x0000, 0x0000, 0x0000, 0x9C70, 0xFC70, 0x7C70, 0x0000, 0x0000,
  0x0000, 0x0000,
  0x0000, 		// ;
  0x0000, 0x00C0, 0x01E0, 0x03F0, 0x0738, 0x0E1C, 0x1C0E, 0x3807,
  0x3003, 0x0000,
  0x0000, 		// <
  0x0000, 0x0660, 0x0660, 0x0660, 0x0660, 0x0660, 0x0660, 0x0660,
  0x0660, 0x0660,
  0x0000, 		// =
  0x0000, 0x3003, 0x3807, 0x1C0E, 0x0E1C, 0x0738, 0x03F0, 0x01E0,
  0x00C0, 0x0000,
  0x0000, 		// >
  0x001C, 0x001E, 0x0007, 0x0003, 0x3783, 0x37C3, 0x00E3, 0x0077,
  0x003E, 0x001C,
  0x0000, 		// ?
  0x0FF8, 0x1FFE, 0x1807, 0x33F3, 0x37FB, 0x361B, 0x37FB, 0x37FB,
  0x3607, 0x03FE,
  0x01F8, 		// @
  0x3800, 0x3F00, 0x07E0, 0x06FC, 0x061F, 0x061F, 0x06FC, 0x07E0,
  0x3F00, 0x3800,
  0x0000, 		// A
  0x3FFF, 0x3FFF, 0x30C3, 0x30C3, 0x30C3, 0x30C3, 0x30E7, 0x39FE,
  0x1FBC, 0x0F00,
  0x0000, 		// B
  0x03F0, 0x0FFC, 0x1C0E, 0x3807, 0x3003, 0x3003, 0x3003, 0x3807,
  0x1C0E, 0x0C0C,
  0x0000, 		// C
  0x3FFF, 0x3FFF, 0x3003, 0x3003, 0x3003, 0x3003, 0x3807, 0x1C0E,
  0x0FFC, 0x03F0,
  0x0000, 		// D
  0x3FFF, 0x3FFF, 0x30C3, 0x30C3, 0x30C3, 0x30C3, 0x30C3, 0x30C3,
  0x3003, 0x3003,
  0x0000, 		// E
  0x3FFF, 0x3FFF, 0x00C3, 0x00C3, 0x00C3, 0x00C3, 0x00C3, 0x00C3,
  0x0003, 0x0003,
  0x0000, 		// F
  0x03F0, 0x0FFC, 0x1C0E, 0x3807, 0x3003, 0x30C3, 0x30C3, 0x30C3,
  0x3FC7, 0x3FC6,
  0x0000, 		// G
  0x3FFF, 0x3FFF, 0x00C0, 0x00C0, 0x00C0, 0x00C0, 0x00C0, 0x00C0,
  0x3FFF, 0x3FFF,
  0x0000, 		// H
  0x0000, 0x0000, 0x3003, 0x3003, 0x3FFF, 0x3FFF, 0x3003, 0x3003,
  0x0000, 0x0000,
  0x0000, 		// I
  0x0E00, 0x1E00, 0x3800, 0x3000, 0x3000, 0x3000, 0x3000, 0x3800,
  0x1FFF, 0x07FF,
  0x0000, 		// J
  0x3FFF, 0x3FFF, 0x00C0, 0x01E0, 0x03F0, 0x0738, 0x0E1C, 0x1C0E,
  0x3807, 0x3003,
  0x0000, 		// K
  0x3FFF, 0x3FFF, 0x3000, 0x3000, 0x3000, 0x3000, 0x3000, 0x3000,
  0x3000, 0x3000,
  0x0000, 		// L
  0x3FFF, 0x3FFF, 0x001E, 0x0078, 0x01E0, 0x01E0, 0x0078, 0x001E,
  0x3FFF, 0x3FFF,
  0x0000, 		// M
  0x3FFF, 0x3FFF, 0x000E, 0x0038, 0x00F0, 0x03C0, 0x0700, 0x1C00,
  0x3FFF, 0x3FFF,
  0x0000, 		// N
  0x03F0, 0x0FFC, 0x1C0E, 0x3807, 0x3003, 0x3003, 0x3807, 0x1C0E,
  0x0FFC, 0x03F0,
  0x0000, 		// O
  0x3FFF, 0x3FFF, 0x0183, 0x0183, 0x0183, 0x0183, 0x0183, 0x01C7,
  0x00FE, 0x007C,
  0x0000, 		// P
  0x03F0, 0x0FFC, 0x1C0E, 0x3807, 0x3003, 0x3603, 0x3E07, 0x1C0E,
  0x3FFC, 0x33F0,
  0x0000, 		// Q
  0x3FFF, 0x3FFF, 0x0183, 0x0183, 0x0383, 0x0783, 0x0F83, 0x1DC7,
  0x38FE, 0x307C,
  0x0000, 		// R
  0x0C3C, 0x1C7E, 0x38E7, 0x30C3, 0x30C3, 0x30C3, 0x30C3, 0x39C7,
  0x1F8E, 0x0F0C,
  0x0000, 		// S
  0x0000, 0x0003, 0x0003, 0x0003, 0x3FFF, 0x3FFF, 0x0003, 0x0003,
  0x0003, 0x0000,
  0x0000, 		// T
  0x07FF, 0x1FFF, 0x3800, 0x3000, 0x3000, 0x3000, 0x3000, 0x3800,
  0x1FFF, 0x07FF,
  0x0000, 		// U
  0x0007, 0x003F, 0x01F8, 0x0FC0, 0x3E00, 0x3E00, 0x0FC0, 0x01F8,
  0x003F, 0x0007,
  0x0000, 		// V
  0x3FFF, 0x3FFF, 0x1C00, 0x0600, 0x0380, 0x0380, 0x0600, 0x1C00,
  0x3FFF, 0x3FFF,
  0x0000, 		// W
  0x3003, 0x3C0F, 0x0E1C, 0x0330, 0x01E0, 0x01E0, 0x0330, 0x0E1C,
  0x3C0F, 0x3003,
  0x0000, 		// X
  0x0003, 0x000F, 0x003C, 0x00F0, 0x3FC0, 0x3FC0, 0x00F0, 0x003C,
  0x000F, 0x0003,
  0x0000, 		// Y
  0x3003, 0x3C03, 0x3E03, 0x3303, 0x31C3, 0x30E3, 0x3033, 0x301F,
  0x300F, 0x3003,
  0x0000, 		// Z
  0x0000, 0x0000, 0x3FFF, 0x3FFF, 0x3003, 0x3003, 0x3003, 0x3003,
  0x0000, 0x0000,
  0x0000, 		// [
  0x000E, 0x001C, 0x0038, 0x0070, 0x00E0, 0x01C0, 0x0380, 0x0700,
  0x0E00, 0x1C00,
  0x1800, 		// ''
  0x0000, 0x0000, 0x3003, 0x3003, 0x3003, 0x3003, 0x3FFF, 0x3FFF,
  0x0000, 0x0000,
  0x0000, 		// ]
  0x0060, 0x0070, 0x0038, 0x001C, 0x000E, 0x0007, 0x000E, 0x001C,
  0x0038, 0x0070,
  0x0060, 		// ^
  0xC000, 0xC000, 0xC000, 0xC000, 0xC000, 0xC000, 0xC000, 0xC000,
  0xC000, 0xC000,
  0xC000, 		// _
  0x0000, 0x0000, 0x0000, 0x0000, 0x003E, 0x007E, 0x004E, 0x0000,
  0x0000, 0x0000,
  0x0000, 		// `
  0x1C00, 0x3E40, 0x3360, 0x3360, 0x3360, 0x3360, 0x3360, 0x3360,
  0x3FE0, 0x3FC0,
  0x0000, 		// a
  0x3FFF, 0x3FFF, 0x30C0, 0x3060, 0x3060, 0x3060, 0x3060, 0x38E0,
  0x1FC0, 0x0F80,
  0x0000, 		// b
  0x0F80, 0x1FC0, 0x38E0, 0x3060, 0x3060, 0x3060, 0x3060, 0x3060,
  0x18C0, 0x0880,
  0x0000, 		// c
  0x0F80, 0x1FC0, 0x38E0, 0x3060, 0x3060, 0x3060, 0x30E0, 0x30C0,
  0x3FFF, 0x3FFF,
  0x0000, 		// d
  0x0F80, 0x1FC0, 0x3BE0, 0x3360, 0x3360, 0x3360, 0x3360, 0x3360,
  0x13C0, 0x0180,
  0x0000, 		// e
  0x00C0, 0x00C0, 0x3FFC, 0x3FFE, 0x00C7, 0x00C3, 0x00C3, 0x0003,
  0x0000, 0x0000,
  0x0000, 		// f
  0x0380, 0xC7C0, 0xCEE0, 0xCC60, 0xCC60, 0xCC60, 0xCC60, 0xE660,
  0x7FE0, 0x3FE0,
  0x0000, 		// g
  0x3FFF, 0x3FFF, 0x00C0, 0x0060, 0x0060, 0x0060, 0x00E0, 0x3FC0,
  0x3F80, 0x0000,
  0x0000, 		// h
  0x0000, 0x0000, 0x3000, 0x3060, 0x3FEC, 0x3FEC, 0x3000, 0x3000,
  0x0000, 0x0000,
  0x0000, 		// i
  0x0000, 0x0000, 0x6000, 0xE000, 0xC000, 0xC060, 0xFFEC, 0x7FEC,
  0x0000, 0x0000,
  0x0000, 		// j
  0x0000, 0x3FFF, 0x3FFF, 0x0300, 0x0780, 0x0FC0, 0x1CE0, 0x3860,
  0x3000, 0x0000,
  0x0000, 		// k
  0x0000, 0x0000, 0x3000, 0x3003, 0x3FFF, 0x3FFF, 0x3000, 0x3000,
  0x0000, 0x0000,
  0x0000, 		// l
  0x3FE0, 0x3FC0, 0x00E0, 0x00E0, 0x3FC0, 0x3FC0, 0x00E0, 0x00E0,
  0x3FC0, 0x3F80,
  0x0000, 		// m
  0x0000, 0x3FE0, 0x3FE0, 0x0060, 0x0060, 0x0060, 0x0060, 0x00E0,
  0x3FC0, 0x3F80,
  0x0000, 		// n
  0x0F80, 0x1FC0, 0x38E0, 0x3060, 0x3060, 0x3060, 0x3060, 0x38E0,
  0x1FC0, 0x0F80,
  0x0000, 		// o
  0xFFE0, 0xFFE0, 0x0C60, 0x1860, 0x1860, 0x1860, 0x1860, 0x1CE0,
  0x0FC0, 0x0780,
  0x0000, 		// p
  0x0780, 0x0FC0, 0x1CE0, 0x1860, 0x1860, 0x1860, 0x1860, 0x0C60,
  0xFFE0, 0xFFE0,
  0x0000, 		// q
  0x0000, 0x3FE0, 0x3FE0, 0x00C0, 0x0060, 0x0060, 0x0060, 0x0060,
  0x00E0, 0x00C0,
  0x0000, 		// r
  0x11C0, 0x33E0, 0x3360, 0x3360, 0x3360, 0x3360, 0x3F60, 0x1E40,
  0x0000, 0x0000,
  0x0000, 		// s
  0x0060, 0x0060, 0x1FFE, 0x3FFE, 0x3060, 0x3060, 0x3060, 0x3000,
  0x0000, 0x0000,
  0x0000, 		// t
  0x0FE0, 0x1FE0, 0x3800, 0x3000, 0x3000, 0x3000, 0x3000, 0x1800,
  0x3FE0, 0x3FE0,
  0x0000, 		// u
  0x0060, 0x01E0, 0x0780, 0x1E00, 0x3800, 0x3800, 0x1E00, 0x0780,
  0x01E0, 0x0060,
  0x0000, 		// v
  0x07E0, 0x1FE0, 0x3800, 0x1C00, 0x0FE0, 0x0FE0, 0x1C00, 0x3800,
  0x1FE0, 0x07E0,
  0x0000, 		// w
  0x3060, 0x38E0, 0x1DC0, 0x0F80, 0x0700, 0x0F80, 0x1DC0, 0x38E0,
  0x3060, 0x0000,
  0x0000, 		// x
  0x0000, 0x0060, 0x81E0, 0xE780, 0x7E00, 0x1E00, 0x0780, 0x01E0,
  0x0060, 0x0000,
  0x0000, 		// y
  0x3060, 0x3860, 0x3C60, 0x3660, 0x3360, 0x31E0, 0x30E0, 0x3060,
  0x3020, 0x0000,
  0x0000, 		// z
  0x0000, 0x0080, 0x01C0, 0x1FFC, 0x3F7E, 0x7007, 0x6003, 0x6003,
  0x6003, 0x0000,
  0x0000, 		// {
  0x0000, 0x0000, 0x0000, 0x0000, 0x3FFF, 0x3FFF, 0x0000, 0x0000,
  0x0000, 0x0000,
  0x0000, 		// |
  0x0000, 0x6003, 0x6003, 0x6003, 0x7007, 0x3F7E, 0x1FFC, 0x01C0,
  0x0080, 0x0000,
  0x0000, 		// }
  0x0010, 0x0018, 0x000C, 0x0004, 0x000C, 0x0018, 0x0010, 0x0018,
  0x000C, 0x0004, 0x0000 		// ~
};

