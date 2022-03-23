/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "RIT.h"
#include "Game_functions.h"

/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/


extern uint8_t Eint1;
extern uint8_t Eint2;
volatile uint8_t Play, pause=0;

void RIT_IRQHandler (void)
{	
	
	
	if(Eint1 > 1){ 
		if((LPC_GPIO2->FIOPIN & (1<<11)) == 0){				
			switch(Eint1){
				case 2:
					
						
						//enable_RIT();
						Play=1;
						NewGame();
						enable_timer(0);
				
				break;
				default:
					break;
			}
			Eint1++;
		}
		else {	
			Eint1=0;			
			NVIC_EnableIRQ(EINT1_IRQn);							
			LPC_PINCON->PINSEL4    |= (1 << 22);     
		}
	}
	else {
		if(Eint1 == 1)Eint1++;
	}
	

	if(Eint2 > 1){ 
		if((LPC_GPIO2->FIOPIN & (1<<12)) == 0){	
			
			switch(Eint2){
				case 2:
	        if(pause==0){
						disable_timer(0);
						Play=0;
						Pause();
						pause=1;
					}
					else{
						Play=1;
						pause=0;
						MakeField();
						enable_timer(0);
						}
					
					break;
				default: 
					break;
			}
			
			Eint2++;
		}
		else {	
			Eint2=0;			
			NVIC_EnableIRQ(EINT2_IRQn);							
			LPC_PINCON->PINSEL4    |= (1 << 24);     
		}
	}
	else {
		if (Eint2 == 1){Eint2++;}
	}
	


  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
		
		return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
