#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"


main()
{
  configureClocks();
  lcd_init();
  u_char width = screenWidth, height = screenHeight;

  clearScreen(COLOR_BLUE);

  drawString5x7(20,20, "hello", COLOR_GREEN, COLOR_RED);

  fillRectangle(30,30, 60, 60, COLOR_ORANGE);
  
}
