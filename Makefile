CC      = gcc
CFLAGS += -march=native -O2 -Wall -Wextra

all: 001 002 005 006 007 009 010 015 019

001: src/001.c
	$(CC) $(CFLAGS) -o bin/001 src/001.c

002: src/002.c
	$(CC) $(CFLAGS) -o bin/002 src/002.c

005: src/005.c src/func/common.c
	$(CC) $(CFLAGS) -o bin/005 src/005.c src/func/common.c

006: src/006.c
	$(CC) $(CFLAGS) -o bin/006 src/006.c

007: src/007.c src/func/prime.c
	$(CC) $(CFLAGS) -o bin/007 src/007.c src/func/prime.c -lm

009: src/009.c src/func/common.c
	$(CC) $(CFLAGS) -o bin/009 src/009.c src/func/common.c

010: src/010.c src/func/prime.c
	$(CC) $(CFLAGS) -o bin/010 src/010.c src/func/prime.c -lm

015: src/015.c
	$(CC) $(CFLAGS) -o bin/015 src/015.c -lgmp

019: src/019.c
	$(CC) $(CFLAGS) -o bin/019 src/019.c

clean:
	@rm -f bin/*
