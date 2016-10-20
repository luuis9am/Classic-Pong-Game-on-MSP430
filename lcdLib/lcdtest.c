#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"

main()
{
  configureClocks();
  lcd_init();
  clearScreen(COLOR_ORANGE);
  drawString5x7(20,20, "hello", COLOR_GREEN, COLOR_ORANGE);
}
