#include "Game_functions.h"
#include "RIT.h"
#include "button.h"
#include "stdlib.h"

//240*320

volatile uint8_t punteggio, punteggio2;
volatile unsigned short PaddleSize=50;

uint16_t x_pos, y_pos ,x_pos_old, y_pos_old;
int16_t x_speed, y_speed, normal_s, previsto, future_x, difficult;
uint8_t From_sx_Paddle, From_sx_Ball, Temp, Last_Racc=0,Racc, Count, Random;
unsigned short top_paddle, top_paddle_size, top_paddle_mov, top_paddle_sx;
float rnd;


extern unsigned short Paddle_Last_pos, Paddle_Pos, AD_last;
extern uint8_t Play;

void MainPage(void){
	
	
	LCD_Clear(Black);
	//x,y,frase,background,colore
	GUI_Text_SIZED(10, 100, (uint8_t *) " PONG! ", Yellow, Black,4);
	GUI_Text(0, 180, (uint8_t *) " Press KEY1 to start the game ", Green, White);
return;
}

void NewGame(void){
	punteggio=0;
	punteggio2=0;
	top_paddle=95;
	top_paddle_size=50;
	top_paddle_mov=1;
	
	/*****************************************************/
	/*Aumentando "normal_s" si aumenta o diminuisce la velocità normale 1=semplice 2=difficile 3=estremo*/
	/*Aumentando difficult si aumenta la capacità della cpu di prevedere dove finirà la pallina e conseguente*/
	/*tempo per spostare la racchetta e colpire la palla. 160 è già un livello complesso, dopo i 180 è quasi impossibile*/
	difficult=160;
	normal_s=2;
	/*******************************************************/
	x_pos=229;
	y_pos=155;
	x_speed=-normal_s;
	y_speed=normal_s;
	
	MakeField();
}

void MakeField(void){
	
	uint8_t i;
	
	LCD_Clear(Black);
	
	for(i=0;i<5;i++){
	//LCD_DrawLine( 0, i, MAX_X, i, Red);
	LCD_DrawLine( i, 0, i, MAX_Y, Red);
	LCD_DrawLine( MAX_X+i-4, 0, MAX_X+i-4, MAX_Y, Red);
}
	
	upgrade_punteggio(0);
	
	DrawPaddleBottom(Paddle_Last_pos,Paddle_Pos);
	DrawFirstTopPaddle(top_paddle);

top_paddle_sx=1;


	return;
}

void DrawFirstTopPaddle(unsigned short top_paddle){
	unsigned short i;
	
for(i=0;i<10;i++){LCD_DrawLine(5,32+i,234,32+i,Black);
									LCD_DrawLine(top_paddle,32+i,top_paddle+PaddleSize,32+i,Green);
									}
}

void Pause(void){

LCD_Clear(Black);

GUI_Text_SIZED(65, 120, (uint8_t *) " PAUSE ", Yellow, Black,2);
GUI_Text(0, 180, (uint8_t *) "Press KEY1 to restart the game", Green, White);
GUI_Text(0, 200, (uint8_t *) "Press KEY2 to resume the game ", Cyan, White);

	return;
}


