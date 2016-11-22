#include "shape.h"

// true if pixel is in rect centerPosed at rectPos
int 
abRectCheck(const AbRect *rect, const Vec2 *centerPos, const Vec2 *pixel)
{
  Region bounds;
  abRectGetBounds(rect, centerPos, &bounds);
  int within = 1, axis;
  for (axis = 0; axis < 2; axis ++) {
    int p = pixel->axes[axis];
    if (p > bounds.botRight.axes[axis] || p < bounds.topLeft.axes[axis])
      within = 0;
  }
  return within;
}

// compute bounding box in screen coordinates for rect at centerPos
void abRectGetBounds(const AbRect *rect, const Vec2 *centerPos, Region *bounds)
{
  vec2Sub(&bounds->topLeft, centerPos, &rect->halfSize);
  vec2Add(&bounds->botRight, centerPos, &rect->halfSize);
}



// true if pixel is in rect centerPosed at rectPos
int 
abRectOutlineCheck(const AbRectOutline *rect, const Vec2 *centerPos, const Vec2 *pixel)
{
  Region bounds;
  abRectOutlineGetBounds(rect, centerPos, &bounds);
  int col = pixel->axes[0], row = pixel->axes[1];
  return (
	  ((col == bounds.topLeft.axes[0] || col == bounds.botRight.axes[0])
	   && 
	   (row >= bounds.topLeft.axes[1] && row <= bounds.botRight.axes[1]))
	  ||
	  ((row == bounds.topLeft.axes[1] || row == bounds.botRight.axes[1])
	   &&
	   (col >= bounds.topLeft.axes[0] && col <= bounds.botRight.axes[0]))
	  );
}
 
// compute bounding box in screen coordinates for rect at centerPos
void abRectOutlineGetBounds(const AbRectOutline *rect, const Vec2 *centerPos, Region *bounds)
{
  vec2Sub(&bounds->topLeft, centerPos, &rect->halfSize);
  vec2Add(&bounds->botRight, centerPos, &rect->halfSize);
}



