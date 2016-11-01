#include "shape.h"

void
vec2Max(Vec2 *vecMax, const Vec2 *v1, const Vec2 *v2)
{
  u_char axis;
  for (axis = 0; axis < 2; axis ++) {
    int val1 = v1->axes[axis], val2 = v2->axes[axis];
    vecMax->axes[axis] = val1 > val2 ? val1 : val2;
  }
}

void
vec2Min(Vec2 *vecMin, const Vec2 *v1, const Vec2 *v2)
{
  u_char axis;
  for (axis = 0; axis < 2; axis ++) {
    int val1 = v1->axes[axis], val2 = v2->axes[axis];
    vecMin->axes[axis] = val1 < val2 ? val1 : val2;
  }
}

void 
vec2Add(Vec2 *result, const Vec2 *v1, const Vec2 *v2)
{
  u_char axis;
  for (axis = 0; axis < 2; axis ++) {
    result->axes[axis] = v1->axes[axis] + v2->axes[axis];
  }
}

void 
vec2Sub(Vec2 *result, const Vec2 *v1, const Vec2 *v2)
{
  u_char axis;
  for (axis = 0; axis < 2; axis ++) {
    result->axes[axis] = v1->axes[axis] - v2->axes[axis];
  }
}

void 
vec2Abs(Vec2 *vec)
{
  u_char axis;
  for (axis = 0; axis < 2; axis ++) {
    int val = vec->axes[axis];
    if (val < 0)
      vec->axes[axis] = -val;
  }
}
