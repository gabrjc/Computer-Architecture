
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
void DrawPaddle(unsigned short Last_pos, unsigned short Pos);
void DrawBall(uint16_t xpos_old,uint16_t ypos_old,uint16_t xpos,uint16_t ypos);
void Game_over(void);
void Continue_Run(void);
void upgrade_punteggio(uint8_t flag);
#endif
