CC = clang
CFLAGS = -Wall -Wextra -Wpedantic -Werror

all: encode decode

encode: encode.o node.o pq.o stack.o code.o io.o huffman.o header.h
	$(CC) encode.o node.o pq.o code.o io.o stack.o huffman.o -o encode -lm

encode.o: encode.c node.o pq.o stack.o code.o io.o huffman.o
	$(CC) $(CFLAGS) -c encode.c

decode: decode.o node.o pq.o stack.o code.o io.o huffman.o header.h
	$(CC) encode.o node.o pq.o code.o io.o stack.o huffman.o -o decode -lm

decode.o: decode.c node.o pq.o stack.o code.o io.o huffman.o
	$(CC) $(CFLAGS) -c decode.c

io.o: io.c io.h
	$(CC) $(CFLAGS) -c io.c

node.o: node.c node.h
	$(CC) $(CFLAGS) -c node.c

pq.o: pq.c pq.h node.c node.h
	$(CC) $(CFLAGS) -c pq.c

stack.o: stack.c stack.h node.c node.h
	$(CC) $(CFLAGS) -c stack.c

code.o: code.c code.h defines.h
	$(CC) $(CFLAGS) -c code.c

huffman.o: huffman.c huffman.h node.c node.h pq.c pq.h stack.c stack.h code.c code.h io.c io.h header.h
	$(CC) $(CFLAGS) -c huffman.c

clean:
	rm -f encode *.o	
	rm -f decode *.o
	rm -f *.gch

format:
	clang-format -i -style=file *[c,h]
