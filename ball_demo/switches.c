#include <msp430.h>
#include "lcdutils.h"
#include "switches.h"

u_char switch_state_down, switch_state_changed; /* effectively boolean */
u_int p2switches;
static u_int p2switchMask = SW1;

static u_int buttons_previous;
static u_int buttons_current;
static u_int buttons_changed;

static u_char 
switch_update_interrupt_sense()
{
  char p2val = P2IN;
  /* update switch interrupt to detect changes from current buttons */
  P2IES |= (p2val & p2switches);  /* if switch up, sense down */
  P2IES &= (p2val | ~p2switchMask); /* if switch down, sense up */
  return p2val;
}

void 
p2butInit(u_char mask)
{
  P2REN |= mask;    /* enables resistors for switches */
  P2IE = mask;      /* enable interrupts from switches */
  P2OUT |= mask;    /* pull-ups for switches */
  P2DIR &= ~mask;   /* set switches' bits for input */
  P2IES |= mask;    
}

void 
p2intInit()           /* setup switch */
{  
  p2switches |= SW1;            /* setup switches to use */
  p2switchMask |= p2switches;   /* setup p2switchMask */

  p2butInit(p2switchMask);

  switch_update_interrupt_sense();
  switch_interrupt_handler(); /* to initially read the switches */
}

void
switch_interrupt_handler()
{
  u_char p2val = switch_update_interrupt_sense();
  buttons_current = (p2val & p2switchMask);
  switch_state_down = (p2val & SW1) ? 0 : 1; /* 0 when SW1 is up */
  switch_state_changed = 1;                  /* SW1 has changed */
  buttons_changed = buttons_previous ^ buttons_current; /* Update the buttons that have changed */
  buttons_previous = buttons_current;        
}

/* Returns a word where:
 * the high-order byte is the buttons that have changed,
 * the low-order byte is the current state of the buttons
 */
u_int 
p2GetSw() {
  u_int button_word;
  button_word |= (buttons_changed<<8); /* Set high-order byte */
  button_word |= buttons_current;      /* Set low-order byte */
  return button_word;
}
