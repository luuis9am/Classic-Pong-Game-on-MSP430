#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "shape.h"

static Circle circle14;

void makeCircle14()
{
  static u_char chords14[15];	/* for a circle of radius 14 */
  computeChordVec(chords14, 14);
  circle14.radius = 14;
  circle14.chords = chords14;
}  

drawCircle()
{
  u_char row, col;
  Region bounds;
  makeCircle14();
  circleGetBounds(&circle14, &screenCenter, &bounds);
  lcd_setArea(bounds.topLeft.axes[0], bounds.topLeft.axes[1],
	      bounds.botRight.axes[0]-1, bounds.botRight.axes[1]-1);
  for (row = bounds.topLeft.axes[1]; row < bounds.botRight.axes[1]; row++) {
    for (col = bounds.topLeft.axes[0]; col < bounds.botRight.axes[0]; col++) {
      Vec2 pos = {col, row};
      int color = circleCheck(&circle14, &screenCenter, &pos) ?
	COLOR_RED : COLOR_BLUE;
      lcd_writeColor(color);
    }
  }
}


Rect rect10 = {10,10};;

drawRect()
{
  u_char row, col;
  Region bounds;
  Vec2 rectPos, offset = {0, +30};	/* 0 across, 30 pixels down */
  vec2Add(&rectPos, &screenCenter, &offset); /* 30 pixels below center */
  rectGetBounds(&rect10, &rectPos, &bounds);
  lcd_setArea(bounds.topLeft.axes[0], bounds.topLeft.axes[1],
	      bounds.botRight.axes[0]-1, bounds.botRight.axes[1]-1);
  for (row = bounds.topLeft.axes[1]; row < bounds.botRight.axes[1]; row++) {
    for (col = bounds.topLeft.axes[0]; col < bounds.botRight.axes[0]; col++) {
      Vec2 pixelPos = {col, row};
      int color = rectCheck(&rect10, &rectPos, &pixelPos) ?
	COLOR_ORANGE : COLOR_BLUE;
      lcd_writeColor(color);
    }
  }
}




typedef struct {
  Vec2 position;
  Vec2 velocity;
  u_int color;
  void (*getBounds)(void *shape, Vec2 *shapePos, Region *bounds);
  int (*check)(void *shape, Vec2 *shapePos, Vec2 *pixel);
} MovingShape;




main()
{
  configureClocks();
  lcd_init();

  clearScreen(COLOR_BLUE);
  drawString5x7(20,20, "hello", COLOR_GREEN, COLOR_RED);
  shapeInit();
  drawCircle();
  drawRect();
}
