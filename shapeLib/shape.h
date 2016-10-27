
#ifndef shape_included
#define shape_included

#include "lcdutils.h"


typedef struct {
  int axes[2];
} Vec2;

extern Vec2 screenSize, screenCenter, vec2Unit, vec2Zero;

void vec2Max(Vec2 *vecMax, Vec2 *v1, Vec2 *v2);
void vec2Min(Vec2 *vecMin, Vec2 *v1, Vec2 *v2);
void vec2Add(Vec2 *result, Vec2 *a1, Vec2 *a2);
void vec2Sub(Vec2 *result, Vec2 *a1, Vec2 *a2);
void vec2Abs(Vec2 *vec);

typedef struct {
  Vec2 topLeft, botRight;	/* in screen coordinates */
} Region;		

// compute union of two regions
void regionUnion(Region *rUnion, Region *r1, Region *r2);
// Trims extent of region to screen bounds
void regionClipScreen(Region *region);

void
shapeInit();

typedef struct {
  Vec2 halfSize;
} Rect;


// true if pixel is in rect centered at rectPos
int rectCheck(Rect *rect, Vec2 *rectPos, Vec2 *pixel);
// compute bounding box in screen coordinates for rect centered at rectPos
void rectGetBounds(Rect *rect, Vec2 *rectPos, Region *bounds);

typedef struct {
  u_char *chords;
  u_char radius;
} Circle;

// true if pixel is in circle centered at circlePos
int circleCheck(Circle *circle, Vec2 *circlePos, Vec2 *pixel);
// compute bounding box in screen coordinates for circle centered at circlePos
void circleGetBounds(Circle *circle, Vec2 *circlePos, Region *bounds);


#endif
