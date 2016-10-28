#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "shape.h"

Region fence = {{10,30}, {screenWidth-10, screenHeight-10}};

int redrawScreen;			/* true when screen needs to be redrawn */

static Circle circle14;

void makeCircle14()
{
  static u_char chords14[15];	/* for a circle of radius 14 */
  computeChordVec(chords14, 14);
  circle14.radius = 14;
  circle14.chords = chords14;
}  
Rect rect10 = {10,15};;

typedef struct {
  Vec2 position, prevPosition;
  Vec2 velocity;
  u_int color;
  void *object;
  void (*getBounds)(void *shape, Vec2 *shapePos, Region *bounds);
  int (*check)(void *shape, Vec2 *shapePos, Vec2 *pixel);
} MovingShape;

mshapeAdvance(MovingShape *ms, Region *fence)
{
  Vec2 newPos;
  u_char axis;
  Region shapeBoundary;
  vec2Add(&newPos, &ms->position, &ms->velocity);
  (*ms->getBounds)(ms->object, &newPos, &shapeBoundary);
  for (axis = 0; axis < 2; axis ++) {
    if ((shapeBoundary.topLeft.axes[axis] < fence->topLeft.axes[axis]) ||
	(shapeBoundary.botRight.axes[axis] > fence->botRight.axes[axis]) ) {
      int velocity = ms->velocity.axes[axis] = -ms->velocity.axes[axis];
      newPos.axes[axis] += (2*velocity);
    }
  }
}

mshapeGetBounds(MovingShape *ms, Region *bounds)
{
  Region prevBounds, curBounds;
   (*ms->getBounds)(ms->object, &ms->position, &curBounds);
   (*ms->getBounds)(ms->object, &ms->prevPosition, &prevBounds);
   regionUnion(bounds, &curBounds, &prevBounds);
   *bounds = fence;
   regionClipScreen(bounds);
}

#define numLayers 2
MovingShape layers[] = {
  {
    {50,50}, {55,55},	/* position */
    {1,2},			/* velocity */
    COLOR_RED,
    &rect10,
    (void *)rectGetBounds,
    (void *)rectCheck
  },
  {
    {100,101}, {101,101},	/* position */
    {1,2},			/* velocity */
    COLOR_ORANGE,
    &circle14,
    (void *)circleGetBounds,
    (void *)circleCheck
  }, 
};


void
layersAdvance()
{
  int layer;
  for (layer = 0; layer < numLayers; layer ++)
    mshapeAdvance(&layers[layer], &fence);
}

void
drawLayerLoop()
{
  int layer, layer2, row, col;
  for (;;) {
    while (!redrawScreen)	/* Pause CPU if screen doesn't need updating */
      or_sr(0x10);		/* CPU OFF */
    for (layer = 0; layer < numLayers; layer ++) {
      Region bounds;
      mshapeGetBounds(&layers[layer], &bounds);
      lcd_setArea(bounds.topLeft.axes[0], bounds.topLeft.axes[1],
		  bounds.botRight.axes[0]-1, bounds.botRight.axes[1]-1);
      for (row = bounds.topLeft.axes[1]; row < bounds.botRight.axes[1]; row++) {
	for (col = bounds.topLeft.axes[0]; col < bounds.botRight.axes[0]; col++) {
	  Vec2 pixelPos = {col, row};
	  u_int color = COLOR_BLUE; /* background */
	  for (layer2 = 0; layer2 < numLayers; layer2 ++) {
	    if ((*layers[layer2].check)(layers[layer2].object, 
					&layers[layer2].position,
					&pixelPos)) {
	      color = layers[layer2].color;
	      break; 
	    } /* if check */
	  } // for checking all layers at col, row
	  lcd_writeColor(color); 
	} // for col
      } // for row
    } // for layer being rendered
  }	  
}




main()
{
  configureClocks();
  enableWDTInterrupts();      /* enable periodic interrupt */
  lcd_init();
  shapeInit();
  clearScreen(COLOR_BLUE);
  drawString5x7(20,20, "hello", COLOR_GREEN, COLOR_RED);
  makeCircle14();
  or_sr(0x8);			/* GIE (enable interrupts) */
  drawLayerLoop();
}

void wdt_c_handler()
{
  static short count = 0;
  count ++;
  if (count == 25) {
    layersAdvance();
    redrawScreen = 1;
    count = 0;
  }
}
