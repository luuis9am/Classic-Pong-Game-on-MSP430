#ifndef _UTILS_H
#define _UTILS_H

// hack fix this later
#define interrupt(x) void __attribute__((interrupt (x)))

// delays a specified number of cycles
/* static void __inline__ _delay_cycles(unsigned long cyc) */
/* { */
/*   unsigned int full_count = ~0; */
/*   int num_exec = (cyc >> 16); */

/*   // full 16 bit cycles */
/*   while (num_exec) */
/*     __delay_cycles(full_count); */

/*   // remainder */
/*   __delay_cycles((unsigned int) (full_count & cyc)); */
/* } */


/* // machine code to delay a specified number of cycles, only works */
/* // on int size (16 bit) or smaller */
/* static void __inline__ __delay_cycles(register unsigned int n) */
/* { */
/*   __asm__ __volatile__ ( */
/* 			"1: \n" */
/* 			" dec %[n] \n" */
/* 			" jne 1b \n" */
/* 			: [n] "+r"(n)); */
/* } */

#endif // _UTILS_H
