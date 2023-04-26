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
				if(cursor_x<columns)
					move(cursor_y,++cursor_x);
				else
					move(cursor_y,cursor_x=0);
				break;
			case JUMP_RIGHT:
				if(cursor_x+JUMP_DISTANCE<columns)
					move(cursor_y,cursor_x+=JUMP_DISTANCE);
				else if(cursor_x=columns)
					move(cursor_y,cursor_x=0);
				else 
					move(cursor_y,cursor_x=columns);
				break;
			case END:
				move(cursor_y,cursor_x=columns);
				break;
			case MOVE_LEFT:
				if(cursor_x>0)
					move(cursor_y,--cursor_x);
				else
					move(cursor_y,cursor_x=columns);
				break;
			case JUMP_LEFT:
				if(cursor_x-JUMP_DISTANCE>0)
					move(cursor_y,cursor_x-=JUMP_DISTANCE);
				else if(cursor_x==0)
					move(cursor_y,cursor_x=columns);
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
					move(cursor_y=rows,cursor_x);
				break;
			case JUMP_UP:
				if(cursor_y-JUMP_DISTANCE>0)
					move(cursor_y-=JUMP_DISTANCE,cursor_x);
				else if(cursor_y==0)
					move(cursor_y=rows,cursor_x);
				else
					move(cursor_y=0,cursor_x);
				break;
			case TOP:
				move(cursor_y=0,cursor_x);
				break;
			case MOVE_DOWN:
				if(cursor_y>rows)
					move(cursor_y=0,cursor_x);
				else
					move(++cursor_y,cursor_x);
				break;
			case JUMP_DOWN:
				if(cursor_y+JUMP_DISTANCE<rows)
					move(cursor_y+=JUMP_DISTANCE,cursor_x);
				else if(cursor_y=rows)
					move(cursor_y=0,cursor_x);
				else
					move(cursor_y=rows,cursor_x);
				break;
			case BOTTOM:
				move(cursor_y=rows,cursor_x);
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
			case FASTER:
				frame_speed*=(1.0-SPEED_CHANGE);
				break;
			case SLOWER:
				frame_speed*=(1.0+SPEED_CHANGE);
				break;
			case DEFAULT_SPEED:
				frame_speed=1.0/DEFAULT_FPS;
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
	}
	endwin();//clean terminal
	curs_set(1);//make cursor normal
}
