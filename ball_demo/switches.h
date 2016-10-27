#ifndef switches_included
#define switches_included

#include "lcdtypes.h"

#define SW1 BIT0			/* switch1 is p2.0 */
#define SWITCHES SW1

static u_char switch_update_interrupt_sense();
void p2butInit(u_char);
void p2intInit();
void switch_interrupt_handler();
u_int p2GetSw();

extern u_char switch_state_down, switch_state_changed; /* effectively boolean */
extern u_int p2switches;

#endif // included
