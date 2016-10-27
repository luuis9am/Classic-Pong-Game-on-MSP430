#include "msp430.h"
#include "libTimer.h"
#include "lcdutils.h"
#include "lcddraw.h"

#define ARENA_WIDTH 100
#define ARENA_HEIGHT 50

u_char LOWER_BOUNDARY, UPPER_BOUNDARY, LEFT_BOUNDARY, RIGHT_BOUNDARY; /* Boundaries for arena */
u_char width, height;       /* screen width and height */


u_char pcol, prow;        /* position coordinates of ball */
signed int deltaCOL = 1, deltaROW = 1;
u_char count = 0;    




Circle circle14;

Vec2 circle1Pos, circle2Pos, circle1Velocity, circle2Velocity;

void initCircles() {
  static u_char chords14[15];	/* for a circle of radius 14 */
  computeChordVec(chords14, 14);
  circle14.radius = 14;
  circle14.chords = chords14;
  for (axis = 0; axis < 2; axis ++) {
    circle1Pos.axes[axis] = screenCenter.axes[axis] + 5;
    circle2Pos.axes[axis] = screenCenter.axes[axis] - 5;
    circle1Velocity[axis] = 1;
    circle1Velocity[axis] = 2;
  }
  circle1.color = COLOR_RED;
  circle2.color = COLOR_ORANGE;
}
    


/* return true if pixelPos is within circle at circlePos */
int
circleCheck(Vec2 *pixelPos, Circle *circle, Vec2 *circlePos)
{
  Vec2 relPos;			/* pixel location, relative to circle center */
  vec2Sub(&relPos, &pixelPos, &circlePas);
  s_char row = abs(relPos->axes[0]);
  s_char col = abs(relPos->axes[1]);
  return (col <= circle->radius) && (row <= circle->chords[col]);
}
  

void drawArena()
{
  drawRectOutline(LEFT_BOUNDARY, LOWER_BOUNDARY, ARENA_WIDTH, ARENA_HEIGHT, COLOR_BLACK);
}

fillCircle(u_char col, u_char row, u_char radius, u_char chords[], u_int color)
{
  u_char drow;
  for (drow = 0; drow < radius; drow++) {
    u_char dcol = chords[drow];
    u_char width = 1 + (dcol << 1);
    fillRectangle(col-dcol, row+drow, width, 1, color);
    fillRectangle(col-dcol, row-drow, width, 1, color);
  }
}

main()
{
  configureClocks();
  enableWDTInterrupts();      /* enable periodic interrupt */
  lcd_init();
  width = lcd_getScreenWidth(), height = lcd_getScreenHeight();
  u_char width_offset = ARENA_WIDTH>>1, height_offset = ARENA_HEIGHT>>1;
  
  LOWER_BOUNDARY = (height>>1) - height_offset;
  UPPER_BOUNDARY = (height>>1) + height_offset;
  LEFT_BOUNDARY = (width>>1) - width_offset;
  RIGHT_BOUNDARY = (width>>1) + width_offset;
  
  pcol = (width>>1);
  prow = (height>>1);
  
  clearScreen(COLOR_BLUE);
  drawString5x7((width>>1) - 20, 20, "Arena", COLOR_GREEN, COLOR_RED);
  
  drawArena();
  fillCircle(pcol, prow, RADIUS, chords14, COLOR_RED);
  
  or_sr(0x18);  /* CPU off, GIE on */
}




void update_ball() 
{
  u_char pcol_new = pcol + deltaCOL;
  u_char prow_new = prow + deltaROW;
  
  if (pcol_new - RADIUS <= LEFT_BOUNDARY || (pcol_new + RADIUS >= RIGHT_BOUNDARY))
    deltaCOL = -deltaCOL;
  
  if (prow_new - RADIUS <= LOWER_BOUNDARY || prow_new + RADIUS >= UPPER_BOUNDARY)
    deltaROW = -deltaROW;
  
  pcol = pcol_new + deltaCOL;
  prow = prow_new + deltaROW;
}

__interrupt(WDT_VECTOR) WDT()
{  
  drawArena();
  if (++count == 10) {
    fillCircle(pcol, prow, RADIUS, chords14, COLOR_BLUE);
    update_ball();
    fillCircle(pcol, prow, RADIUS, chords14, COLOR_RED);
    count = 0;
  }
}
