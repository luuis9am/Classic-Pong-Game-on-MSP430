#include "shape.h"


// true if pixel is in arrow whose tip is at centerPos
int 
abRArrowCheck(AbRArrow *arrow, Vec2 *centerPos, Vec2 *pixel)
{
  Vec2 relPos;
  int row, col, within = 0;
  int size = arrow->size, halfSize = size/2;
  vec2Sub(&relPos, pixel, centerPos); /* vector from center to pixel */
  row = relPos.axes[1]; col = -relPos.axes[0]; /* note that col is negated */
  if (col >= 0 && col <= size) {
    row = (row >= 0) ? row : -row; /* |row| */
    within =  ((row <= col) && (col < halfSize)) || (row == 0);
  }
}

// compute bounding box in screen coordinates for arrow with whose tip is at centerPos
void 
abRArrowGetBounds(AbRArrow *arrow, Vec2 *centerPos, Region *bounds)
{
  int size = arrow->size, halfSize = size / 2;
  bounds->topLeft.axes[0] = centerPos->axes[0] - size;
  bounds->topLeft.axes[1] = centerPos->axes[1] - halfSize;
  bounds->botRight.axes[0] = centerPos->axes[0];
  bounds->botRight.axes[1] = centerPos->axes[1] + halfSize;
}


