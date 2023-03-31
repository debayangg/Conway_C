#ifndef CONTROLS_H
#define CONTROLS_H

//macros
#define ROWS surface->_maxy
#define COLUMNS surface->_maxx
//variables
extern WINDOW* surface;extern char* cells;
extern unsigned short RIGHTMOST,BOTTOMMOST;
bool is_alive(unsigned short row,unsigned short column);
void death(unsigned short row,unsigned short column);
void birth(unsigned short row,unsigned short column);

#endif
