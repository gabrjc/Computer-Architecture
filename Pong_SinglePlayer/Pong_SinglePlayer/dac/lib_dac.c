#include "lpc17xx.h"
#include "dac.h"

/*----------------------------------------------------------------------------
  Function that initializes ADC
 *----------------------------------------------------------------------------*/
void DAC_init (void) {

  //LPC_SC->PCONP       |=  (1<<12);      /* Enable power to ADC block          */

	/* these lines are used to enable DAC */
	LPC_PINCON->PINSEL1 |= (1<<21);
	LPC_PINCON->PINSEL1 &= ~(1<<20);
	LPC_GPIO0->FIODIR |= (1<<26);

}

