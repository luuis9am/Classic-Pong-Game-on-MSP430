#include "lcdutils.h"
#include "lcddraw.h"

/**
 * Draw single pixel at x,row
 * Adapted from RobG's EduKit
 **/
void drawPixel(u_char col, u_char row, u_int colorRGB) 
{
  lcd_setArea(col, row, col, row);
  lcd_writeColor(lcd_rgbToBgr(colorRGB));
}

/////////////////////////
// Fill rectangle
// Adapted from RobG's EduKit
/////////////////////////
void fillRectangle(u_char colMin, u_char rowMin, u_char width, u_char height, 
		   u_int colorRGB)
{
  u_int colorBGR = lcd_rgbToBgr(colorRGB);
  u_char colLimit = colMin + width, rowLimit = rowMin + height;
  lcd_setArea(colMin, rowMin, colLimit - 1, rowLimit - 1);
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
 * Draw string at col,row
 * Type:
 * FONT_SM - small (5x8,) FONT_MD - medium (8x12,) FONT_LG - large (11x16)
 * FONT_SM_BKG, FONT_MD_BKG, FONT_LG_BKG - as above, but with background color
 * Adapted from RobG's EduKit
 **/
void drawString5x7(u_char col, u_char row, char *string,
		u_int fgColorRGB, u_int bgColorRGB)
{
  u_char cols = col;
  while (*string) {
    drawChar5x7(cols, row, *string++, fgColorRGB, bgColorRGB);
    cols += 6;
  }
}

//////////////////////////////////////////////////////
// 5x7 font - this function draws background pixels
// Adapted from RobG's EduKit
//////////////////////////////////////////////////////
void drawChar5x7(u_char rcol, u_char rrow, char c, 
		 u_int fgColorRGB, u_int bgColorRGB) 
{
  u_char col = 0;
  u_char row = 0;
  u_char bit = 0x01;
  u_char oc = c - 0x20;

  u_int fgColorBGR = lcd_rgbToBgr(fgColorRGB);
  u_int bgColorBGR = lcd_rgbToBgr(bgColorRGB);
  
  lcd_setArea(rcol, rrow, rcol + 4, rrow + 7); /* relative to requested col/row */
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
void drawRectOutline(u_char colMin, u_char rowMin, u_char width, u_char height,
		     u_int colorRGB)
{
  /* top & bot */
  fillRectangle(colMin, rowMin, width, 1, colorRGB);
  fillRectangle(colMin, rowMin + height, width, 1, colorRGB);

  /* left & right */
  fillRectangle(colMin, rowMin, 1, height, colorRGB);
  fillRectangle(colMin + width, rowMin, 1, height, colorRGB);
}

///////////////////////////////////////////
// build table chordVec[d] of circle 1/2 widths at distances d from center
// Code adapted from RobG's EduKit
// Uses Bresenham's circle algorithm
///////////////////////////////////////////
void computeChordVec(u_char chordVec[], u_char radius) 
{
  int col = radius, row = 0;	/* first coordinate (radius, 0) */

  // key insight: (col+1)**2 - col**2 = 2col+1

  int dColSquared = 2 * col - 1;  // change in col**2 for a unit decrease in col
  int dRowSquared = 1;	    // change in row**2 for a unit increase in row

  int radiusSqErr = 0;		/* (radius, 0) is on the circle  */
  int colPrev = 0;		/* initially bogus value  to force first entry*/
  while (col >= row) {		/* only sweep first octant */
    chordVec[row] = col;      /* row always changes in first octant */

    /* mirror into 2nd octant */
    if (colPrev != col)		/* col sometimes repeats in first octant */
      chordVec[col] = row;	/* only save first (max) col for row */
    colPrev = col;

    row++;			/* move vertically (slope <= -1 for first octant) */
    radiusSqErr += dRowSquared;	/* current radiusSqErr */
    dRowSquared += 2; 		/* next dRowSquared */
    if ((2 * radiusSqErr) > dColSquared) { /* only update col if error reduced */
      col--;			/* move horizontally */
      radiusSqErr -= dColSquared;	/* current radiusSqErr */
      dColSquared -= 2;	      /* next dColSquared */
    }
  }
}

