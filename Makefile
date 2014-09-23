CC      = gcc
CFLAGS += -march=native -O2 -Wall -Wextra

all: 001 002 005 006 007 008 010 015 016 019 020 025

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

008: src/008.c
	$(CC) $(CFLAGS) -o bin/008 src/008.c

010: src/010.c src/func/prime.c
	$(CC) $(CFLAGS) -o bin/010 src/010.c src/func/prime.c -lm

015: src/015.c
	$(CC) $(CFLAGS) -o bin/015 src/015.c -lgmp

016: src/016.c
	$(CC) $(CFLAGS) -o bin/016 src/016.c -lgmp

019: src/019.c
	$(CC) $(CFLAGS) -o bin/019 src/019.c

020: src/020.c
	$(CC) $(CFLAGS) -o bin/020 src/020.c -lgmp

025: src/025.c
	$(CC) $(CFLAGS) -o bin/025 src/025.c -lgmp

clean:
	@rm -f bin/*
