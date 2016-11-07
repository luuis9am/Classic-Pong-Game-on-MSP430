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

extern const Vec2 screenSize, screenCenter, vec2Unit, vec2Zero;

/** vec2Max computes the maximum in both dimensions.
 *  
 *  \param vecMax (out) 
 *  \param (in) v1 Vector 1
 *  \param (in) v2 Vector 2
 */ 
void vec2Max(Vec2 *vecMax, const Vec2 *v1, const Vec2 *v2);

/** vec2Min computes the minimum in both dimensions
 *  
 *  \param vecMin (out) The min vector
 *  \param v1 (in) Vector 1
 *  \param v2 (in) Vector 2
 */ 
void vec2Min(Vec2 *vecMin, const Vec2 *v1, const Vec2 *v2);

/** Vector sum: result = v1 + v2
 */ 
void vec2Add(Vec2 *result, const Vec2 *a1, const Vec2 *a2);

/** Vector difference: result = v1 - v2
 *  
 */ 
void vec2Sub(Vec2 *result, const Vec2 *a1, const Vec2 *a2);

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
void regionUnion(Region *rUnion, const Region *r1, const Region *r2);

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
  void (*getBounds)(const struct AbShape_s *shape, const Vec2 *centerPos, Region *bounds);
  int (*check)(const struct AbShape_s *shape, const Vec2 *centerPos, const Vec2 *pixelLoc);
} AbShape;

/** Computes bounding box of abShape in screen coordinates 
 *
 *  \param s (in) The abstract shape
 *  \param centerPos (in) The Vec2 specifying the center poisiton of the shape
 *  \param bounds (out) The computed bounding box region
 */
void abShapeGetBounds(const AbShape *s, const Vec2 *centerPos, Region *bounds);

/** Check if pixel is within the abShape centered at centerPos
 *
 *  \param shape (in) The abstract shape
 *  \param centerPos (in) The Vec2 specifying the center position of the shape
 *  \param pixelLoc (in) The Vec2 specifying the location of the pixel
 *  \return True (1) if pixel is in the abShape centered at centerPos 
 */
int abShapeCheck(const AbShape *shape, const Vec2 *centerPos, const Vec2 *pixelLoc);

/** An AbShape Right Arrow with filled tip
 *
 *  size: width of the arrow.  Tip is a triangle with width=1/2 size.
 *  The "centerPos is at the arrow's tip.
 */
typedef struct AbRArrow_s {
  void (*getBounds)(const struct AbRArrow_s *shape, const Vec2 *centerPos, Region *bounds);
  int (*check)(const struct AbRArrow_s *shape, const Vec2 *centerPos, const Vec2 *pixelLoc);
  int size;
} AbRArrow;

/** As required by AbShape
 */
void abRArrowGetBounds(const AbRArrow *arrow, const Vec2 *centerPos, Region *bounds);

/** As required by AbShape
 */
int abRArrowCheck(const AbRArrow *arrow, const Vec2 *centerPos, const Vec2 *pixel);

/** AbShape rectangle
 *
 *  Vector halfSize must be to first quadrant (both axes non-negative).  
 *  Specifies extent in all four directions.
 */ 
typedef struct AbRect_s {
  void (*getBounds)(const struct AbRect_s *rect, const Vec2 *centerPos, Region *bounds);
  int (*check)(const struct AbRect_s *shape, const Vec2 *centerPos, const Vec2 *pixel);
  const Vec2 halfSize;	
} AbRect;

/** As required by AbShape
 */
void abRectGetBounds(const AbRect *rect, const Vec2 *centerPos, Region *bounds);

/** As required by AbShape
 */
int abRectCheck(const AbRect *rect, const Vec2 *centerPos, const Vec2 *pixel);

typedef AbRect AbRectOutline;	/* same as AbRect */

/** As required by AbShape
 */
void abRectOutlineGetBounds(const AbRect *rect, const Vec2 *centerPos, Region *bounds);

/** As required by AbShape
 */
int abRectOutlineCheck(const AbRect *rect, const Vec2 *centerPos, const Vec2 *pixel);

/** Linked list of Layers.  
 * 
 *  Each layer contains
 *   - a referenced to an abstract shape to be rendered.
 *   - the layer's current position
 *   - the layer's color
 *   - a reference to the next (lower) layer.
 */
typedef struct Layer_s {
  AbShape *abShape;
  Vec2 pos, posLast, posNext; /* initially just set pos */
  u_int color;
  struct Layer_s *next;
} Layer;	

/** Compute layer's bounding box.
 */
void layerGetBounds(const Layer *l, Region *bounds);

/**
  sets bounds into a consistent state
 */
void layerInit(Layer *layers);

/** Render all layers.   
 *  Pixels that are not contained by a layer are set to bgColor.
 */
void layerDraw(Layer *layers);

/** Background color.
  */
extern u_int bgColor;		/*  background color */

#endif
