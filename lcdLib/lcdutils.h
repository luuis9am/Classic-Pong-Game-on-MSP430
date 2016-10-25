/*
 * lcdutils.c: 
 *
 *  Created on: 10/19/2016
 *  Author: Eric Freudenthal & David Pruitt
 *  Portions derived from EduKit code by RobG
 */

#ifndef lcdutils_included
#define lcdutils_included

typedef unsigned char u_char;
typedef unsigned int u_int;
//
extern const unsigned char font_5x7[96][5];
extern const unsigned char font_8x12[95][12];
extern const unsigned int font_11x16[95][11];

extern const unsigned int colors[43];


// Orientation
#define ORIENTATION_VERTICAL			0
#define ORIENTATION_HORIZONTAL			1
#define ORIENTATION_VERTICAL_ROTATED	2
#define ORIENTATION_HORIZONTAL_ROTATED	3

void lcd_init();
void lcd_setOrientation(u_char orientation);
u_char lcd_getScreenWidth();
u_char lcd_getScreenHeight();
void lcd_setArea(u_char colStart, u_char rowStart, u_char colEnd, u_char rowEnd);
void lcd_writeColor(u_int colorBGR);

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

#endif /* lcdutils_included */
