#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "shape.h"

AbRect rect10 = {abRectGetBounds, abRectCheck, 10,10};;


Region fence = {{10,30}, {SHORT_EDGE_PIXELS-10, LONG_EDGE_PIXELS-10}};


#define numLayers 2
Layer layer1 = {
  (AbShape *)&rect10,
  {screenWidth/2, screenHeight/2},{screenWidth/2, screenHeight/2}, /* position */
  COLOR_RED,
  0,
};
Layer layer0 = {
  (AbShape *)&rect10,
  {(screenWidth/2)+10, (screenHeight/2)+5}, /* position */
  {(screenWidth/2)+10, (screenHeight/2)+5}, 
  COLOR_ORANGE,
  &layer1,
};


    

u_int bgColor = COLOR_BLUE;

main()
{
  configureClocks();
  lcd_init();
  shapeInit();
  Vec2 rectPos = screenCenter, circlePos = {30,screenHeight - 30};

  clearScreen(COLOR_BLUE);
  drawString5x7(20,20, "hello", COLOR_GREEN, COLOR_RED);
  shapeInit();
  
  layerDraw(&layer0);
  
}


