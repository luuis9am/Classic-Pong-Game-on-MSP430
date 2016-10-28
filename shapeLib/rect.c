#include "shape.h"

// true if pixel is in rect centerPosed at rectPos
int 
abRectCheck(AbRect *rect, Vec2 *centerPos, Vec2 *pixel)
{
  Region bounds;
  abRectGetBounds(rect, centerPos, &bounds);
  int within = 1, axis;
  for (axis = 0; axis < 2; axis ++) {
    int p = pixel->axes[axis];
    if (p >= bounds.botRight.axes[axis] || p < bounds.topLeft.axes[axis])
      within = 0;
  }
  return within;
}

// compute bounding box in screen coordinates for rect at centerPos
void abRectGetBounds(AbRect *rect, Vec2 *centerPos, Region *bounds)
{
  vec2Sub(&bounds->topLeft, centerPos, &rect->halfSize);
  vec2Add(&bounds->botRight, centerPos, &rect->halfSize);
}

  
