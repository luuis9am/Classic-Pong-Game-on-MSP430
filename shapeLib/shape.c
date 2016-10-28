#include "shape.h"

Vec2 screenSize, screenCenter, vec2Unit = {1,1}, vec2Zero = {0,0};;

void
shapeInit()
{
  u_char axis;
  screenSize.axes[1] = screenHeight;
  screenSize.axes[0] = screenWidth;
  for (axis = 0; axis < 2; axis ++) 
    screenCenter.axes[axis] = screenSize.axes[axis]/2;
}

