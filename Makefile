CC=gcc
LIBS=-lncurses -lpthread
play: main.c controls.o ui.o game.o settings.h keybindings.h
	${CC} main.c controls.o ui.o game.o -o play ${LIBS}
controls.o: controls.c controls.h
	${CC} -c controls.c -o controls.o
game.o: game.c game.h
	${CC} -c game.c -o game.o
ui.o: ui.c ui.h keybindings.h
	${CC} -c ui.c -o ui.o
clean:
	rm controls.o ui.o game.o play
.PHONY:clean
