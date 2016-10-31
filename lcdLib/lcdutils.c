/** \file lcdutils.c: 
 * 
 *  \brief Created on: 10/19/2016
 *  Author: Eric Freudenthal & David Pruitt
 *  Derived from EduKit code by RobG
 *  Chip select: P1.0
 *  Data/Cmd: P1.4
 *  Buzzer: P2.6 (default)
 */
 
#include "lcdutils.h"
#include "msp430.h"

u_char _orientation = 0;

/** LCD pin definitions*/
/** SCLK & MOSI*/
#define LCD_SPI_OUT		P1OUT
#define LCD_SPI_DIR		P1DIR
#define LCD_SPI_SEL		P1SEL
#define LCD_SPI_SEL2	P1SEL2
#define LCD_SCLK_PIN	BIT5
#define LCD_MOSI_PIN	BIT7

/** Chip select */
#define LCD_CS_PIN	BIT0
#define LCD_CS_DIR	P1DIR
#define LCD_CS_OUT	P1OUT

/** CS convenience defines */
#define LCD_SELECT() LCD_CS_OUT &= ~LCD_CS_PIN
#define LCD_DESELECT()

/** Data/command */
#define LCD_DC_PIN	BIT4
#define LCD_DC_DIR	P1DIR
#define LCD_DC_OUT	P1OUT

/** D/C convenience defines */
#define LCD_DC_LO() LCD_DC_OUT &= ~LCD_DC_PIN
#define LCD_DC_HI() LCD_DC_OUT |= LCD_DC_PIN

/** LCD driver IC specific defines */
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

/** Set up onboard LCD's SPI and control pins */
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
  UCB0CTL0 = UCCKPH + UCMSB + UCMST + UCSYNC; /**< 3-pin, 8-bit SPI master */
  UCB0CTL1 |= UCSSEL_2; /**< SMCLK */
  UCB0BR0 |= 0x01; /**< 1:1 */
  UCB0BR1 = 0;
  UCB0CTL1 &= ~UCSWRST;
  LCD_SELECT();
}

/** Screen dimensions */

/** Write data to LCD */
static inline void 
lcd_writeData(u_char data) 
{
  while (UCB0STAT & UCBUSY);	/**< wait for previous transfer to complete */
  LCD_DC_HI();			/**< specify sending data */
  UCB0TXBUF = data;		/**< send data */
}

typedef union {
  u_char colorBytes[2];
  u_int colorBGRWord;
} ColorBGR;

void lcd_writeColor(u_int colorBGR)
{
  ColorBGR colorU = {.colorBGRWord = colorBGR};
  lcd_writeData(colorU.colorBytes[1]);
  lcd_writeData(colorU.colorBytes[0]);
}

/** Write command to LCD (private) */
void _writeCommand(u_char command) 
{
  while (UCB0STAT & UCBUSY);	/**< wait for previous transfer to complete */
  LCD_DC_LO();			          /**< specify sending a command */
  UCB0TXBUF = command;		    /**< send command */
}

/** Long delay (private) */
void _delay(u_char x10ms) {
	while (x10ms > 0) {
		__delay_cycles(160000);
		x10ms--;
	}
}

/** Set area to draw to */
void lcd_setArea(u_char colStart, u_char rowStart, u_char colEnd, u_char rowEnd) 
{
	_writeCommand(CASETP);
	lcd_writeData(0);
	lcd_writeData(colStart);
	lcd_writeData(0);
	lcd_writeData(colEnd);
	_writeCommand(PASETP);
	lcd_writeData(0);
	lcd_writeData(rowStart);
	lcd_writeData(0);
	lcd_writeData(rowEnd);
	_writeCommand(RAMWRP);
}

/** Initialize onboard LCD */
void lcd_init() 
{
  setUpSPIforLCD();
  _writeCommand(SWRESET);  /**< software reset */
  _delay(20);
  _writeCommand(SLEEPOUT); /**< exit sleep */
  _delay(20);
  _writeCommand(COLMOD);   /**< Set Color Format 16bit */
  lcd_writeData(0x05);
  _writeCommand(DISPON);   /**< display ON */

  _writeCommand(MADCTL);
  switch (ORIENTATION) {
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
}

