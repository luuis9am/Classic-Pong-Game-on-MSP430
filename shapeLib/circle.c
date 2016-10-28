#include "shape.h"


// true if pixel is in circle centered at circlePos
int circleCheck(Circle *circle, Vec2 *circlePos, Vec2 *pixel)
{
  u_char radius = circle->radius;
  int axis;
  Vec2 relPos;
  vec2Sub(&relPos, pixel, circlePos); /* vector from center to pixel */
  vec2Abs(&relPos);		      /* project to first quadrant */
  return (relPos.axes[0] <= radius && circle->chords[relPos.axes[0]] >= relPos.axes[1]);
}
  
void
circleGetBounds(Circle *circle, Vec2 *circlePos, Region *bounds)
{
  u_char axis, radius = circle->radius;
  for (axis = 0; axis < 2; axis ++) {
    bounds->topLeft.axes[axis] = circlePos->axes[axis] - radius;
    bounds->botRight.axes[axis] = circlePos->axes[axis] + radius;
  }
  regionClipScreen(bounds);
}

