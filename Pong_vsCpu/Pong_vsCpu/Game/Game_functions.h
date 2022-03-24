
#ifndef _GAMEFUNCT_H_
#define _GAMEFUNCT_H_

/* Includes ------------------------------------------------------------------*/
#include "LPC17xx.h"
#include "stdio.h"
#include "timer.h"
#include "GLCD.h" 
#include "TouchPanel.h"
#include "button.h"
void MainPage(void);
void NewGame(void);
void MakeField(void);
void Pause(void);
void GameLogic(void);
void DrawPaddleBottom(unsigned short Last_pos, unsigned short Pos);
void DrawFirstTopPaddle(unsigned short top_paddle);
void DrawPaddleTop(void);
void Prevedi_x(void);
void DrawBall(uint16_t xpos_old,uint16_t ypos_old,uint16_t xpos,uint16_t ypos);
void Game_over(unsigned short flag);
void Continue_Run(void);
void NewSet(unsigned short flag);
uint16_t xpos2select(uint8_t punteggio2);
void upgrade_punteggio(uint8_t flag);
#endif
