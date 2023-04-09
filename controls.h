#ifndef CONTROLS_H
#define CONTROLS_H

//macros
#define ALIVE_COLOR 1
#define DEAD_COLOR 2
//variables
extern WINDOW* surface;extern char* cells;
extern unsigned short rightmost,bottommost,rows,columns;
bool is_alive(unsigned short row,unsigned short column);
void death(unsigned short row,unsigned short column);
void birth(unsigned short row,unsigned short column);

#endif
