/** \file shape.h
 *  \brief 
 */ 

#ifndef shape_included
#define shape_included

#include "lcdutils.h"

/** Vector structure containing:
 *  an array of two integers that can be used
 *  to describe a position (x,y), or dimensions
 *  such as length and width.
 */
typedef struct {
  int axes[2];
} Vec2;

extern Vec2 screenSize, screenCenter, vec2Unit, vec2Zero;

/** Gives the max vector between v1 and v2
 *  
 *  \param vecMax (out) The max vector
 *  \param (in) v1 Vector 1
 *  \param (in) v2 Vector 2
 */ 
void vec2Max(Vec2 *vecMax, Vec2 *v1, Vec2 *v2);

/** Gives the min vector between v1 and v2
 *  
 *  \param vecMin (out) The min vector
 *  \param v1 (in) Vector 1
 *  \param v2 (in) Vector 2
 */ 
void vec2Min(Vec2 *vecMin, Vec2 *v1, Vec2 *v2);

/** Gives the summed vector of v1 and v2 (v1 + v2)
 *  
 *  \param result (out) The resulting vector of v1 + v2
 *  \param v1 (in) Vector 1
 *  \param v2 (in) Vector 2
 */ 
void vec2Add(Vec2 *result, Vec2 *a1, Vec2 *a2);

/** Gives the subtracted vector between v1 and v2 (v1 - v2)
 *  
 *  \param result (out) The resulting vector of v1 - v2
 *  \param v1 (in) Vector 1
 *  \param v2 (in) Vector 2
 */ 
void vec2Sub(Vec2 *result, Vec2 *a1, Vec2 *a2);

/** Gives the absolute value of vector
 *  
 *  \param vec (in and out) The vector
 */ 
void vec2Abs(Vec2 *vec);

/** Region structure that contains:
 *  an array of two integers that 
 *  represent the top left and
 *  bottom right coordinates of the region
 */
typedef struct {
  Vec2 topLeft, botRight;	/* in screen coordinates */
} Region;		

/** This function computes the union of two regions
 *  
 *  \param rUnion (out) The unioned region of r1 and r2
 *  \param r1 (in) The first region
 *  \param r2 (in) The second region
 */
void regionUnion(Region *rUnion, Region *r1, Region *r2);

/** Trims extend of region to screen bounds 
 *  
 *  \param region (in and out) The region
 */
void regionClipScreen(Region *region);

/** This function initializes the screen
 *  vectors that are used by shapes
 */
void shapeInit();

/** Trims extend of region to screen bounds 
 *  
 *  \param region The region
 */
typedef struct AbShape_s{		/* base type for all abstrct shapes */
  void (*getBounds)(struct AbShape_s *shape, Vec2 *centerPos, Region *bounds);
  int (*check)(struct AbShape_s *shape, Vec2 *centerPos, Vec2 *pixelLoc);
} AbShape;

/** Computes bounding box of abShape in screen coordinates 
 *
 *  \param s (in) The abstract shape
 *  \param centerPos (in) The Vec2 specifying the center poisiton of the shape
 *  \param bounds (out) The computed bounding box region
 */
void abShapeGetBounds(AbShape *s, Vec2 *centerPos, Region *bounds);

/** Check if pixel is within the abShape centered at centerPos
 *
 *  \param shape (in) The abstract shape
 *  \param centerPos (in) The Vec2 specifying the center position of the shape
 *  \param pixelLoc (in) The Vec2 specifying the location of the pixel
 *  \return True (1) if pixel is in the abShape centered at centerPos 
 */
int abShapeCheck(AbShape *shape, Vec2 *centerPos, Vec2 *pixelLoc);

/** Abstract Arrow structure that contains:
 *  a pointer to a getBounds() function,
 *  a pointer to a check() function, and
 *  a size
 */
typedef struct AbRArrow_s {
  void (*getBounds)(struct AbRArrow_s *shape, Vec2 *centerPos, Region *bounds);
  int (*check)(struct AbRArrow_s *shape, Vec2 *centerPos, Vec2 *pixelLoc);
  int size;
} AbRArrow;

/** Computes bounding box in screen coordinates for arrow with 
 *  whose tip is at centerPos
 *  
 *  \param arrow (in) The abstract arrow
 *  \param centerPos (in) The Vec2 specifying the center position of the arrow
 *  \param bounds (out) The computed bounded box region
 */
void abRArrowGetBounds(AbRArrow *arrow, Vec2 *centerPos, Region *bounds);

/** Check if pixel is within the abArrow centered at centerPos
 *
 *  \param arrow (in) The abstract arrow
 *  \param centerPos (in) The Vec2 specifying the center position of the arrow
 *  \param pixel (in) The Vec2 specifying the location of the pixel
 *  \return True (1) if pixel is in arrow whose tip is at centerPos
 */
int abRArrowCheck(AbRArrow *arrow, Vec2 *centerPos, Vec2 *pixel);

/** Abstract Rectangle structure that contains:
 *  a pointer a getBounds() function,
 *  a pointer to a check() function, and
 *  a half size vector from the center to upper-right corner
 */ 
typedef struct AbRect_s {
  void (*getBounds)(struct AbRect_s *rect, Vec2 *centerPos, Region *bounds);
  int (*check)(struct AbRect_s *shape, Vec2 *centerPos, Vec2 *pixel);
  Vec2 halfSize;	
} AbRect;

/** Computes bounding box in screen coordinates for rect centered at centerPos
 *
 *  \param rect (in) The abstract rectangle
 *  \param centerPos (in) The Vec2 specifying the center position of the rectangle
 *  \param bounds (out) The computed bounded box region
 */
void abRectGetBounds(AbRect *rect, Vec2 *centerPos, Region *bounds);

/** Check if pixel is within the abRect centered at centerPos
 *
 *  \param rect (in) The abstract rectangle
 *  \param centerPos (in) The Vec2 specifying the center position of the rectangle
 *  \param pixel (in) The Vec2 specifying the location of the pixel
 *  \return True (1) if pixel is in rectangle whose tip is at centerPos
 */
int abRectCheck(AbRect *rect, Vec2 *centerPos, Vec2 *pixel);

/** Abstract Circle structure that contains:
 *  a pointer a getBounds() function,
 *  a pointer to a check() function, 
 *  a half chord vector for drawing the circle, and
 *  a radius size
 */ 
typedef struct AbCircle_s {
  void (*getBounds)(struct AbCircle_s *circle, Vec2 *centerPos, Region *bounds);
  int (*check)(struct AbCircle_s *circle, Vec2 *centerPos, Vec2 *pixel);
  u_char *chords;
  u_char radius;
} AbCircle;

/** Computes bounding box in screen coordinates for circle centered at circlePos
 *
 *  \param circle (in) The abstract circle
 *  \param circlePos (in) The Vec2 specifying the center position of the circle
 *  \param bounds (out) The computed bounded box region
 */void abCircleGetBounds(AbCircle *circle, Vec2 *circlePos, Region *bounds);

/** Check if pixel is within the abRect centered at centerPos
 *
 *  \param circle (in) The abstract circle
 *  \param circlePos (in) The Vec2 specifying the center position of the circle
 *  \param pixel (in) The Vec2 specifying the location of the pixel
 *  \return True (1) if pixel is in circle whose tip is at circlePos
 */int abCircleCheck(AbCircle *circle, Vec2 *circlePos, Vec2 *pixel);

/** Layer structure that contains:
 *  A shape to be displayed
 */
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
