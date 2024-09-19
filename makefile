OBJS	= main.o lib/grid.o lib/colors.o lib/Position.o lib/blocks.o lib/Block.o lib/game.o
SOURCE	= main.cpp lib/grid.cpp lib/colors.cpp lib/Position.cpp lib/blocks.cpp lib/Block.cpp lib/game.cpp
OUT	= main
FLAGS	= -g -c -Wall
LFLAGS	= -lraylib
CC	= g++

all:	main

main: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp -lcppunit

grid.o: lib/grid.cpp
	$(CC) $(FLAGS) lib/grid.cpp -lcppunit

colors.o: lib/colors.cpp
	$(CC) $(FLAGS) lib/colors.cpp -lcppunit

Position.o: lib/Position.cpp
	$(CC) $(FLAGS) lib/Position.cpp -lcppunit

blocks.o: lib/blocks.cpp
	$(CC) $(FLAGS) lib/blocks.cpp -lcppunit

Block.o: lib/Block.cpp
	$(CC) $(FLAGS) lib/Block.cpp -lcppunit

game.o: lib/game.cpp
	$(CC) $(FLAGS) lib/game.cpp -lcppunit

clean:
	rm -f $(OBJS) $(OUT)

