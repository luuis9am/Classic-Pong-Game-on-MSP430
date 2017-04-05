#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "shape.h"

AbRect rect10 = {abRectGetBounds, abRectCheck, 10,10};
AbRArrow arrow30 = {abRArrowGetBounds, abRArrowCheck, 30};


Region fence = {{10,30}, {SHORT_EDGE_PIXELS-10, LONG_EDGE_PIXELS-10}};


Layer layer2 = {
  (AbShape *)&arrow30,
  {screenWidth/2+40, screenHeight/2+10}, 	    /* position */
  {0,0}, {0,0},				    /* last & next pos */
  COLOR_BLACK,
  0,
};
Layer layer1 = {
  (AbShape *)&rect10,
  {screenWidth/2, screenHeight/2}, 	    /* position */
  {0,0}, {0,0},				    /* last & next pos */
  COLOR_RED,
  &layer2,
};
Layer layer0 = {
  (AbShape *)&rect10,
  {(screenWidth/2)+10, (screenHeight/2)+5}, /* position */
  {0,0}, {0,0},				    /* last & next pos */
  COLOR_ORANGE,
  &layer1,
};


u_int bgColor = COLOR_BLUE;

int
main()
{
  configureClocks();
  lcd_init();
  shapeInit();
  Vec2 rectPos = screenCenter, circlePos = {30,screenHeight - 30};

  clearScreen(COLOR_BLUE);
  drawString5x7(20,20, "hello", COLOR_GREEN, COLOR_RED);
  shapeInit();
  
  layerInit(&layer0);
  layerDraw(&layer0);
  
}


