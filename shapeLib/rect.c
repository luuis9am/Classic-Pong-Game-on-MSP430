#include "shape.h"

// true if pixel is in rect centered at rectPos
int 
rectCheck(Rect *rect, Vec2 *rectPos, Vec2 *pixel)
{
  Region bounds;
  rectGetBounds(rect, rectPos, &bounds);
  int within = 1, axis;
  for (axis = 0; axis < 2; axis ++) {
    int p = pixel->axes[axis];
    if (p >= bounds.botRight.axes[axis] || p < bounds.topLeft.axes[axis])
      within = 0;
  }
  return within;
}

// compute bounding box in screen coordinates for rect centered at rectPos
void rectGetBounds(Rect *rect, Vec2 *rectPos, Region *bounds)
{
  vec2Sub(&bounds->topLeft, rectPos, &rect->halfSize);
  vec2Add(&bounds->botRight, rectPos, &rect->halfSize);
}

  
