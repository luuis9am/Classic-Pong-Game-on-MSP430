#ifndef switches_included
#define switches_included

#define SW1 BIT0			/* switch1 is p2.0 */

void p2intInit();
void p2butInit(u_char);
void switch_interrupt_handler();

extern u_char switch_state_down, switch_state_changed; /* effectively boolean */
extern u_char p2switches;

#endif // included