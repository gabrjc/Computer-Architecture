/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_adc.c
** Last modified Date:  20184-12-30
** Last Version:        V1.00
** Descriptions:        functions to manage A/D interrupts
** Correlated files:    adc.h
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/

#include "lpc17xx.h"
#include "adc.h"
#include "stdio.h"
#include "Game_functions.h"

/*----------------------------------------------------------------------------
  A/D IRQ: Executed when A/D Conversion is ready (signal from ADC peripheral)
 *----------------------------------------------------------------------------*/

unsigned short AD_current=0x00;
volatile unsigned short Paddle_Pos=0;
unsigned short AD_last = 0xFF;     /* Last converted value               */
volatile unsigned short Paddle_Last_pos=0;
volatile unsigned short Paddle_Pos_fract=0;
extern unsigned short PaddleSize;

void ADC_IRQHandler(void) {

	Paddle_Last_pos = Paddle_Pos;
	AD_last = AD_current;
	
  AD_current = ((LPC_ADC->ADGDR>>4) & 0xFFF);/* Read Conversion Result             */
	
	Paddle_Pos_fract=AD_current*(18)/0xFFF;
	Paddle_Pos=Paddle_Pos_fract*10;
return;
}
