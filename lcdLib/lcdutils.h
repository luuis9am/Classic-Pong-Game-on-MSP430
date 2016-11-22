/** \file lcdutils.h
 *  \brief Portions derived from EduKit code by RobG
 *  Created on: 10/19/2016
 *  Author: Eric Freudenthal & David Pruitt
 */

#ifndef lcdutils_included
#define lcdutils_included

typedef unsigned char u_char;
typedef unsigned int u_int;

extern const unsigned char font_5x7[96][5];
extern const unsigned char font_8x12[95][12];
extern const unsigned int font_11x16[95][11];

extern const unsigned int colors[43];


/** Orientation */
#define LONG_EDGE_PIXELS				160
#define SHORT_EDGE_PIXELS				128
#define ORIENTATION_VERTICAL			0
#define ORIENTATION_HORIZONTAL			1
#define ORIENTATION_VERTICAL_ROTATED	2
#define ORIENTATION_HORIZONTAL_ROTATED	3

/** Default Orientation */
#ifndef ORIENTATION		
#define ORIENTATION ORIENTATION_VERTICAL_ROTATED
#endif

#if (ORIENTATION == ORIENTATION_VERTICAL) || (ORIENTATION == ORIENTATION_VERTICAL_ROTATED)
# define screenWidth SHORT_EDGE_PIXELS
# define screenHeight LONG_EDGE_PIXELS
#else
# define screenHeight SHORT_EDGE_PIXELS
# define screenWidth LONG_EDGE_PIXELS
#endif

/** Initialize the onboard LCD */
void lcd_init();

/** Set area to draw to
 *  
 *  \param colStart Start column of the area
 *  \param rowStart Start row of the area
 *  \param colEnd End column of the area
 *  \param rowEnd End row of the area
 */
void lcd_setArea(u_char colStart, u_char rowStart, u_char colEnd, u_char rowEnd);

/** Write color to LCD
 *
 *  \param colorBGR The color in BGR
 */
void lcd_writeColor(u_int colorBGR);

#define rgb2bgr(val) ((((val) << 11)&0xf800) | ((val)&0x7e0) | (((val)>>11)&0x1f))

/** Colors */
#define BLACK 0x0000
#define WHITE 0xFFFF
#define COLOR_BLACK   BLACK
#define COLOR_WHITE   WHITE

#define COLOR_BLUE              0xf800
#define COLOR_RED 		0x001f
#define COLOR_GREEN   		0x07e0
#define COLOR_CYAN    		0xffe0
#define COLOR_MAGENTA 		0xf81f
#define COLOR_YELLOW  		0x07ff
#define COLOR_ORANGE		0x053f
#define COLOR_ORANGE_RED	0x023f
#define COLOR_DARK_ORANGE	0x047f
#define COLOR_GRAY		0xbdf7
#define COLOR_NAVY		0x8000
#define COLOR_ROYAL_BLUE	0xe348
#define COLOR_SKY_BLUE		0xee70
#define COLOR_TURQUOISE		0xd708
#define COLOR_STEEL_BLUE	0xb408
#define COLOR_LIGHT_BLUE	0xe6d5
#define COLOR_AQUAMARINE	0xd7ef
#define COLOR_DARK_GREEN	0x0320
#define COLOR_DARK_OLIVE_GREEN	0x2b4a
#define COLOR_SEA_GREEN		0x5445
#define COLOR_SPRING_GREEN	0x7fe0
#define COLOR_PALE_GREEN	0x9fd3
#define COLOR_GREEN_YELLOW	0x2ff5
#define COLOR_LIME_GREEN	0x3666
#define COLOR_FOREST_GREEN	0x2444
#define COLOR_KHAKI		0x8f3e
#define COLOR_GOLD		0x06bf
#define COLOR_GOLDENROD		0x253b
#define COLOR_SIENNA		0x2a94
#define COLOR_BEIGE		0xdfbe
#define COLOR_TAN		0x8dba
#define COLOR_BROWN		0x2954
#define COLOR_CHOCOLATE		0x1b5a
#define COLOR_FIREBRICK		0x2116
#define COLOR_HOT_PINK		0xb35f
#define COLOR_PINK		0xce1f
#define COLOR_DEEP		0x90bf
#define COLOR_VIOLET		0xec1d
#define COLOR_DARK_VIOLE	0xd012
#define COLOR_PURPLE		0xf114
#define COLOR_MEDIUM_PURPLE	0xdb92

#endif /* lcdutils_included */
