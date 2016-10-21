#include "lcdutils.h"
#include "lcddraw.h"

/**
 * Draw single pixel at x,y
 * Adapted from RobG's EduKit
 **/
void drawPixel(u_char x, u_char y, u_int colorRGB) 
{
  lcd_setArea(x, y, x, y);
  lcd_writeColor(lcd_rgbToBgr(colorRGB));
}

/////////////////////////
// Fill rectangle
// Adapted from RobG's EduKit
/////////////////////////
void fillRectangle(u_char xMin, u_char yMin, u_char width, u_char height, 
		   u_int colorRGB)
{
  u_int colorBGR = lcd_rgbToBgr(colorRGB);
  u_char xLimit = xMin + width, yLimit = yMin + height;
  lcd_setArea(xMin, yMin, xLimit - 1, yLimit - 1);
  u_int total = width * height;
  u_int c = 0;
  while ((c++) < total) {
    lcd_writeColor(colorBGR);
  }
}

/**
 * Clear screen (fill with color)
 **/
void clearScreen(u_int colorRGB) 
{
  u_char w = lcd_getScreenWidth();
  u_char h = lcd_getScreenHeight();
  fillRectangle(0, 0, w, h, colorRGB);
}

/**
 * Draw string at x,y
 * Type:
 * FONT_SM - small (5x8,) FONT_MD - medium (8x12,) FONT_LG - large (11x16)
 * FONT_SM_BKG, FONT_MD_BKG, FONT_LG_BKG - as above, but with background color
 * Adapted from RobG's EduKit
 **/
void drawString5x7(u_char x, u_char y, char *string,
		u_int fgColorRGB, u_int bgColorRGB)
{
  u_char xs = x;
  while (*string) {
    drawChar5x7(xs, y, *string++, fgColorRGB, bgColorRGB);
    xs += 6;
  }
}

//////////////////////////////////////////////////////
// 5x7 font - this function draws background pixels
// Adapted from RobG's EduKit
//////////////////////////////////////////////////////
void drawChar5x7(u_char x, u_char y, char c, 
		 u_int fgColorRGB, u_int bgColorRGB) 
{
  u_char col = 0;
  u_char row = 0;
  u_char bit = 0x01;
  u_char oc = c - 0x20;

  u_int fgColorBGR = lcd_rgbToBgr(fgColorRGB);
  u_int bgColorBGR = lcd_rgbToBgr(bgColorRGB);
  
  lcd_setArea(x, y, x + 4, y + 7); 
  while (row < 8) {
    while (col < 5) {
      u_int colorBGR = (font_5x7[oc][col] & bit) ? fgColorBGR : bgColorBGR;
      lcd_writeColor(colorBGR);
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
		     u_int colorRGB)
{
  /* top & bot */
  fillRectangle(xMin, yMin, width, 1, colorRGB);
  fillRectangle(xMin, yMin + height, width, 1, colorRGB);

  /* left & right */
  fillRectangle(xMin, yMin, 1, height, colorRGB);
  fillRectangle(xMin + width, yMin, 1, height, colorRGB);
}

///////////////////////////////////////////
// build table chordVec[d] of circle 1/2 widths at distances d from center
// Code adapted from RobG's EduKit
// Uses Bresenham's circle algorithm
///////////////////////////////////////////
void computeChordVec(u_char chordVec[], u_char radius) 
{
  int x = radius, y = 0;	/* first coordinate (radius, 0) */

  // key insight: (x+1)**2 - x**2 = 2x+1

  int dXSquared = 2 * x - 1;  // change in x**2 for a unit decrease in x
  int dYSquared = 1;	    // change in y**2 for a unit increase in y

  int radiusSqErr = 0;		/* (radius, 0) is on the circle  */
  int xPrev = 0;		/* initially bogus value  to force first entry*/
  while (x >= y) {		/* only sweep first octant */
    chordVec[y] = x;		/* y always changes in first octant */

    /* mirror into 2nd octant */
    if (xPrev != x)		/* x sometimes repeats in first octant */
      chordVec[x] = y;		/* only save first (max) col for y */
    xPrev = x;

    y++;			/* move vertically (slope <= -1 for first octant) */
    radiusSqErr += dYSquared;	/* current radiusSqErr */
    dYSquared += 2; 		/* next dYSquared */
    if ((2 * radiusSqErr) > dXSquared) { /* only update x if error reduced */
      x--;			/* move horizontally */
      radiusSqErr -= dXSquared;	/* current radiusSqErr */
      dXSquared -= 2;	      /* next dXSquared */
    }
  }
}

