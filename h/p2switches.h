#ifndef switches_included
#define switches_included

#include "msp430.h"

unsigned int p2sw_read();
void p2sw_init(unsigned char mask);

#endif // included
