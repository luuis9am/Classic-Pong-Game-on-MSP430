#include <msp430.h>
#include "led.h"
#include "switches.h"

void main(void) 
{  
  p2intInit();
  led_init();

  or_sr(0x18);  // CPU off, GIE on
} 