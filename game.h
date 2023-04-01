#ifndef GAME_H
#define GAME_H

extern WINDOW* surface;extern char* cells;
extern bool playing,running,stepping;
extern unsigned short cursor_y,cursor_x;
extern double frame_speed;
void game();

#endif
