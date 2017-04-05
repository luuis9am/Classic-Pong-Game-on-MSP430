#include "lcdutils.h"
#include "lcddraw.h"
#include "shape.h"

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
layerGetBounds(const Layer *l, Region *bounds)
{
  Region lastBounds, curBounds;
  abShapeGetBounds(l->abShape, &l->posLast, &lastBounds);
  abShapeGetBounds(l->abShape, &l->pos, &curBounds);
  regionUnion(bounds, &curBounds, &lastBounds);
  regionClipScreen(bounds);
}

void
layerInit(Layer *layer)
{
  for (; layer; layer = layer->next)
    layer->posLast = layer->posNext = layer->pos;
}

