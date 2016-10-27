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
Rect rect10 = {10,10};;

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
  regionClipScreen(bounds);
}

#define numLayers 2
MovingShape layers[numLayers] = {
  {
    {100,100}, {100,100},	/* position */
    {1,2},			/* velocity */
    COLOR_ORANGE,
    &circle14,
    (void *)circleGetBounds,
    (void *)circleCheck
  }, {
    {100,100}, {100,100},	/* position */
    {1,2},			/* velocity */
    COLOR_RED,
    &rect10,
    (void *)rectGetBounds,
    (void *)rectCheck
  }
};

Region fence = {{10,40}, {SHORT_EDGE_PIXELS-10, LONG_EDGE_PIXELS-10}};

void
layersAdvance()
{
  int layer;
  for (layer = 0; layer < numLayers; layer ++)
    mshapeAdvance(&layers[layer], &fence);
}

drawLayers()
{
  int layer, layer2, row, col;
  for (layer = 0; layer < numLayers; layer ++) {
    Region bounds;
    mshapeGetBounds(&layers[layer], &bounds);
    bounds = fence;
    lcd_setArea(bounds.topLeft.axes[0], bounds.topLeft.axes[1],
		bounds.botRight.axes[0]-1, bounds.botRight.axes[1]-1);
    for (row = bounds.topLeft.axes[1]; row < bounds.botRight.axes[1]; row++) {
      for (col = bounds.topLeft.axes[0]; col < bounds.botRight.axes[0]; col++) {
	Vec2 pixelPos = {col, row};
	u_int color = COLOR_GREEN; /* background */
	for (layer2 = 0; layer2 < numLayers; layer2 ++) {
	  if ((*layers[layer2].check)(layers[layer2].object, 
				       &layers[layer2].position,
				       &pixelPos)) {
	    color = layers[layer2].color;
	    break;
	  }
	} // for checking all layers at col, row
	lcd_writeColor(color); 
      } // for col
    } // for row
  } // for layer being rendered
}	  
    




main()
{
  configureClocks();
  lcd_init();

  clearScreen(COLOR_BLUE);
  drawString5x7(20,20, "hello", COLOR_GREEN, COLOR_RED);
  makeCircle14();
  drawLayers();
}
