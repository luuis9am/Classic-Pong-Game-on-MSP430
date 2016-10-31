#include "shape.h"

Vec2 screenSize = {screenWidth, screenHeight};
Vec2 screenCenter= {screenWidth/2, screenHeight/2};
Vec2 vec2Unit = {1,1}, vec2Zero = {0,0};;

void
shapeInit()
{
  /* no longer needed */
}

void 
abShapeGetBounds(AbShape *s, Vec2 *centerPos, Region *bounds)
{
  (*s->getBounds)(s, centerPos, bounds);
}

int
abShapeCheck(AbShape *s, Vec2 *centerPos, Vec2 *pixelLoc)
{
  (*s->check)(s, centerPos, pixelLoc);
}

