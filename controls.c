#include<ncurses.h>
#include"controls.h"
#include"settings.h"
unsigned char is_alive(unsigned short row,unsigned short column){
	char det=1<<8-column%8;
	return (cells[row*(COLUMNS+2*PADDING)+column/8] & det)==det;
}
void death(unsigned short row,unsigned short column){
	unsigned short pointer=row*(COLUMNS+2*PADDING)+column/8;
	cells[pointer]=cells[pointer] ^ 0x01<<8-column%8;
}
void birth(unsigned short row,unsigned short column){
	unsigned short pointer=row*(COLUMNS+2*PADDING)+column/8;
	cells[pointer]=cells[pointer] | 0x01<<8-column%8;
}
