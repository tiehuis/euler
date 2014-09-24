# Flags
CC      = gcc
CFLAGS += -march=native -O2 -Wall -Wextra

# All targets
all: 001_020 021_040 041_060 061_080 081_100

# Targets for problem ranges
001_020: 001 002 005 006 007 008 010 011 013 014 015 016 017 019 020 

021_040: 025 028 

041_060: 048 056 

061_080:
	
081_100: 099

# Actual source level targets
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

011: src/011.c
	$(CC) $(CFLAGS) -o bin/011 src/011.c

013: src/013.c
	$(CC) $(CFLAGS) -o bin/013 src/013.c -lgmp

014: src/014.c
	$(CC) $(CFLAGS) -o bin/014 src/014.c

015: src/015.c
	$(CC) $(CFLAGS) -o bin/015 src/015.c -lgmp

016: src/016.c
	$(CC) $(CFLAGS) -o bin/016 src/016.c -lgmp

017: src/017.c
	$(CC) $(CFLAGS) -o bin/017 src/017.c

019: src/019.c
	$(CC) $(CFLAGS) -o bin/019 src/019.c

020: src/020.c
	$(CC) $(CFLAGS) -o bin/020 src/020.c -lgmp

025: src/025.c
	$(CC) $(CFLAGS) -o bin/025 src/025.c -lgmp

028: src/028.c
	$(CC) $(CFLAGS) -o bin/028 src/028.c

048: src/048.c
	$(CC) $(CFLAGS) -o bin/048 src/048.c -lgmp

056: src/056.c
	$(CC) $(CFLAGS) -o bin/056 src/056.c -lgmp

099: src/099.c
	$(CC) $(CFLAGS) -o bin/099 src/099.c -lm

# Misc targets
clean:
	@rm -f bin/*
