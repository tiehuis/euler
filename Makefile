CC      = gcc
CFLAGS += -march=native -O2 -Wall -Wextra

all: 001 002 005

001: src/001.c
	$(CC) $(CFLAGS) -o bin/001 src/001.c

002: src/002.c
	$(CC) $(CFLAGS) -o bin/002 src/002.c

005: src/005.c src/func/common.c
	$(CC) $(CFLAGS) -o bin/005 src/005.c src/func/common.c

006: src/006.c
	$(CC) $(CFLAGS) -o bin/006 src/006.c

clean:
	@rm -f bin/*