void GameLogic(void){
	
		
	
	DrawPaddleBottom(Paddle_Last_pos,Paddle_Pos);
	
	/*Se la palla va verso il paddle della cpu prevedo dove andrà a finire*/	
if(y_pos<difficult && y_speed<0){ if(previsto==0){Prevedi_x();} 
															DrawPaddleTop();}
	
	x_pos_old=x_pos;
	y_pos_old=y_pos;
	x_pos+=x_speed;
	y_pos+=y_speed;
	
	if(x_pos_old<x_pos) From_sx_Ball=1;
	else From_sx_Ball=0;
	
	/*Top paddle*/
	if(y_pos < 42 ){
	
	if(x_pos<top_paddle-6 || x_pos > top_paddle+PaddleSize+1){
		DrawBall(x_pos_old,y_pos_old,x_pos,y_pos);
		Continue_Run();
		}else{
		
		y_pos=y_pos_old;
		x_pos=x_pos_old;
			
			if(From_sx_Ball==1){
			if(top_paddle_sx==1){ //Dritto
													if(x_pos>=top_paddle+4 && x_pos<=top_paddle+36){
																																					Random=AD_last%3;
																																					y_speed=+2*normal_s;
																																					x_speed=+2*normal_s;									
														switch(Random){case 0: y_speed--; break;
																					 case 1: x_speed--; y_speed--; break;
																					 case 2: x_speed--; break;}}
													
													else{Random=AD_last%2;
																y_speed=+normal_s; x_speed=2*normal_s+Random;} }
			if(top_paddle_sx==0){ //Rovescio
														if(x_pos>=top_paddle+4 && x_pos<=top_paddle+36){
																																					Random=AD_last%3;
																																					y_speed=2*normal_s;
																																					x_speed=-2*normal_s;								
														switch(Random){case 0: y_speed--; break;
																					 case 1: x_speed++; y_speed--; break;
																					 case 2: x_speed++; break;}}
													else{
																Random=AD_last%2;	
																y_speed=+normal_s; x_speed=-3*normal_s-Random;}}
			}
		else {
			if(top_paddle_sx==1){ //Rovescio
													if(x_pos>=top_paddle+4 && x_pos<=top_paddle+36){Random=AD_last%3;
																																					y_speed=+2*normal_s;
																																					x_speed=+2*normal_s;																		
														switch(Random){case 0: y_speed--; break;
																					 case 1: x_speed--; y_speed--; break; 
																					 case 2: x_speed--; break;}}
													else{Random=AD_last%2;
															 y_speed=+normal_s; 
															 x_speed=3*normal_s+Random;} }
			if(top_paddle_sx==0){ //Dritto
													if(x_pos>=top_paddle+4 && x_pos<=top_paddle+36){Random=AD_last%3;
																																					y_speed=2*normal_s;
																																					x_speed=-2*normal_s;																		
														switch(Random){case 0: y_speed--; break;
																					 case 1: x_speed++; y_speed--; break;
																					 case 3: x_speed++; break;}}
													else{Random=AD_last%2;
															 y_speed=normal_s; 
															 x_speed=-2*normal_s-Random;}}
			
		}
	previsto=0;
	upgrade_punteggio(0);
		}
	}
	/*Walls*/
	if(x_pos < 5 || x_pos > 230 ){
	y_pos=y_pos_old;
	x_pos=x_pos_old;
	x_speed=-x_speed;
	upgrade_punteggio(0);
		
	
	}	
	/*Bottom paddle*/
	if(y_pos>=273){ 
		
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
																																					y_speed=-2*normal_s;
																																					x_speed=+2*normal_s;									
														switch(Random){case 0: y_speed++; break;
																					 case 1: x_speed--; y_speed++; break;
																					 case 2: x_speed--; break;}}
													
													else{Random=AD_last%2;
																y_speed=-normal_s; x_speed=2*normal_s+Random;} }
			if(From_sx_Paddle==0){ //Rovescio
														if(x_pos>=Paddle_Pos+4 && x_pos<=Paddle_Pos+36){
																																					Random=AD_last%3;
																																					y_speed=-2*normal_s;
																																					x_speed=-2*normal_s;								
														switch(Random){case 0: y_speed++; break;
																					 case 1: x_speed++; y_speed++; break;
																					 case 2: x_speed++; break;}}
													else{
																Random=AD_last%2;	
																y_speed=-normal_s; x_speed=-3*normal_s-Random;}}
			}
		else {
			if(From_sx_Paddle==1){ //Rovescio
													if(x_pos>=Paddle_Pos+4 && x_pos<=Paddle_Pos+36){Random=AD_last%3;
																																					y_speed=-2*normal_s;
																																					x_speed=+2*normal_s;																		
														switch(Random){case 0: y_speed++; break;
																					 case 1: x_speed--; y_speed++; break; 
																					 case 2: x_speed--; break;}}
													else{Random=AD_last%2;
															 y_speed=-normal_s; 
															 x_speed=3*normal_s+Random;} }
			if(From_sx_Paddle==0){ //Dritto
													if(x_pos>=Paddle_Pos+4 && x_pos<=Paddle_Pos+36){Random=AD_last%3;
																																					y_speed=-2*normal_s;
																																					x_speed=-2*normal_s;																		
														switch(Random){case 0: y_speed++; break;
																					 case 1: x_speed++; y_speed++; break;
																					 case 3: x_speed++; break;}}
													else{Random=AD_last%2;
															 y_speed=-normal_s; 
															 x_speed=-2*normal_s-Random;}}
			
		}
	upgrade_punteggio(0);
		}
		
	
	}
	
	DrawBall(x_pos_old,y_pos_old,x_pos,y_pos);
}

