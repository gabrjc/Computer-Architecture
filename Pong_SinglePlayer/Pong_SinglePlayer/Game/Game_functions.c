#include "Game_functions.h"
#include "RIT.h"
#include "button.h"
#include "stdlib.h"

//240*320

volatile uint8_t punteggio;
volatile uint8_t record=100;
volatile unsigned short PaddleSize=50;

uint16_t x_pos, y_pos ,x_pos_old, y_pos_old;
int16_t x_speed, y_speed, no=1;
uint8_t From_sx_Paddle, From_sx_Ball, Temp, Last_Racc=0,Racc, Count, Random;
float rnd;


extern unsigned short Paddle_Last_pos, Paddle_Pos, AD_last;
extern uint8_t Play;

void MainPage(void){
	
char string_record[10];
sprintf(string_record, "%d", record);
	
	LCD_Clear(Black);
	//x,y,frase,background,colore
	GUI_Text(120, 10, (uint8_t *) " Record: ", White, Black);
	GUI_Text(190, 10, (uint8_t *) string_record, White, Black);
	GUI_Text_SIZED(15, 120, (uint8_t *) " LONELY PONG ", Yellow, Black,2);
	GUI_Text(0, 180, (uint8_t *) " Press KEY1 to start the game ", Green, White);
return;
}

void NewGame(void){
	punteggio=130;
	x_pos=229;
	y_pos=155;
	x_speed=-no;
	y_speed=no;
	
	//DrawBall(228,156,x_pos, y_pos);
	MakeField();
}

void MakeField(void){
	
char string_record[10];
	uint16_t i;
	sprintf(string_record, "%d", punteggio);
	LCD_Clear(Black);
	
	for(i=0;i<5;i++){
	LCD_DrawLine( 0, i, MAX_X, i, Red);
	LCD_DrawLine( i, 0, i, MAX_Y-32-11, Red);
	LCD_DrawLine( MAX_X+i-4, 0, MAX_X+i-4, MAX_Y-32-11, Red);
}
	
	GUI_Text_SIZED(8, 160, (uint8_t *) string_record , White, Black, 2 );

	

	return;
}



void Pause(void){

LCD_Clear(Black);

GUI_Text_SIZED(65, 120, (uint8_t *) " PAUSE ", Yellow, Black,2);
GUI_Text(0, 180, (uint8_t *) "Press KEY1 to restart the game", Green, White);
GUI_Text(0, 200, (uint8_t *) "Press KEY2 to resume the game ", Cyan, White);

	return;
}


void GameLogic(void){
	
		
	
	DrawPaddle(Paddle_Last_pos,Paddle_Pos);
	
	x_pos_old=x_pos;
	y_pos_old=y_pos;
	x_pos+=x_speed;
	y_pos+=y_speed;
	
	if(x_pos_old<x_pos) From_sx_Ball=1;
	else From_sx_Ball=0;
	
	if(y_pos < 5 ){
	y_pos=y_pos_old;
	x_pos=x_pos_old;
	y_speed=-y_speed;
	
	upgrade_punteggio(0);
	enable_timer(1);
	init_timer(1,0x1062);
	}
	
	if(x_pos < 5 || x_pos > 230 ){
	y_pos=y_pos_old;
	x_pos=x_pos_old;
	x_speed=-x_speed;
	upgrade_punteggio(0);
	enable_timer(1);
	init_timer(1,1062);
		
	
	}	
	
	if(y_pos>=273){ /* FONDO*/
		
		if(x_pos<Paddle_Pos-6 || x_pos > Paddle_Pos+PaddleSize+1){
		DrawBall(x_pos_old,y_pos_old,x_pos,y_pos);
		Continue_Run();
		}
		else{
		
		y_pos=y_pos_old;
		x_pos=x_pos_old;
		
			/*Se pallina e racchetta sono concordi il rimbalzo avrà direzione concorde al movimento di entrambe 63-45-26° al centro e 20-26 all'esterno
			Ciò equivale ad un colpo dritto nel pingpong
			Se invece pallina e racchetta hanno direzione discorde come un colpo rovescio nel ping pong la direzione sarà simile a quella di arrivo
			ma con verso opposto, inoltre un colpo con la parte più esterna della racchetta avrà un angolazione di 15 o 20°  con velocità superiore*/
			if(From_sx_Ball==1){
			
			if(From_sx_Paddle==1){ //Dritto
													if(x_pos>=Paddle_Pos+4 && x_pos<=Paddle_Pos+36){
																																					Random=AD_last%3;
																																					y_speed=-2*no;
																																					x_speed=+2*no;									
														switch(Random){case 1: y_speed++; break;
																					 case 3: x_speed--; break;}}
													
													else{Random=AD_last%2;
																y_speed=-no; x_speed=2*no+Random;} }
			
			
			if(From_sx_Paddle==0){ //Rovescio
														if(x_pos>=Paddle_Pos+4 && x_pos<=Paddle_Pos+36){
																																					Random=AD_last%3;
																																					y_speed=-2*no;
																																					x_speed=-2*no;								
									
														switch(Random){case 1: y_speed++; break;
																					 case 3: x_speed++; break;}}
														
													else{
																Random=AD_last%2;	
																y_speed=-no; x_speed=-3*no-Random;}}
			
			
			
													}
		
		else {
			
			if(From_sx_Paddle==1){ //Rovescio
													if(x_pos>=Paddle_Pos+4 && x_pos<=Paddle_Pos+36){Random=AD_last%3;
																																					y_speed=-2*no;
																																					x_speed=+2*no;																		
														switch(Random){case 1: y_speed++; break;
																					 case 3: x_speed--; break;}}
													else{Random=AD_last%2;
															 y_speed=-no; 
															 x_speed=3*no+Random;} }
			
			if(From_sx_Paddle==0){ //Dritto
													if(x_pos>=Paddle_Pos+4 && x_pos<=Paddle_Pos+36){Random=AD_last%3;
																																					y_speed=-2*no;
																																					x_speed=-2*no;																		
														switch(Random){case 1: y_speed++; break;
																					 case 3: x_speed++; break;}}
													
													else{Random=AD_last%2;
															 y_speed=-no; 
															 x_speed=-2*no-Random;}}
			
		}
		

		
		
		
		upgrade_punteggio(1);
		enable_timer(1);
		init_timer(1,2120);
		}
		
	
	
	}
	
	DrawBall(x_pos_old,y_pos_old,x_pos,y_pos);
}

