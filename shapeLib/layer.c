#include "lcdutils.h"
#include "lcddraw.h"
#include "shape.h"

void
layerGetBounds(const Layer *l, Region *bounds)
{
  Region dispBounds, curBounds;
  abShapeGetBounds(l->abShape, &l->pos, &curBounds);
  abShapeGetBounds(l->abShape, &l->dispPos, &dispBounds);
  regionUnion(bounds, &curBounds, &dispBounds);
  regionClipScreen(bounds);
}

void
layerDraw(Layer *layers)
{
  int row, col;
  for (row = 0; row < screenHeight; row++) {
    lcd_setArea(0, row, screenWidth-1, row);
    for (col = 0; col < screenWidth; col++) {
      Vec2 pixelPos = {col, row};
      u_int color = bgColor;
      Layer *probeLayer;
      for (probeLayer = layers; probeLayer; probeLayer = probeLayer->next) {
	if (abShapeCheck(probeLayer->abShape, &probeLayer->pos, &pixelPos)) {
	  color = probeLayer->color;
	  break; 
	} /* if check */
      } // for checking all layers at col, row
      lcd_writeColor(color); 
    } // for col
  } // for row
} 



void
layerDrawOld(Layer *layers)
{
  Layer *boundLayer, *probeLayer;
  for (boundLayer=layers; boundLayer; boundLayer=boundLayer->next) {
    int row, col;
    Region bounds;
    layerGetBounds(boundLayer, &bounds);
    lcd_setArea(bounds.topLeft.axes[0], bounds.topLeft.axes[1],
		bounds.botRight.axes[0], bounds.botRight.axes[1]);
    for (row = bounds.topLeft.axes[1]; row <= bounds.botRight.axes[1]; row++) {
      for (col = bounds.topLeft.axes[0]; col <= bounds.botRight.axes[0]; col++) {
	Vec2 pixelPos = {col, row};
	u_int color = bgColor;
	for (probeLayer = layers; probeLayer; probeLayer = probeLayer->next) {
	  if (abShapeCheck(probeLayer->abShape, &probeLayer->pos, &pixelPos)) {
	    color = probeLayer->color;
	    break; 
	  } /* if check */
	} // for checking all layers at col, row
	lcd_writeColor(color); 
      } // for col
    } // for row
  } // for layer being rendered
  for (boundLayer=layers; boundLayer; boundLayer=boundLayer->next)
    boundLayer->dispPos = boundLayer->pos;
}	  


