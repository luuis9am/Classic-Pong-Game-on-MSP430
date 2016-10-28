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
#define LONG_EDGE_PIXELS				160
#define SHORT_EDGE_PIXELS				132
#define ORIENTATION_VERTICAL			0
#define ORIENTATION_HORIZONTAL			1
#define ORIENTATION_VERTICAL_ROTATED	2
#define ORIENTATION_HORIZONTAL_ROTATED	3

#ifndef ORIENTATION		/* default orientation */
#define ORIENTATION ORIENTATION_VERTICAL_ROTATED
#endif

#if (ORIENTATION == ORIENTATION_VERTICAL) || (ORIENTATION == ORIENTATION_VERTICAL_ROTATED)
# define screenWidth SHORT_EDGE_PIXELS
# define screenHeight LONG_EDGE_PIXELS
#else
# define screenHeight SHORT_EDGE_PIXELS
# define screenWidth LONG_EDGE_PIXELS
#endif

void lcd_init();
void lcd_setArea(u_char colStart, u_char rowStart, u_char colEnd, u_char rowEnd);
void lcd_writeColor(u_int colorBGR);

//
// Colors
//
#define BLACK 0x0000
#define WHITE 0xFFFF
#define COLOR_BLACK   BLACK
#define COLOR_WHITE   WHITE

#define rgb2bgr(val) ((((val) << 11)&0xf800) | ((val)&0x7e0) | (((val)>>11)&0x1f))

//
#define COLOR_BLUE	rgb2bgr(0x001F)
#define COLOR_RED     rgb2bgr(0xF800)
#define COLOR_GREEN   rgb2bgr(0x07E0)
#define COLOR_CYAN    rgb2bgr(0x07FF)
#define COLOR_MAGENTA rgb2bgr(0xF81F)
#define COLOR_YELLOW  rgb2bgr(0xffe0)
#define COLOR_ORANGE	rgb2bgr(0xFD20)
#define COLOR_ORANGE_RED	rgb2bgr(0xFA20)
#define COLOR_DARK_ORANGE	rgb2bgr(0xFC60)
#define COLOR_GRAY	rgb2bgr(0xBDF7)
#define COLOR_NAVY	rgb2bgr(0x0010)
#define COLOR_ROYAL_BLUE	rgb2bgr(0x435C)
#define COLOR_SKY_BLUE	rgb2bgr(0x867D)
#define COLOR_TURQUOISE	rgb2bgr(0x471A)
#define COLOR_STEEL_BLUE	rgb2bgr(0x4416)
#define COLOR_LIGHT_BLUE	rgb2bgr(0xAEDC)
#define COLOR_AQUAMARINE	rgb2bgr(0x7FFA)
#define COLOR_DARK_GREEN	rgb2bgr(0x0320)
#define COLOR_DARK_OLIVE_GREEN	rgb2bgr(0x5345)
#define COLOR_SEA_GREEN	rgb2bgr(0x2C4A)
#define COLOR_SPRING_GREEN	rgb2bgr(0x07EF)
#define COLOR_PALE_GREEN	rgb2bgr(0x9FD3)
#define COLOR_GREEN_YELLOW	rgb2bgr(0xAFE5)
#define COLOR_LIME_GREEN	rgb2bgr(0x3666)
#define COLOR_FOREST_GREEN	rgb2bgr(0x2444)
#define COLOR_KHAKI	rgb2bgr(0xF731)
#define COLOR_GOLD	rgb2bgr(0xFEA0)
#define COLOR_GOLDENROD	rgb2bgr(0xDD24)
#define COLOR_SIENNA	rgb2bgr(0xA285)
#define COLOR_BEIGE	rgb2bgr(0xF7BB)
#define COLOR_TAN	rgb2bgr(0xD5B1)
#define COLOR_BROWN	rgb2bgr(0xA145)
#define COLOR_CHOCOLATE	rgb2bgr(0xD343)
#define COLOR_FIREBRICK	rgb2bgr(0xB104)
#define COLOR_HOT_PINK	rgb2bgr(0xFB56)
#define COLOR_PINK	rgb2bgr(0xFE19)
#define COLOR_DEEP	rgb2bgr(0xF8B2)
#define COLOR_VIOLET	rgb2bgr(0xEC1D)
#define COLOR_DARK_VIOLET	rgb2bgr(0x901A)
#define COLOR_PURPLE	rgb2bgr(0xA11E)
#define COLOR_MEDIUM_PURPLE	rgb2bgr(0x939B)

#endif /* lcdutils_included */
