CC=gcc
LIBS=-lncurses -lpthread
controls.o: controls.c controls.h
	${CC} -c controls.c -o controls.o
ui.o: ui.c ui.h
	${CC} -c ui.c -o ui.o
play: game.c controls.o ui.o settings.h keybindings.h
	${CC} game.c controls.o ui.o -o play ${LIBS}
clean:
	rm controls.o ui.o play
.PHONY:clean
