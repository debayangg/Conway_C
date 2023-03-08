#include<ncurses.h>
#include<stdlib.h>
#include<stdbool.h>
#include<pthread.h>
//load configs
#include"settings.h"
//load functions
#include"controls.h"
#include"ui.h"
#include"game.h"
//globals
WINDOW* surface;char* cells;
unsigned short cursor_x,cursor_y;
bool playing;
int main(){
	surface=initscr();//create surface
	noecho();//do not show keys
	cells=(char*)calloc((COLUMNS/8+1+2*PADDING)*(ROWS+2*PADDING),1);
	for(short i=0;i<=(ROWS+1)*(COLUMNS+1);i++)
			addch(DEAD);
	unsigned short cursor_x=0,cursor_y=0;
	move(0,0);
	pthread_t ui_thread;
	pthread_create(&ui_thread,NULL,ui,NULL);
	playing=false;
	game();
	pthread_join(ui_thread,NULL);
}
