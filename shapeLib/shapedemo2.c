#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "shape.h"

static AbCircle circle14;

void makeCircle14()
{
  static u_char chords14[15];	/* for a circle of radius 14 */
  computeChordVec(chords14, 14);
  circle14.radius = 14;
  circle14.chords = chords14;
  circle14.check = abCircleCheck;
  circle14.getBounds = abCircleGetBounds;
}  

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
  (AbShape *)&circle14,
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
  
  makeCircle14();
  drawLayers(&layer0);
  
  //  abDrawPos((AbShape*)&circle14, &rectPos, COLOR_ORANGE, COLOR_BLUE);
  //  abDrawPos((AbShape*)&rect10, &circlePos, COLOR_RED, COLOR_BLUE);
  //  drawCircle();
  //  drawRect();
}


