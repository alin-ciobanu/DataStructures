CC=gcc
CFLAGS=-O3 -Wall

build:
	$(CC) $(CFLAGS) -o test binaryTree.c tests.c -lm

run: build
	./test

clean:
	rm test
