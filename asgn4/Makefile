CC = clang
CFLAGS = -Wpedantic -Werror -Werror -Wall

all: life

life: life.o universe.o
	$(CC) -o life life.o universe.o -lncurses

life.o: life.c universe.h
	$(CC) $(CFLAGS) -c life.c

universe.o: universe.c
	$(CC) $(CFLAGS) -c universe.c

clean:
	rm -f sorting *.o

format:
	clang-format -i -style=file *[c,h]
