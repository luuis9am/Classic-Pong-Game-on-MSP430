#include <msp430.h>
#include "edukit.h"
#include "arena.h"

int count = 0;
signed int offset = 1;
signed int px = 25;
signed int py = 60;
signed int deltaX = 1;
signed int deltaY = 1;
int RADIUS = 5;

void update_ball() {
	int	px_new = px + deltaX;
	int py_new = py + deltaY;

	if (px_new - RADIUS <= LEFT_BOUNDARY || (px_new + RADIUS >= RIGHT_BOUNDARY))
		deltaX = -deltaX;

	if (py_new - RADIUS <= LOWER_BOUNDARY || py_new + RADIUS >= UPPER_BOUNDARY)
		deltaY = -deltaY;

	px = px_new + deltaX;
	py = py_new + deltaY;
}

__interrupt(WDT_VECTOR) WDT(){	
	drawArena();
	if (++count == 10) {
		setColor(COLOR_BLACK);
		fillCircle(px, py, RADIUS);
		update_ball();
		setColor(COLOR_RED);
		fillCircle(px, py, RADIUS);
		count = 0;
	}
}
