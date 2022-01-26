CC = clang
CFLAGS = -Wpedantic -Werror -Wextra -Wall

all: sorting

sorting: sorting.o batcher.o heap.o insert.o quick.o stats.o
	$(CC) -o sorting sorting.o batcher.o heap.o insert.o quick.o stats.o

sorting.o: sorting.c set.h
	$(CC) $(CFLAGS) -c sorting.c

batcher: batcher.o stats.o
	$(CC) -o batcher batcher.o stats.o

batcher.o: batcher.c stats.h
	$(CC) $(CFLAGS) -c batcher.c

heap: heap.o stats.o
	$(CC) -o heap heap.o stats.o

heap.o: heap.c stats.h
	$(CC) $(CFLAGS) -c heap.c

insert: insert.o stats.o
	$(CC) -o insert insert.o stats.o

insert.o: insert.c stats.h
	$(CC) $(CFALGS) -c insert.c

quick: quick.o stats.o
	$(CC) -o quick quick.o stats.o

quick.o: quick.c stats.h
	$(CC) $(CFLAGS) -c quick.c

stats.o: stats.c
	$(CC) $(CFLAGS) -c stats.c

clean:
	rm -f sorting *.o

format:
	clang-format -i -style=file *[c,h]
