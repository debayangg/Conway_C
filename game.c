#include<ncurses.h>
#include<stdlib.h>
//load configs
#include "keybindings.h"
#include "settings.h"
//macros
#define ROWS surface->_maxy
#define COLUMNS surface->_maxx
int main(){
	WINDOW* surface=initscr();//create surface
	noecho();//do not show keys
	char running=1;
	char* cells=(char*)calloc((COLUMNS/8+1+2*PADDING)*(ROWS+2*PADDING),1);
	for(short i=0;i<=(ROWS+1)*(COLUMNS+1);i++)
			addch(DEAD);
	unsigned short cursor_x=0,cursor_y=0;
	move(0,0);
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
		}
		refresh();
	}
	endwin();//clean terminal
}
