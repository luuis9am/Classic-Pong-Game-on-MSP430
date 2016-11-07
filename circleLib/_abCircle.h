#ifndef abCircle_included
#define abCircle_included

#include "shape.h"

/** AbShape circle
 *  
 *  chords should be a vector of length radius + 1.  
 *  Entry at index i is 1/2 chord length at distance i from the circle's center.  
 *  This vector can be generated using lcdLib's computeChordVec() (lcddraw.h).
 */ 
typedef struct AbCircle_s {
  void (*getBounds)(const struct AbCircle_s *circle, const Vec2 *centerPos, Region *bounds);
  int (*check)(const struct AbCircle_s *circle, const Vec2 *centerPos, const Vec2 *pixel);
  const u_char *chords;
  const u_char radius;
} AbCircle;

/** Required by AbShape
 */
void abCircleGetBounds(const AbCircle *circle, const Vec2 *circlePos, Region *bounds);

/** Required by AbShape
 */
int abCircleCheck(const AbCircle *circle, const Vec2 *circlePos, const Vec2 *pixel);

#endif



