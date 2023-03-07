#include<ncurses.h>
#include"settings.h"
#include"keybindings.h"
#include"controls.h"
void* ui(void* arg){
	char running=1;
	while(running){
		switch(getch()){
			case QUIT:
				running=0;
				break;
			case MOVE_RIGHT:
				if(cursor_x<COLUMNS)
					move(cursor_y,++cursor_x);
				else
					move(cursor_y,cursor_x=0);
				break;
			case JUMP_RIGHT:
				if(cursor_x+JUMP_DISTANCE<COLUMNS)
					move(cursor_y,cursor_x+=JUMP_DISTANCE);
				else if(cursor_x=COLUMNS)
					move(cursor_y,cursor_x=0);
				else 
					move(cursor_y,cursor_x=COLUMNS);
				break;
			case END:
				move(cursor_y,cursor_x=COLUMNS);
				break;
			case MOVE_LEFT:
				if(cursor_x>0)
					move(cursor_y,--cursor_x);
				else
					move(cursor_y,cursor_x=COLUMNS);
				break;
			case JUMP_LEFT:
				if(cursor_x-JUMP_DISTANCE>0)
					move(cursor_y,cursor_x-=JUMP_DISTANCE);
				else if(cursor_x==0)
					move(cursor_y,cursor_x=COLUMNS);
				else
					move(cursor_y,cursor_x=0);
				break;
			case BEGINNING:
				move(cursor_y,cursor_x=0);
				break;
			case MOVE_UP:
				if(cursor_y>0)
					move(--cursor_y,cursor_x);
				else
					move(cursor_y=ROWS,cursor_x);
				break;
			case JUMP_UP:
				if(cursor_y-JUMP_DISTANCE>0)
					move(cursor_y-=JUMP_DISTANCE,cursor_x);
				else if(cursor_y==0)
					move(cursor_y=ROWS,cursor_x);
				else
					move(cursor_y=0,cursor_x);
				break;
			case TOP:
				move(cursor_y=0,cursor_x);
				break;
			case MOVE_DOWN:
				if(cursor_y>ROWS)
					move(cursor_y=0,cursor_x);
				else
					move(++cursor_y,cursor_x);
				break;
			case JUMP_DOWN:
				if(cursor_y+JUMP_DISTANCE<ROWS)
					move(cursor_y+=JUMP_DISTANCE,cursor_x);
				else if(cursor_y=ROWS)
					move(cursor_y=0,cursor_x);
				else
					move(cursor_y=ROWS,cursor_x);
				break;
			case BOTTOM:
				move(cursor_y=ROWS,cursor_x);
				break;
			case CHANGE:
				if(is_alive(PADDING+cursor_y,PADDING+cursor_x)){
					death(PADDING+cursor_y,PADDING+cursor_x);
					addch(DEAD);
				}
				else{
					birth(PADDING+cursor_y,PADDING+cursor_x);
					addch(ALIVE);
				}
				move(cursor_y,cursor_x);
				break;
		}
		refresh();
	}
	endwin();//clean terminal
}