void DrawPaddleBottom(unsigned short Last_pos, unsigned short Pos){
	
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



void DrawPaddleTop(void){
	
	if((top_paddle+25)>future_x){
												if(top_paddle >=5){
												LCD_DrawLine(top_paddle-1,32,top_paddle-1,41,Green);
												LCD_DrawLine(top_paddle+top_paddle_size,32,top_paddle+top_paddle_size,41,Black);
												top_paddle_sx=0;
												top_paddle--;}
	}else if((top_paddle+25)<future_x){
												if(top_paddle+top_paddle_size<235){
												LCD_DrawLine(top_paddle,32,top_paddle,41,Black);
												LCD_DrawLine(top_paddle+top_paddle_size+1,32,top_paddle+top_paddle_size+1,41,Green);
												top_paddle_sx=1;
												top_paddle++;
												}
	}return;
}

/*Intelligenza della cpu*/

void Prevedi_x(void){

int16_t temp_x, temp_y, t_speed_x, t_speed_y;
	temp_x=x_pos;	
	temp_y=y_pos;
	t_speed_x=x_speed;
	t_speed_y=y_speed;
	
	while(1){
  temp_x+=t_speed_x;
	temp_y+=t_speed_y;
	
	if(temp_y < 42 ){
		previsto=1;
		future_x=temp_x;
		return;
	}
	
	if(temp_x < 5 || temp_x > 230 ){
		
	temp_y=temp_y-t_speed_y;
	temp_x=temp_x-t_speed_x;
	
	t_speed_x=-t_speed_x;
	}	
}
};

void DrawBall(uint16_t xpos_old, uint16_t ypos_old, uint16_t xpos, uint16_t ypos){
	unsigned short i;
	
	
	for(i=0;i<5;i++) LCD_DrawLine(xpos_old, ypos_old + i , xpos_old+5, ypos_old+i, Black);
	for(i=0;i<5;i++)LCD_DrawLine(xpos, ypos + i , xpos+5, ypos+i, Green);	
	}
	
void Game_over(unsigned short flag){
	
	switch(flag){
		case 1: 
						upgrade_punteggio(3);
						GUI_Text_SIZED(40, 210, (uint8_t *) " YOU WIN!", Cyan, Black,2);
						GUI_Text_SIZED(40, 60, (uint8_t *) " CPU LOSE!", Magenta, Black,2);
						
						break;
		case 2: 
						upgrade_punteggio(3);
						GUI_Text_SIZED(40, 210, (uint8_t *) " YOU LOSE!", Magenta, Black,2);
						GUI_Text_SIZED(40, 60, (uint8_t *) " CPU WIN!", Cyan, Black,2);
						break;
	}
	
	
	GUI_Text(0, 160, (uint8_t *) "Press KEY0 to restart the game", Green, White);
	Play=0;
	return;
};

/*La palla ha superato la racchetta*/

void Continue_Run(void){
	
	int i=1;
	while(i){
	DrawPaddleBottom(Paddle_Last_pos,Paddle_Pos);
	x_pos_old=x_pos;
	y_pos_old=y_pos;
	x_pos+=x_speed;
	y_pos+=y_speed;
	
	
	if(x_pos < 5 || x_pos > 230 ){
	y_pos=y_pos_old;
	x_pos=x_pos_old;
	x_speed=-x_speed;
	}	
	
	DrawBall(x_pos_old,y_pos_old,x_pos,y_pos);
	
	if(y_pos>=315){
		upgrade_punteggio(2);
	i=0;
	NewSet(0);
	}else if(y_pos<=5){
	DrawFirstTopPaddle(top_paddle);
	upgrade_punteggio(1);
		i=0;
	NewSet(1);
	}
	}
	if(Play==1){upgrade_punteggio(0);GameLogic();}
	return;
}

void upgrade_punteggio(uint8_t flag){

	char string_record[10];
	sprintf(string_record, "%d", punteggio);
	
	switch(flag){
		case 0: GUI_Text_SIZED(8, 160, (uint8_t *) string_record , White, Black, 2 );
						sprintf(string_record, "%d", punteggio2);
						GUI_Text_SIZED(214, 160, (uint8_t *) string_record , White, Black, 2 );
						break;
		
		
		case 1: punteggio+=1;
						GUI_Text_SIZED(8, 160, (uint8_t *) string_record , White, Black, 2 );
						if(punteggio==5) Game_over(1);
						break;
		case 2: punteggio2+=1;
						sprintf(string_record, "%d", punteggio2);
						GUI_Text_SIZED(214, 160, (uint8_t *) string_record , White, Black, 2 );
						if(punteggio2==5) Game_over(2);
						break;
		case 3: /*Delete punteggi*/
						GUI_Text_SIZED(8, 160, (uint8_t *) string_record , Black, Black, 2 );
						sprintf(string_record, "%d", punteggio2);
						GUI_Text_SIZED(214, 160, (uint8_t *) string_record , Black, Black, 2 );
						
						break;
		}
	};

	/*Uno dei player ha fatto punto*/
void NewSet(unsigned short flag){
	unsigned short i;
	
	for(i=0;i<5;i++) LCD_DrawLine( x_pos, y_pos+i, x_pos+5,y_pos+i,Black);
	
	x_pos=229;
	y_pos=155;
switch(flag){
	
	case 0: 
					x_speed=-normal_s;
					y_speed=+normal_s;
					break;
	case 1: 
					x_speed=-normal_s;
					y_speed=-normal_s;
					break;

}

previsto=0;
return;
}
