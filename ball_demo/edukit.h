/*
 * edukit.h
 *
 *  Created on: Aug 20, 2014
 *      Author: RobG
 */

#ifndef EDUKIT_H_
#define EDUKIT_H_
//
//#define ST7735
#define ILI9163
//
typedef unsigned char u_char;
typedef unsigned int u_int;
//
extern const unsigned char font_5x7[96][5];
extern const unsigned char font_8x12[95][12];
extern const unsigned int font_11x16[95][11];
extern const unsigned int colors[43];
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
// Font selection
// Available font sizes: 5x8, 8x12, 11x16
// When _BKG option is used, background color is also drawn
//
#define FONT_SM							0
#define FONT_MD							1
#define FONT_LG							2
#define FONT_SM_BKG						3
#define FONT_MD_BKG						4
#define FONT_LG_BKG						5
// Screen dimensions
#define LONG_EDGE_PIXELS				160
#define SHORT_EDGE_PIXELS				132
// Orientation
#define ORIENTATION_VERTICAL			0
#define ORIENTATION_HORIZONTAL			1
#define ORIENTATION_VERTICAL_ROTATED	2
#define ORIENTATION_HORIZONTAL_ROTATED	3
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
//
//
void initMSP430();
void setUpSPIforLCD();
void initLCD();
void intro();
//
void drawPixel(u_char x, u_char y);
//
void drawString(u_char x, u_char y, char type, char *string);
//
void drawCharLg(u_char x, u_char y, char c);
void drawCharMd(u_char x, u_char y, char c);
void drawCharSm(u_char x, u_char y, char c);
void drawCharLgBkg(u_char x, u_char y, char c);
void drawCharMdBkg(u_char x, u_char y, char c);
void drawCharSmBkg(u_char x, u_char y, char c);
//
void drawLine(u_char xStart, u_char yStart, u_char xEnd, u_char yEnd);
void drawRect(u_char xStart, u_char yStart, u_char xEnd, u_char yEnd);
void drawCircle(u_char x, u_char y, u_char radius);
//
void fillRect(u_char xStart, u_char yStart, u_char xEnd, u_char yEnd);
void fillCircle(u_char x, u_char y, u_char radius);
//
void drawImage(u_char x, u_char y, u_char w, u_char h, u_int * data);
void drawImageLut(u_char x, u_char y, u_char w, u_char h, u_char * data, u_int * lut);
void drawImageMono(u_char x, u_char y, u_char w, u_char h, u_char * data);
//
void setColor(u_int color);
void setBackgroundColor(u_int color);
void setOrientation(u_char orientation);
void clearScreen(u_int color);
//
u_char getScreenWidth();
u_char getScreenHeight();
//
void int2ASCII(u_int number, char * array, int scale);
//
// Colors
//
#define BLACK 0x0000
#define WHITE 0xFFFF
//
#define COLOR_BLACK   BLACK
#define COLOR_BLUE    0x001F
#define COLOR_RED     0xF800
#define COLOR_GREEN   0x07E0
#define COLOR_CYAN    0x07FF
#define COLOR_MAGENTA 0xF81F
#define COLOR_YELLOW  0xffe0
#define COLOR_WHITE   WHITE
#define COLOR_ORANGE	0xFD20
#define COLOR_ORANGE_RED	0xFA20
#define COLOR_DARK_ORANGE	0xFC60
#define COLOR_GRAY	0xBDF7
#define COLOR_NAVY	0x0010
#define COLOR_ROYAL_BLUE	0x435C
#define COLOR_SKY_BLUE	0x867D
#define COLOR_TURQUOISE	0x471A
#define COLOR_STEEL_BLUE	0x4416
#define COLOR_LIGHT_BLUE	0xAEDC
#define COLOR_AQUAMARINE	0x7FFA
#define COLOR_DARK_GREEN	0x0320
#define COLOR_DARK_OLIVE_GREEN	0x5345
#define COLOR_SEA_GREEN	0x2C4A
#define COLOR_SPRING_GREEN	0x07EF
#define COLOR_PALE_GREEN	0x9FD3
#define COLOR_GREEN_YELLOW	0xAFE5
#define COLOR_LIME_GREEN	0x3666
#define COLOR_FOREST_GREEN	0x2444
#define COLOR_KHAKI	0xF731
#define COLOR_GOLD	0xFEA0
#define COLOR_GOLDENROD	0xDD24
#define COLOR_SIENNA	0xA285
#define COLOR_BEIGE	0xF7BB
#define COLOR_TAN	0xD5B1
#define COLOR_BROWN	0xA145
#define COLOR_CHOCOLATE	0xD343
#define COLOR_FIREBRICK	0xB104
#define COLOR_HOT_PINK	0xFB56
#define COLOR_PINK	0xFE19
#define COLOR_DEEP	0xF8B2
#define COLOR_VIOLET	0xEC1D
#define COLOR_DARK_VIOLET	0x901A
#define COLOR_PURPLE	0xA11E
#define COLOR_MEDIUM_PURPLE	0x939B

#endif /* EDUKIT_H_ */
