#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "shape.h"

#define GREEN_LED BIT6

static AbCircle circle14;

void makeCircle14()
{
  static u_char chords14[15];	/* for a circle of radius 14 */
  computeChordVec(chords14, 14);
  circle14.radius = 14;
  circle14.chords = chords14;
  circle14.check = abCircleCheck;
  circle14.getBounds = abCircleGetBounds;
}  

AbRect rect10 = {abRectGetBounds, abRectCheck, 10,10};;

#define numLayers 2
Layer layer1 = {
  (AbShape *)&rect10,
  {screenWidth/2, screenHeight/2},{screenWidth/2, screenHeight/2}, /* position */
  COLOR_RED,
  0,
};
Layer layer0 = {
  (AbShape *)&circle14,
  {(screenWidth/2)+10, (screenHeight/2)+5}, /* position */
  {(screenWidth/2)+10, (screenHeight/2)+5}, 
  COLOR_ORANGE,
  &layer1,
};

typedef struct MovShape_s {
  Layer *layer;
  Vec2 velocity;
  struct MovShape_s *next;
} MovShape;

MovShape ms1 = { &layer1, {1,2}, 0 };
MovShape ms0 = { &layer0, {2,1}, &ms1 };
Region fence = {{10,30}, {SHORT_EDGE_PIXELS-10, LONG_EDGE_PIXELS-10}};

msAdvance(MovShape *ms, Region *fence)
{
  Vec2 newPos;
  u_char axis;
  Region shapeBoundary;
  for (; ms; ms = ms->next) {
    vec2Add(&newPos, &ms->layer->pos, &ms->velocity);
    abShapeGetBounds(ms->layer->abShape, &ms->layer->pos, &shapeBoundary);
    for (axis = 0; axis < 2; axis ++) {
      if ((shapeBoundary.topLeft.axes[axis] < fence->topLeft.axes[axis]) ||
	  (shapeBoundary.botRight.axes[axis] > fence->botRight.axes[axis]) ) {
	int velocity = ms->velocity.axes[axis] = -ms->velocity.axes[axis];
	newPos.axes[axis] += (2*velocity);
      }	// if outside of fence 
    } // for axis
    ms->layer->pos = newPos;
  } // for ms
}


u_int bgColor = COLOR_BLUE;
int redrawScreen = 1;

main()
{
  configureClocks();
  lcd_init();
  shapeInit();
  Vec2 rectPos = screenCenter, circlePos = {30,screenHeight - 30};

  clearScreen(COLOR_BLUE);
  drawString5x7(20,20, "hello", COLOR_GREEN, COLOR_BLUE);
  shapeInit();
  
  makeCircle14();

  enableWDTInterrupts();      /* enable periodic interrupt */
  or_sr(0x8);			/* GIE (enable interrupts) */


  P1DIR |= GREEN_LED;		
  for(;;) {
    while (!redrawScreen) {	/* Pause CPU if screen doesn't need updating */
      P1OUT &= ~GREEN_LED;      /* Green led off with CPU */
      or_sr(0x10);		/* CPU OFF */
    }
    P1OUT |= GREEN_LED;         /* Green led on when CPU on */
    redrawScreen = 0;
    layerDraw(&layer0);
  }
}


void wdt_c_handler()
{
  static short count = 0;
  P1OUT |= GREEN_LED;		/* Green LED on when cpu on */
  count ++;
  if (count == 15) {
    msAdvance(&ms0, &fence);
    redrawScreen = 1;
    count = 0;
  }
  P1OUT &= ~GREEN_LED;		/* Green LED off when cpu off */
}
