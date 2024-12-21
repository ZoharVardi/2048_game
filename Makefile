CC=gcc
OBJS=game.o game_functions.o input.o output.o main.o
EXEC=hw1_2048
DEBUG=-g
CFLAGS=-std=c99 -Wall -Werror $(DEBUG)

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@

game.o: game.c game.h output.h input.h game_functions.h
game_functions.o: game_functions.c game_functions.h
input.o: input.c input.h game.h
output.o: output.c output.h game.h
main.o: main.c game.h

clean:
	rm -f $(OBJS) $(EXEC)

