CC      = gcc
CFLAGS += -march=native -O2 -Wall -Wextra

all: 001 002 005 010

001: src/001.c
	$(CC) $(CFLAGS) -o bin/001 src/001.c

002: src/002.c
	$(CC) $(CFLAGS) -o bin/002 src/002.c

005: src/005.c src/func/common.c
	$(CC) $(CFLAGS) -o bin/005 src/005.c src/func/common.c

006: src/006.c
	$(CC) $(CFLAGS) -o bin/006 src/006.c

010: src/010.c src/func/prime.c
	$(CC) $(CFLAGS) -o bin/010 src/010.c src/func/prime.c -lm

clean:
	@rm -f bin/*
