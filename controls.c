#include<ncurses.h>
#include<stdbool.h>
#include"controls.h"
#include"settings.h"
bool is_alive(unsigned short row,unsigned short column){
	char det=1<<7-(column-1)%8;
	return (cells[row*RIGHTMOST+column/8] & det)==det;
}
void death(unsigned short row,unsigned short column){
	unsigned short pointer=row*RIGHTMOST+column/8;
	cells[pointer]=cells[pointer] ^ 0x1<<7-(column-1)%8;
}
void birth(unsigned short row,unsigned short column){
	unsigned short pointer=row*RIGHTMOST+column/8;
	cells[pointer]=cells[pointer] | 0x1<<7-(column-1)%8;
}
