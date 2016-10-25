#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"

static u_char chords14[15];	/* for a circle of radius 14 */

fillCircle(u_char col, u_char row, u_char radius, u_char chords[], u_int color)
{
  u_char drow;
  for (drow = 0; drow < radius; drow++) {
    u_char dcol = chords[drow];
    u_char width = 1 + (dcol << 1);
    fillRectangle(col-dcol, row+drow, width, 1, color);
    fillRectangle(col-dcol, row-drow, width, 1, color);
  }
}

main()
{
  configureClocks();
  lcd_init();
  u_char width = lcd_getScreenWidth(), height = lcd_getScreenHeight();


  clearScreen(COLOR_BLUE);
  drawString5x7(20,20, "hello", COLOR_GREEN, COLOR_RED);

  
  computeChordVec(chords14, 14);
  fillCircle(width>>1, height>>1, 14, chords14, COLOR_ORANGE);
}
