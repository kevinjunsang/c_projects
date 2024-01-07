CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic -g $(shell pkg-config --cflags gmp)
LFLAGS = $(shell pkg-config --libs gmp)

all: encrypt decrypt keygen

encrypt: encrypt.o randstate.o numtheory.o rsa.o
	$(CC) -o encrypt encrypt.o randstate.o numtheory.o rsa.o $(LFLAGS)

encrypt.o: encrypt.c randstate.h numtheory.h rsa.h
	$(CC) $(CFLAGS) -c encrypt.c

decrypt: decrypt.o randstate.o numtheory.o rsa.o
	$(CC) -o decrypt decrypt.o randstate.o numtheory.o rsa.o $(LFLAGS)

decrypt.o: decrypt.c randstate.h numtheory.h rsa.h
	$(CC) $(CFLAGS) -c decrypt.c

keygen: keygen.o randstate.o numtheory.o rsa.o
	$(CC) -o keygen keygen.o randstate.o numtheory.o rsa.o $(LFLAGS)

keygen.o: keygen.c randstate.c numtheory.c rsa.c randstate.h numtheory.h rsa.h
	$(CC) $(CFLAGS) -c keygen.c randstate.c numtheory.c rsa.c randstate.h numtheory.h rsa.h

test: test.o randstate.o numtheory.o rsa.o
	$(CC) -o test test.o randstate.o numtheory.o rsa.o $(LFLAGS)

test.o: test.c randstate.c randstate.h numtheory.c numtheory.h rsa.c rsa.h
	$(CC) $(CFLAGS) -c test.c randstate.c randstate.h numtheory.c numtheory.h rsa.c rsa.h
	
randstate.o: randstate.c
	$(CC) $(CFLAGS) -c randstate.c

numtheory.o: numtheory.c
	$(CC) $(CFLAGS) -c numtheory.c

rsa.o: rsa.c
	$(CC) $(CFLAGS) -c rsa.c

clean:
	rm -f encrypt *.o
	rm -f decrypt *.o
	rm -f keygen *.o
	rm -f *.gch

format:
	clang-format -i -style=file *[c,h]




