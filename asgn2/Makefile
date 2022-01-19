CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic

.PHONY: all

all: integrate

integrate: integrate.o functions.o mathlib.o
	$(CC) -o integrate integrate.o functions.o mathlib.o

integrate.o: integrate.c
	$(CC) $(CFLAGS) -c integrate.c -o integrate.o

functions.o: functions.c
	$(CC) $(CFLAGS) -c functions.c -o functions.o

mathlib.o:  mathlib.c
	$(CC) $(CFLAGS) -c mathlib.c -o mathlib.o

clean:
	rm -f integrate *.o

format:
	clang-format -i -style=file *.[c,h]

