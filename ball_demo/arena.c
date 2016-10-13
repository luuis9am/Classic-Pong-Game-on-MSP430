#include <msp430.h>
#include "edukit.h"
#include "arena.h"

void drawArena() {
	setColor(COLOR_WHITE);
	drawRect(
		getScreenWidth()/2 - ARENA_WIDTH/2, 
		getScreenHeight()/2 - ARENA_HEIGHT/2, 
		getScreenWidth()/2 + ARENA_WIDTH/2, 
		getScreenHeight()/2 + ARENA_HEIGHT/2
	);
}