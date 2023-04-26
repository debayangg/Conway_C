CC=gcc
LIBS=-lncurses -lpthread
play: main.c controls.o ui.o game.o settings.h keybindings.h
	${CC} main.c controls.o ui.o game.o -o play ${LIBS}
debug: main.c controls_debug.o ui_debug.o game_debug.o settings.h keybindings.h
	${CC} main.c controls_debug.o ui_debug.o game_debug.o -o debug ${LIBS}
controls_debug.o: controls.c controls.h settings.h
	${CC} -ggdb3 -c controls.c -o controls_debug.o
game_debug.o: game.c game.h settings.h controls_debug.o
	${CC} -ggdb3 -c game.c -o game_debug.o
ui_debug.o: ui.c ui.h keybindings.h
	${CC} -ggdb3 -c ui.c -o ui_debug.o
controls.o: controls.c controls.h settings.h
	${CC} -c controls.c -o controls.o
game.o: game.c game.h settings.h controls.o
	${CC} -c game.c -o game.o
ui.o: ui.c ui.h keybindings.h
	${CC} -c ui.c -o ui.o
clean:
	rm controls.o ui.o game.o controls_debug.o game_debug.o ui_debug.o play debug
.PHONY:clean
