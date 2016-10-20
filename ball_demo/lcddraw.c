#include "lcddraw.h"

/**
 * Draw single pixel at x,y
 * Adapted from RobG's EduKit
 **/
void drawPixel(u_char x, u_char y, u_int color) {
  colorBGR = lcd_rgb_to_bgr(color);
  u_char colorHi = colorBGR >> 8;
  lcd_setArea(x, y, x, y);
  lcd_writeData(colorHi);
  lcd_writeData(colorBGR);
}

/////////////////////////
// Fill rectangle
// Adapted from RobG's EduKit
/////////////////////////
void fillRect(u_char xMin, u_char yMin, u_char width, u_char height, 
	      u_int color)
{
  colorBGR = lcd_rgb_to_bgr(color);
  u_char colorHi = colorBGR >> 8;
  u_char xLimit = xMin + width, yLimit = yMin + height;
  lcd_setArea(xStart, yStart, xLimit - 1, yLimit - 1);
  u_int total = width * height;
  u_int c = 0;
  while ((c++) < total) {
    lcd_writeData(colorHi);
    lcd_writeData(colorBGR);
  }
}

/**
 * Clear screen (fill with color)
 **/
void clearScreen(u_int color) 
{
  u_char w = lcd_getScreenWidth();
  u_char h = lcd_getScreenHeight();
  fillRectangle(0, 0, w, h, lcd_rgbToBgr(color));
}

/**
 * Draw string at x,y
 * Type:
 * FONT_SM - small (5x8,) FONT_MD - medium (8x12,) FONT_LG - large (11x16)
 * FONT_SM_BKG, FONT_MD_BKG, FONT_LG_BKG - as above, but with background color
 * Adapted from RobG's EduKit
 **/
void drawString(u_char x, u_char y, char type, char *string) 
{
  u_char xs = x;
  while (*string) {
    drawChar5x7(xs, y, *string++);
    xs += 6;
  }
}

//////////////////////////////////////////////////////
// 5x7 font - this function draws background pixels
// Adapted from RobG's EduKit
//////////////////////////////////////////////////////
void drawChar5x7(u_char x, u_char y, char c, 
		 u_int fgColor, u_int bgColor) {
  u_char col = 0;
  u_char row = 0;
  u_char bit = 0x01;
  u_char oc = c - 0x20;
  union {
    u_char colorBytes[2];
    u_int colorWord;
  } fgColorU, bgColorU, colorU;
  fgColorU.colorWord = fgColor;
  bgColorU.colorWord = bgColor;
  
  lcd_setArea(x, y, x + 4, y + 7); 
  while (row < 8) {
    while (col < 5) {
      colorU = (font_5x7[oc][col] & bit) ? fgColorU : bgColorU;
      lcd_writeData(colorU.colorBytes[1]);
      lcd_writeData(colorU.colorBytes[0]);
      col++;
    }
    col = 0;
    bit <<= 1;
    row++;
  }
}

/////////////////////////////////////////////////////
// Draw rectangle
/////////////////////////////////////////////////////
void drawRectOutline(u_char xMin, u_char yMin, u_char width, u_char height,
		     u_int color)
{
  /* top & bot */
  fillRect(xMin, yMin, width, 1, color);
  fillRect(xMin, yMin + height, width, 1, color);

  /* left & right */
  fillRect(xMin, yMin, 1, height, color);
  fillRect(xMin + width, yMin, 1, height, color);
}

///////////////////////////////////////////
// build table chordVec[d] of circle 1/2 widths as distances d from center
// Code adapted from RobG's EduKit
// Uses Bresenham's circle algorithm
///////////////////////////////////////////
void computeChordVec(u_char chordVec[], u_char radius) 
{
  int dx = radius;
  int dy = 0;
  int xChange = 1 - 2 * radius;
  int yChange = 1;
  int radiusError = 0;
  while (dx >= dy) {
    chordVec[dy] = dx;
    chordVec[dx] = dy;
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

