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

typedef struct AbShape_s{		/* base type for all abstrct shapes */
  void (*getBounds)(struct AbShape_s *shape, Vec2 *centerPos, Region *bounds);
  int (*check)(struct AbShape_s *shape, Vec2 *centerPos, Vec2 *pixelLoc);
} AbShape;

void abShapeGetBounds(AbShape *s, Vec2 *centerPos, Region *bounds);
int abShapeCheck(AbShape *shape, Vec2 *centerPos, Vec2 *pixelLoc);



typedef struct AbRect_s {
  void (*getBounds)(struct AbRect_s *rect, Vec2 *centerPos, Region *bounds);
  int (*check)(struct AbRect_s *shape, Vec2 *centerPos, Vec2 *pixel);
  Vec2 halfSize;	/* vector from center to upper-right corner */
} AbRect;


// true if pixel is in rect centered at centerPos
int abRectCheck(AbRect *rect, Vec2 *centerPos, Vec2 *pixel);
// compute bounding box in screen coordinates for rect centered at centerPos
void abRectGetBounds(AbRect *rect, Vec2 *centerPos, Region *bounds);

typedef struct AbCircle_s {
  void (*getBounds)(struct AbCircle_s *circle, Vec2 *centerPos, Region *bounds);
  int (*check)(struct AbCircle_s *circle, Vec2 *centerPos, Vec2 *pixel);
  u_char *chords;
  u_char radius;
} AbCircle;

// true if pixel is in circle centered at circlePos
int abCircleCheck(AbCircle *circle, Vec2 *circlePos, Vec2 *pixel);
// compute bounding box in screen coordinates for circle centered at circlePos
void abCircleGetBounds(AbCircle *circle, Vec2 *circlePos, Region *bounds);

/* Layer: contains a shape to be displayed */
typedef struct Layer_s {
  AbShape *abShape;
  Vec2 pos, dispPos;
  u_int color;
  struct Layer_s *next;
} Layer;	
void layerGetBounds(Layer *l, Region *bounds);
void layerDraw(Layer *layers);

extern u_int bgColor;		/*  background color */

#endif
