#include "button.h"
#include "lpc17xx.h"
#include "Game_functions.h"
#include "RIT.h"

volatile uint8_t Eint1=0, Eint2=0;



void EINT0_IRQHandler (void)	  
{
		disable_RIT();
		disable_timer(0);
		disable_timer(1);           /* enable irq in nvic                 */
		Eint1=0;Eint2=0;
		MainPage();
		LPC_SC->EXTINT &= (1 << 0);     /* clear pending interrupt         */
}


void EINT1_IRQHandler (void)	  
{			
	
		NVIC_DisableIRQ(EINT1_IRQn);
		LPC_PINCON->PINSEL4    &= ~(1 << 22);			
		Eint1=1;
		enable_RIT();
		LPC_SC->EXTINT &= (1 << 1);     /* clear pending interrupt         */
	
}

void EINT2_IRQHandler (void)	  
{	
		
		NVIC_DisableIRQ(EINT2_IRQn);              /* enable irq in nvic                 */
		LPC_PINCON->PINSEL4    &= ~(1 << 24);
		Eint2=1;
		enable_RIT();
	
		LPC_SC->EXTINT &= (1 << 2);     /* clear pending interrupt         */    

	}

