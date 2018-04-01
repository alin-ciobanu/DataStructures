CC=gcc
CFLAGS=-O3 -Wall

build:
	$(CC) $(CFLAGS) -o addNumbers ./../utils/utils.c ./../linkedList/linkedList.c addNumbersLinkedList.c -lm

run: build
	./addNumbers

clean:
	rm addNumbers
