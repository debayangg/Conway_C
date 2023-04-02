#include<ncurses.h>
#include<stdbool.h>
#include<time.h>
#include<stdlib.h>
#include"settings.h"
#include"controls.h"
#include"game.h"
#define IF_ONSCREEN() if(PADDING<=tail->row && tail->row<=ROWS+PADDING && PADDING<=tail->column && tail->column<=COLUMNS+PADDING)
typedef struct Change{//linked list node
	bool new_state;
	unsigned short row,column;
	struct Change* previous;
} Change;
unsigned short STRUCT_SIZE;
Change* tail;
void rules(unsigned short row,unsigned short column,unsigned char neighbours){
	if(is_alive(row,column)){
		if(neighbours<2 || neighbours>3){//underpopulation or overpopulation
			Change* change=(Change*)malloc(STRUCT_SIZE);
			change->row=row;change->column=column;
			change->new_state=false;//die
			change->previous=tail;
			tail=change;
		}
	}
	else if(neighbours==3){//reproduction
		Change* change=(Change*)malloc(STRUCT_SIZE);
		change->row=row;change->column=column;
		change->new_state=true;//be born
		change->previous=tail;
		tail=change;
	}
}
void game(){
	clock_t begin_frame;
	double sleep_time;
	struct timespec sleep_arg;
	tail=NULL;
	STRUCT_SIZE=sizeof(Change);
	while(running){
		begin_frame=clock();
		if(playing || stepping){
			//plan next frame, store Changes
				//corners
			rules(0,0,is_alive(0,1)+is_alive(1,1)+is_alive(1,0));//top left
			rules(0,RIGHTMOST,is_alive(0,RIGHTMOST-1)+is_alive(1,RIGHTMOST-1)+is_alive(1,RIGHTMOST));//top right
			rules(BOTTOMMOST,0,is_alive(BOTTOMMOST,1)+is_alive(BOTTOMMOST-1,1)+is_alive(BOTTOMMOST-1,0));//bottom left
			rules(BOTTOMMOST,RIGHTMOST,is_alive(BOTTOMMOST,RIGHTMOST-1)+is_alive(BOTTOMMOST-1,RIGHTMOST-1)+is_alive(BOTTOMMOST-1,RIGHTMOST));//bottom right
				//borders
			for(short i=1;i<RIGHTMOST;){//horizontal borders
				rules(0,i,
					is_alive(0,i-1)+//left
					is_alive(1,i-1)+//bottom left
					is_alive(1,i)+//bottom
					is_alive(1,i+1)+//bottom right
					is_alive(0,i+1)//right
				);//top border
				rules(BOTTOMMOST,i,
					is_alive(BOTTOMMOST,i-1)+//left
					is_alive(BOTTOMMOST-1,i-1)+//top left
					is_alive(BOTTOMMOST-1,i)+//top
					//'i' is incremented
					is_alive(BOTTOMMOST-1,++i)+//top right
					is_alive(BOTTOMMOST,i)//right
				);//bottom border
			}
			for(short i=1;i<BOTTOMMOST;){//vertical borders
				rules(i,0,
					is_alive(i-1,0)+//top
					is_alive(i-1,1)+//top right
					is_alive(i,1)+//right
					is_alive(i+1,1)+//bottom right
					is_alive(i+1,0)//bottom
				);//left border
				rules(BOTTOMMOST,i,
					is_alive(i-1,RIGHTMOST)+//top
					is_alive(i-1,RIGHTMOST-1)+//top left
					is_alive(i,RIGHTMOST-1)+//left
					//'i' is incremented
					is_alive(++i,RIGHTMOST-1)+//bottom left
					is_alive(i,RIGHTMOST)//bottom
				);//right border
			}
				//interior
			for(short i=1;i<BOTTOMMOST;i++)
				for(short j=1;j<RIGHTMOST;j++)
					rules(i,j,
						is_alive(i-1,j-1)+//top left,
						is_alive(i-1,j)+//left,
						is_alive(i-1,j+1)+//bottom left,
						is_alive(i,j+1)+//bottom
						is_alive(i,j-1)+//top
						//'i' is incremented
						is_alive(i+1,j+1)+//bottom right
						is_alive(i+1,j)+//right
						is_alive(i+1,j-1)//top right
					);
			//create new generation
			while(tail!=NULL){
				Change* new_tail;
				if(tail->new_state){//cell alive on grid
					birth(tail->row,tail->column);
					IF_ONSCREEN(){
						attron(COLOR_PAIR(ALIVE_COLOR));
						mvaddch(tail->row-PADDING,tail->column-PADDING,ALIVE);
					}
				}
				else{//cell dead on grid
					death(tail->row,tail->column);
					IF_ONSCREEN(){
						attron(COLOR_PAIR(DEAD_COLOR));
						mvaddch(tail->row-PADDING,tail->column-PADDING,DEAD);
					}
				}
				new_tail=tail->previous;
				free(tail);
				tail=new_tail;
			}
			if(stepping){
				stepping=false;
				curs_set(1);
				move(cursor_y,cursor_x);
			}
			refresh();
		}
		sleep_time=frame_speed-((double)(clock()-begin_frame))/CLOCKS_PER_SEC;
		sleep_arg.tv_sec=(int)sleep_time;sleep_arg.tv_nsec=(long)((sleep_time-sleep_arg.tv_sec)*1000000000);
		nanosleep(&sleep_arg,NULL);
	}
}
