#include "msp430.h"
#include "libTimer.h"
#include "lcdutils.h"
#include "lcddraw.h"

#define ARENA_WIDTH 100
#define ARENA_HEIGHT 50
#define RADIUS 14

u_char LOWER_BOUNDARY, UPPER_BOUNDARY, LEFT_BOUNDARY, RIGHT_BOUNDARY; /* Boundaries for arena */
u_char width, height;       /* screen width and height */
u_char chords14[RADIUS+1];	/* for a circle of radius 14 */

u_char px, py;        /* position coordinates of ball */
signed int deltaX = 1, deltaY = 1;
u_char count = 0;    

void drawArena()
{
  drawRectOutline(LEFT_BOUNDARY, LOWER_BOUNDARY, ARENA_WIDTH, ARENA_HEIGHT, COLOR_BLACK);
}

fillCircle(u_char x, u_char y, u_char radius, u_char chords[], u_int color)
{
  u_char dy;
  for (dy = 0; dy < radius; dy++) {
    u_char dx = chords[dy];
    u_char width = 1 + (dx << 1);
    fillRectangle(x-dx, y+dy, width, 1, color);
    fillRectangle(x-dx, y-dy, width, 1, color);
  }
}

main()
{
  configureClocks();
  enableWDTInterrupts();      /* enable periodic interrupt */
  lcd_init();
  width = lcd_getScreenWidth(), height = lcd_getScreenHeight();
  u_char width_offset = ARENA_WIDTH>>1, height_offset = ARENA_HEIGHT>>1;
  
  LOWER_BOUNDARY = (height>>1) - height_offset;
  UPPER_BOUNDARY = (height>>1) + height_offset;
  LEFT_BOUNDARY = (width>>1) - width_offset;
  RIGHT_BOUNDARY = (width>>1) + width_offset;
  
  px = (width>>1);
  py = (height>>1);
  
  clearScreen(COLOR_BLUE);
  drawString5x7((width>>1) - 20, 20, "Arena", COLOR_GREEN, COLOR_RED);
  
  drawArena();
  fillCircle(px, py, RADIUS, chords14, COLOR_RED);
  computeChordVec(chords14, 14);
  
  or_sr(0x18);  /* CPU off, GIE on */
}

void update_ball() 
{
  u_char px_new = px + deltaX;
  u_char py_new = py + deltaY;
  
  if (px_new - RADIUS <= LEFT_BOUNDARY || (px_new + RADIUS >= RIGHT_BOUNDARY))
    deltaX = -deltaX;
  
  if (py_new - RADIUS <= LOWER_BOUNDARY || py_new + RADIUS >= UPPER_BOUNDARY)
    deltaY = -deltaY;
  
  px = px_new + deltaX;
  py = py_new + deltaY;
}

__interrupt(WDT_VECTOR) WDT()
{  
  drawArena();
  if (++count == 10) {
    fillCircle(px, py, RADIUS, chords14, COLOR_BLUE);
    update_ball();
    fillCircle(px, py, RADIUS, chords14, COLOR_RED);
    count = 0;
  }
}
