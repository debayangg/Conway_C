CC=gcc
play: game.c settings.h keybindings.h
	${CC} game.c -o play -lncurses
clean:
	rm play
.PHONY:clean