void DrawPaddle(unsigned short Last_pos, unsigned short Pos){
	
	uint8_t i;
	if(Paddle_Pos!=Temp){
	Temp=Paddle_Pos;
	Count=1;
	}
	else{
	Count++;}
	
	if(Count==5){
		Last_Racc=Racc;
		Racc=Temp;
		
	if(Last_Racc<Racc){From_sx_Paddle=1;}
	else From_sx_Paddle=0;

	for(i=0;i<10;i++)	LCD_DrawLine(Last_Racc+5,i+278, Last_Racc+5+PaddleSize, i+278, Black);
	for(i=0;i<10;i++) LCD_DrawLine(Racc+5,i+278, Racc+5+PaddleSize, i+278, Green);
	
	}
	return;
}


void DrawBall(uint16_t xpos_old, uint16_t ypos_old, uint16_t xpos, uint16_t ypos){
	unsigned short i;
	
	
	for(i=0;i<5;i++) LCD_DrawLine(xpos_old, ypos_old + i , xpos_old+5, ypos_old+i, Black);
	for(i=0;i<5;i++)LCD_DrawLine(xpos, ypos + i , xpos+5, ypos+i, Green);	
	}
	
void Game_over(void){

	
	GUI_Text_SIZED(40, 120, (uint8_t *) "GAME OVER!", Magenta, Black,2);
	upgrade_punteggio(2);
	GUI_Text(0, 166, (uint8_t *) "Press KEY0 to restart the game", Green, White);
	
	if(punteggio>record){record=punteggio; 
	GUI_Text_SIZED(40, 200, (uint8_t *) "New Record!", Yellow, Black,2);}
	Play=0;
	return;
};

void Continue_Run(void){
	
	int i=1;
	while(i){
	DrawPaddle(Paddle_Last_pos,Paddle_Pos);
	x_pos_old=x_pos;
	y_pos_old=y_pos;
	x_pos+=x_speed;
	y_pos+=y_speed;
	
	if(y_pos < 5 ){
	y_pos=y_pos_old;
	x_pos=x_pos_old;
	y_speed=-y_speed;
	}
	if(x_pos < 5 || x_pos > 230 ){
	y_pos=y_pos_old;
	x_pos=x_pos_old;
	x_speed=-x_speed;
	}	
	
	DrawBall(x_pos_old,y_pos_old,x_pos,y_pos);
	
	if(y_pos>=315){
		Game_over();
	i=0;
	}
	}
	return;
}

void upgrade_punteggio(uint8_t flag){

	char string_record[10];
	if(flag==1){
	if(punteggio<100) punteggio+=5;
	else punteggio+=10;
	}
	sprintf(string_record, "%d", punteggio);
	GUI_Text_SIZED(8, 160, (uint8_t *) string_record , White, Black, 2 );
	
	
	if(flag==2){
	GUI_Text_SIZED(8, 160, (uint8_t *) string_record , Black, Black, 2 );
	}
	
	
};
