#include<ncurses.h>
#include<stdbool.h>
#include"ui.h"
#include"settings.h"
#include"keybindings.h"
#include"controls.h"
void* ui(void* arg){
	while(running){
		switch(getch()){//respond to input
			case QUIT:
				running=FALSE;
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
				if(playing)
					break;
				else if(is_alive(PADDING+cursor_y,PADDING+cursor_x)){
					death(PADDING+cursor_y,PADDING+cursor_x);
					attron(COLOR_PAIR(DEAD_COLOR));
					addch(DEAD);
				}
				else{
					birth(PADDING+cursor_y,PADDING+cursor_x);
					attron(COLOR_PAIR(ALIVE_COLOR));
					addch(ALIVE);
				}
				move(cursor_y,cursor_x);
				break;
			case PLAY_PAUSE:
				curs_set(playing);//change cursor visibility
				playing=1-playing;
				if(!playing)
					move(cursor_y,cursor_x);
				break;
			case NEXT:
				if(!playing){
					stepping=true;
					curs_set(0);
				}
				break;
		}
		refresh();
		//TODO: prepare for size change events
	}
	endwin();//clean terminal
	curs_set(1);//make cursor normal
}
