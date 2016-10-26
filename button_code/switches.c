#include <msp430.h>
#include "switches.h"

u_char switch_state_down, switch_state_changed; /* effectively boolean */
u_char p2switches;
static u_char p2switchMask = SW1;

static u_char 
switch_update_interrupt_sense()
{
  char p2val = P2IN;
  /* update switch interrupt to detect changes from current buttons */
  P2IES |= (p2val & SWITCHES);  /* if switch up, sense down */
  P2IES &= (p2val | ~SWITCHES); /* if switch down, sense up */
  return p2val;
}

void 
p2butInit(u_char mask)
{
  P2REN |= mask;    /* enables resistors for switches */
  P2IE = mask;      /* enable interrupts from switches */
  P2OUT |= mask;    /* pull-ups for switches */
  P2DIR &= ~mask;   /* set switches' bits for input */
}

void 
p2intInit()           /* setup switch */
{  
  p2switches = SW1;
  p2switchMask = p2switches;

  p2butInit(p2switchMask);

  switch_update_interrupt_sense();
  switch_interrupt_handler(); /* to initially read the switches */
}

void
switch_interrupt_handler()
{
  u_char p2val = switch_update_interrupt_sense();
  switch_state_down = (p2val & SW1) ? 0 : 1; /* 0 when SW1 is up */
  switch_state_changed = 1;
}