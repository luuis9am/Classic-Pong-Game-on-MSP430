#include "shape.h"
#include "_abCircle.h"

// true if pixel is in circle centered at centerPos
int abCircleCheck(const AbCircle *circle, const Vec2 *centerPos, const Vec2 *pixel)
{
  u_char radius = circle->radius;
  int axis;
  Vec2 relPos;
  vec2Sub(&relPos, pixel, centerPos); /* vector from center to pixel */
  vec2Abs(&relPos);		      /* project to first quadrant */
  return (relPos.axes[0] <= radius && circle->chords[relPos.axes[0]] >= relPos.axes[1]);
}
  
void
abCircleGetBounds(const AbCircle *circle, const Vec2 *centerPos, Region *bounds)
{
  u_char axis, radius = circle->radius;
  for (axis = 0; axis < 2; axis ++) {
    bounds->topLeft.axes[axis] = centerPos->axes[axis] - radius;
    bounds->botRight.axes[axis] = centerPos->axes[axis] + radius;
  }
  regionClipScreen(bounds);
}

