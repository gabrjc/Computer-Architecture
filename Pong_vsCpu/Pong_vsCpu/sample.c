/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               main.c
** Descriptions:            ExtraPoint2
**
**--------------------------------------------------------------------------------------------------------
** Created by:              Gabriele Canova
** Created date:            14/01/2022
** Version:                 v1.0
** Descriptions:            The final version
** Note: 										Il gioco è stato pensato per essere utilizzato in ambiente emulativo 
														e funziona in maniera decorosa su questo dispositivo che ha scaling ~26
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "LPC17xx.h"
#include "GLCD.h" 
#include "TouchPanel.h"
#include "timer.h"
#include "button.h"
#include "Game_functions.h"
#include "RIT.h"
#include "adc.h"
#include "dac.h"

#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif


extern uint8_t Play;
int main(void)
{
  SystemInit();  												/* System Initialization (i.e., PLL)  */
	BUTTON_init();
  LCD_Initialization();                /* LED Initialization                 */  
	ADC_init();														/* ADC Initialization */
	DAC_init();
	init_timer(0,0x4E2);	
	init_RIT(0x4c4b40);									
	
	
	MainPage();
	
	LPC_SC->PCON |= 0x1;									/* power-down	mode										*/
	LPC_SC->PCON &= ~(0x2);						
	
  while (1)	
  {
	
		__ASM("wfi");
  }
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
