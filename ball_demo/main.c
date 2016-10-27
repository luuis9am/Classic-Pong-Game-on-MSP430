#include "msp430.h"
#include "libTimer.h"
#include "lcdutils.h"
#include "lcddraw.h"
#include "switches.h"

#define ARENA_WIDTH 100
#define ARENA_HEIGHT 50
#define RADIUS 14

u_char LOWER_BOUNDARY, UPPER_BOUNDARY, LEFT_BOUNDARY, RIGHT_BOUNDARY; /* Boundaries for arena */
u_char width, height;       /* screen width and height */
u_char chords14[RADIUS+1];	/* for a circle of radius 14 */

volatile u_char pcol, prow;        /* position coordinates of ball */
signed int deltaCOL = 1, deltaROW = 1;

volatile u_char ball_moved = 1;


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

void 
redrawBallForever()
{
  static int lcol, lrow;	/* last position */
  int _lcol, _lrow, _pcol, _prow;;
  
  for(;;) {
    while (!ball_moved)
      or_sr(0x10);		/* CPU OFF */
    
    /* lock out interrupts as we update state */
    and_sr(0xfff7);		/* clear GIE (enable interrupts) */
    ball_moved = 0;		
    _pcol = pcol; _prow = prow;
    _lcol = lcol; _lrow = lrow;
    or_sr(8);		/* set GIE */
          
    fillCircle(_lcol, _lrow, RADIUS, chords14, COLOR_BLUE);
    fillCircle(_pcol, _prow, RADIUS, chords14, COLOR_RED);
    lrow = _prow; lcol = _pcol;
  }
}

main()
{
  configureClocks();
  enableWDTInterrupts();      /* enable periodic interrupt */
  lcd_init();

  p2intInit();

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
  computeChordVec(chords14, 14);
  
  or_sr(0x8);			/* GIE (enable interrupts) */
  redrawBallForever();
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
  ball_moved = 1;
}

void wdt_c_handler()
{
  static int count = 0;
  count ++;
  if (count == 10) {
    count = 0;  
    if(p2GetSw() & SW1)      /* If SW1 up, update ball */
      update_ball();
  }
}
