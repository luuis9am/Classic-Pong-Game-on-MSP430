/** \file shape.h
 *  \brief 
 */ 

#ifndef shape_included
#define shape_included

#include "lcdutils.h"

/** Vec2 contain a position or vector
 *
 *  Axes: 0 for col, 1 for row.
 */
typedef struct {
  int axes[2];
} Vec2;

extern Vec2 screenSize, screenCenter, vec2Unit, vec2Zero;

/** vec2Max computes the maximum in both dimensions.
 *  
 *  \param vecMax (out) 
 *  \param (in) v1 Vector 1
 *  \param (in) v2 Vector 2
 */ 
void vec2Max(Vec2 *vecMax, Vec2 *v1, Vec2 *v2);

/** vec2Min computes the minimum in both dimensions
 *  
 *  \param vecMin (out) The min vector
 *  \param v1 (in) Vector 1
 *  \param v2 (in) Vector 2
 */ 
void vec2Min(Vec2 *vecMin, Vec2 *v1, Vec2 *v2);

/** Vector sum: result = v1 + v2
 *  
 */ 
void vec2Add(Vec2 *result, Vec2 *a1, Vec2 *a2);

/** Vector difference: result = v1 - v2
 *  
 */ 
void vec2Sub(Vec2 *result, Vec2 *a1, Vec2 *a2);

/** Absolute value in each direction
 *  
 *  \param vec (in and out) The vector
 */ 
void vec2Abs(Vec2 *vec);

/** Specifies a rectangular region
 */
typedef struct {
  Vec2 topLeft, botRight;	/* in screen coordinates */
} Region;		

/** Computes the bounding box containing two regions.
 */
void regionUnion(Region *rUnion, Region *r1, Region *r2);

/** Clip region within screen bounds
 */
void regionClipScreen(Region *region);

/** This function initializes the screen
 *  vectors that are used by shapes
 *
 *  Not needed anymore.
 */
void shapeInit();

/** Effectively a base class for Abstract Shapes
 *  
 *  Abstract Shapes have a shape but no position or color.
 *  The first two fields MUST BE pointers to
 *
 *  getBounds: A function that computes the bounding box for the AbShape
 *  when rendered at coordinate centerPos
 * 
 *  check: A function that determines if the AbShape contains pixelLoc when 
 *  rendered at centerPos
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

/** An AbShape Right Arrow with filled tip
 *
 *  size: width of the arrow.  Tip is a triangle with width=1/2 size.
 *  The "centerPos is at the arrow's tip.
 */
typedef struct AbRArrow_s {
  void (*getBounds)(struct AbRArrow_s *shape, Vec2 *centerPos, Region *bounds);
  int (*check)(struct AbRArrow_s *shape, Vec2 *centerPos, Vec2 *pixelLoc);
  int size;
} AbRArrow;

/** As required by AbShape
 */
void abRArrowGetBounds(AbRArrow *arrow, Vec2 *centerPos, Region *bounds);

/** As required by AbShape
 */
int abRArrowCheck(AbRArrow *arrow, Vec2 *centerPos, Vec2 *pixel);

/** AbShape rectangle
 *
 *  Vector halfSize must be to first quadrant (both axes non-negative).  
 *  Specifies extent in all four directions.
 */ 
typedef struct AbRect_s {
  void (*getBounds)(struct AbRect_s *rect, Vec2 *centerPos, Region *bounds);
  int (*check)(struct AbRect_s *shape, Vec2 *centerPos, Vec2 *pixel);
  Vec2 halfSize;	
} AbRect;

/** As required by AbShape
 */
void abRectGetBounds(AbRect *rect, Vec2 *centerPos, Region *bounds);

/** As required by AbShape
 */
int abRectCheck(AbRect *rect, Vec2 *centerPos, Vec2 *pixel);

typedef AbRect AbRectOutline;	/* same as AbRect */

/** As required by AbShape
 */
void abRectOutlineGetBounds(AbRect *rect, Vec2 *centerPos, Region *bounds);

/** As required by AbShape
 */
int abRectOutlineCheck(AbRect *rect, Vec2 *centerPos, Vec2 *pixel);

/** AbShape circle
 *  
 *  chords should be a vector of length radius + 1.  
 *  Entry at index i is 1/2 chord length at distance i from the circle's center.  
 *  This vector can be generated using lcdLib's computeChordVec() (lcddraw.h).
 */ 
typedef struct AbCircle_s {
  void (*getBounds)(struct AbCircle_s *circle, Vec2 *centerPos, Region *bounds);
  int (*check)(struct AbCircle_s *circle, Vec2 *centerPos, Vec2 *pixel);
  u_char *chords;
  u_char radius;
} AbCircle;

/** Required by AbShape
 */
void abCircleGetBounds(AbCircle *circle, Vec2 *circlePos, Region *bounds);

/** Required by AbShape
 */
int abCircleCheck(AbCircle *circle, Vec2 *circlePos, Vec2 *pixel);

/** Layer structure of AbShapes.  Each has a color and position.
 *  
 *  Next should either reference a lower layer or zero.
 * 
 *  Pos is the layer's current position.  
 *
 *  DispPos is the position where it was last rendered.  
 */
typedef struct Layer_s {
  AbShape *abShape;
  Vec2 pos, dispPos;
  u_int color;
  struct Layer_s *next;
} Layer;	

/** Compute layer's bounding box.
 */
void layerGetBounds(Layer *l, Region *bounds);


/** Render all layers.  Pixels that are not contained by a layer are set to bgColor.
 */
void layerDraw(Layer *layers);

/** Background color.
  */
extern u_int bgColor;		/*  background color */

#endif
