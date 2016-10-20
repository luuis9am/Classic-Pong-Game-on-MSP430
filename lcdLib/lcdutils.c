#include "lcdutils.h"
#include "msp430.h"

/*
 * lcdutils.c: 
 *
 *  Created on: 10/19/2016
 *  Author: Eric Freudenthal & David Pruitt
 *  Derived from EduKit code by RobG
 */


u_char _orientation = 0;

//
// Chip select: P1.0
// Data/Cmd: P1.4
// Buzzer: P2.6 (default)

//
// LCD pin definitions
//
// SCLK & MOSI
#define LCD_SPI_OUT		P1OUT
#define LCD_SPI_DIR		P1DIR
#define LCD_SPI_SEL		P1SEL
#define LCD_SPI_SEL2	P1SEL2
#define LCD_SCLK_PIN	BIT5
#define LCD_MOSI_PIN	BIT7
// Chip select
#define LCD_CS_PIN	BIT0
#define LCD_CS_DIR	P1DIR
#define LCD_CS_OUT	P1OUT
// CS convenience defines
#define LCD_SELECT() LCD_CS_OUT &= ~LCD_CS_PIN
#define LCD_DESELECT()
//LCD_CS_OUT |= LCD_CS_PIN

// Data/command
#define LCD_DC_PIN	BIT4
#define LCD_DC_DIR	P1DIR
#define LCD_DC_OUT	P1OUT
// D/C convenience defines
#define LCD_DC_LO() LCD_DC_OUT &= ~LCD_DC_PIN
#define LCD_DC_HI() LCD_DC_OUT |= LCD_DC_PIN

//
// LCD driver IC specific defines
//
#define SWRESET							0x01
#define	SLEEPOUT						0x11
#define DISPON							0x29
#define CASETP							0x2A
#define PASETP							0x2B
#define RAMWRP							0x2C
#define	MADCTL							0x36
#define	COLMOD							0x3A
#define GMCTRP1							0xE0
#define GMCTRN1							0xE1

/**
 * Set up onboard LCD's SPI and control pins
 **/
static void setUpSPIforLCD() {
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

// Screen dimensions

/**
 * Get screen dimensions
 **/
#define LONG_EDGE_PIXELS				160
#define SHORT_EDGE_PIXELS				132

u_char lcd_getScreenWidth() {
  if (_orientation == ORIENTATION_VERTICAL
      || _orientation == ORIENTATION_VERTICAL_ROTATED)
    return SHORT_EDGE_PIXELS;
  else
    return LONG_EDGE_PIXELS;
}
u_char lcd_getScreenHeight() {
  if (_orientation == ORIENTATION_VERTICAL
      || _orientation == ORIENTATION_VERTICAL_ROTATED)
    return LONG_EDGE_PIXELS;
  else
    return SHORT_EDGE_PIXELS;
}

/**
 * Write data to LCD 
 **/
void lcd_writeData(u_char data) 
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
 * Set area to draw to 
 **/
void setArea(u_char xStart, u_char yStart, u_char xEnd, u_char yEnd) 
{
	_writeCommand(CASETP);
	lcd_writeData(0);
	lcd_writeData(xStart);
	lcd_writeData(0);
	lcd_writeData(xEnd);
	_writeCommand(PASETP);
	lcd_writeData(0);
	lcd_writeData(yStart);
	lcd_writeData(0);
	lcd_writeData(yEnd);
	_writeCommand(RAMWRP);
}

/**
 * Initialize onboard LCD
 **/
void lcd_init() 
{
  setUpSPIforLCD();
  _writeCommand(SWRESET); //software reset
  _delay(20);
  _writeCommand(SLEEPOUT); //exit sleep
  _delay(20);
  _writeCommand(COLMOD); //Set Color Format 16bit
  lcd_writeData(0x05);
  _writeCommand(DISPON); //display ON
  setOrientation(ORIENTATION_VERTICAL_ROTATED);
}

/**
 * Change LCD's orientation
 * One of 4 possible values:
 * ORIENTATION_VERTICAL, ORIENTATION_HORIZONTAL, 
 * ORIENTATION_VERTICAL_ROTATED, ORIENTATION_HORIZONTAL_ROTATED
 **/
void lcd_setOrientation(u_char orientation) 
{
  _writeCommand(MADCTL);
  switch (orientation) {
  case ORIENTATION_HORIZONTAL:
    lcd_writeData(0x68);
    break;
  case ORIENTATION_VERTICAL_ROTATED:
    lcd_writeData(0x08);
    break;
  case ORIENTATION_HORIZONTAL_ROTATED:
    lcd_writeData(0xA8);
    break;
  default:
    lcd_writeData(0xC8);
  }
  _orientation = orientation;
}

u_int lcd_rgbToBgr(u_int rgbColor)
{
  u_int bgrColor = rgbColor & COLOR_GREEN; /* g in same bits! */
  bgrColor |= rgbColor >> 11; 	/* r to b */
  bgrColor |= (rgbColor << 11);	/* b to r */
  return bgrColor;
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


