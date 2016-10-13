#ifndef arena_def
#define arena_def
#include "edukit.h"

#define ARENA_WIDTH 100
#define ARENA_HEIGHT 50

#define LOWER_BOUNDARY (LONG_EDGE_PIXELS/2 - ARENA_HEIGHT/2)
#define UPPER_BOUNDARY (LONG_EDGE_PIXELS/2 + ARENA_HEIGHT/2)
#define LEFT_BOUNDARY (SHORT_EDGE_PIXELS/2 - ARENA_WIDTH/2)
#define RIGHT_BOUNDARY (SHORT_EDGE_PIXELS/2 + ARENA_WIDTH/2)

void drawArena();

#endif