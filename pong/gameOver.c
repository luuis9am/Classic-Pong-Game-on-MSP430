//game over song in c

#include "libTimer.h"
#include "buzzer.h"
#include <msp430.h>

static int counter = 0;

void buzzer_init() {
  /*
    Direct timer A output "TA0.1" to P2.6.
    According to table 21 from data sheet:
    P2SEL2.6, P2SEL2.7, and P2SEL.7 must be zero
    P2SEL.6 must be 1
    Also: P2.6 direction must be output
  */
  timerAUpmode(); 	 //used to drive speaker
  P2SEL2 &= ~(BIT6 | BIT7);
  P2SEL &= ~BIT7;
  P2SEL |= BIT6;
  P2DIR = BIT6; 	//enable output to speaker (P2.6)
}

void buzzer_set_period(short cycles){
  CCR0 = cycles;
  CCR1 = cycles >> 1; //one half cycle
}

void gameOver(){
  switch(counter){
  	  case 0:
  		  buzzer_set_period(300);
  		  buzzer_set_period(900);
  		  counter++;
  		  break;
  	  case 1:
  		  buzzer_set_period(400);
  		  buzzer_set_period(800);
  		  counter++;
  		  break;
  	  case 2:
  		  buzzer_set_period(500);
  		  buzzer_set_period(700);
  		  counter++;
  		  break;
  	  case 3:
  		  buzzer_set_period(600);
  		  buzzer_set_period(500);
  		  counter++;
  		  break;
  	  case 4:
  		  buzzer_set_period(700);
  		  buzzer_set_period(400);
  		  counter++;
  		  break;
  	  case 5:
  		  buzzer_set_period(800);
  		  buzzer_set_period(300);
  		  counter++;
  		  break;
  	  case 6:
  		  buzzer_set_period(900);
  		  buzzer_set_period(200);
  		  counter++;
  		  break;
  	  case 7:
  		  buzzer_set_period(300);
  		  buzzer_set_period(400);
  		  counter++;
  		  break;
  	  case 8:
  		  buzzer_set_period(600);
  		  buzzer_set_period(500);
  		  counter++;
  		  break;
  	  case 9:
  		  buzzer_set_period(700);
  		  buzzer_set_period(600);
  		  counter++;
  		  break;
  	  case 10:
  		  buzzer_set_period(0);
  		  break;

  }
}
