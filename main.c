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
double frame_speed;
bool playing,running,stepping;
unsigned short RIGHTMOST,BOTTOMMOST;
int main(){
	surface=initscr();//create surface
	start_color();//allow colors
	use_default_colors();//terminal transparency
	noecho();//do not show keys
	RIGHTMOST=COLUMNS+2*PADDING;
	BOTTOMMOST=ROWS+2*PADDING;
	init_pair(ALIVE_COLOR,ALIVE_FOREGROUND,ALIVE_BACKGROUND);
	init_pair(DEAD_COLOR,DEAD_FOREGROUND,DEAD_BACKGROUND);
	cells=(char*)calloc((RIGHTMOST/8+1)*(BOTTOMMOST),1);
	attron(COLOR_PAIR(DEAD_COLOR));
	for(short i=0;i<=(ROWS+1)*(COLUMNS+1);i++)
			addch(DEAD);
	unsigned short cursor_x=0,cursor_y=0;
	move(0,0);
	pthread_t ui_thread;
	pthread_create(&ui_thread,NULL,ui,NULL);
	playing=false,running=true;stepping=false;
	frame_speed=1.0/DEFAULT_FPS;
	game();
	pthread_join(ui_thread,NULL);
}
