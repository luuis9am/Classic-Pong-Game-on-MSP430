#include "shape.h"

void
vec2Max(Vec2 *vecMax, Vec2 *v1, Vec2 *v2)
{
  u_char axis;
  for (axis = 0; axis < 2; axis ++) {
    int val1 = v1->axes[axis], val2 = v2->axes[axis];
    vecMax->axes[axis] = val1 > val2 ? val1 : val2;
  }
}

void
vec2Min(Vec2 *vecMin, Vec2 *v1, Vec2 *v2)
{
  u_char axis;
  for (axis = 0; axis < 2; axis ++) {
    int val1 = v1->axes[axis], val2 = v2->axes[axis];
    vecMin->axes[axis] = val1 < val2 ? val1 : val2;
  }
}

void 
vec2Add(Vec2 *result, Vec2 *v1, Vec2 *v2)
{
  u_char axis;
  for (axis = 0; axis < 2; axis ++) {
    result->axes[axis] = v1->axes[axis] + v2->axes[axis];
  }
}

void 
vec2Sub(Vec2 *result, Vec2 *v1, Vec2 *v2)
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
    vec->axes[axis] = (val >= 0) ? val : -val;
  }
}
