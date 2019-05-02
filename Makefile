CC=g++
CFLAGS=-Wall -Werror -std=c++11

all:
	$(CC) $(CFLAGS) board.cpp -c -o board.o
	$(CC) $(CFLAGS) puzzle.cpp -c -o puzzle.o
	$(CC) $(CFLAGS) main.cpp -c -o main.o
	$(CC) $(CFLAGS) -o tp1 main.o board.o puzzle.o
	rm *.o

run:
	./tp1

clean:
	rm *.o