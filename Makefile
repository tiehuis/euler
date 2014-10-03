# Flags
CC      = gcc
CFLAGS += -march=native -O2 -Wall -Wextra

# All targets
all: 001_020 021_040 041_060 061_080 081_100

# Targets for problem ranges
001_020: 001 002 003 004 005 006 007 008 009 010 012 011 013 014 015 016 017 018 019 020 

021_040: 021 022 023 025 027 028 035 036 040

041_060: 042 045 047 048 053 055 056 059

061_080: 065 067
	
081_100: 097 099

# Actual source level targets
001: src/001.c
	$(CC) $(CFLAGS) -o bin/001 src/001.c

002: src/002.c
	$(CC) $(CFLAGS) -o bin/002 src/002.c

003: src/003.c
	$(CC) $(CFLAGS) -o bin/003 src/003.c src/func/prime.c -lm

004: src/004.c
	$(CC) $(CFLAGS) -o bin/004 src/004.c

005: src/005.c src/func/common.c
	$(CC) $(CFLAGS) -o bin/005 src/005.c src/func/common.c

006: src/006.c
	$(CC) $(CFLAGS) -o bin/006 src/006.c

007: src/007.c src/func/prime.c
	$(CC) $(CFLAGS) -o bin/007 src/007.c src/func/prime.c -lm

008: src/008.c
	$(CC) $(CFLAGS) -o bin/008 src/008.c

009: src/009.c
	$(CC) $(CFLAGS) -o bin/009 src/009.c

010: src/010.c src/func/prime.c
	$(CC) $(CFLAGS) -o bin/010 src/010.c src/func/prime.c -lm

011: src/011.c
	$(CC) $(CFLAGS) -o bin/011 src/011.c

012: src/012.c src/func/prime.c
	$(CC) $(CFLAGS) -o bin/012 src/012.c src/func/prime.c -lm

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

018: src/018.c
	$(CC) $(CFLAGS) -o bin/018 src/018.c -lm

019: src/019.c
	$(CC) $(CFLAGS) -o bin/019 src/019.c

020: src/020.c
	$(CC) $(CFLAGS) -o bin/020 src/020.c -lgmp

021: src/021.c src/func/prime.c
	$(CC) $(CFLAGS) -o bin/021 src/021.c src/func/prime.c -lm 

022: src/022.c
	$(CC) $(CFLAGS) -o bin/022 src/022.c

023: src/023.c src/func/prime.c
	$(CC) $(CFLAGS) -o bin/023 src/023.c src/func/prime.c -lm

025: src/025.c
	$(CC) $(CFLAGS) -o bin/025 src/025.c -lgmp

026: src/026.c src/func/prime.c
	$(CC) $(CFLAGS) -o bin/026 src/026.c src/func/prime.c -lm 

027: src/027.c src/func/prime.c
	$(CC) $(CFLAGS) -o bin/027 src/027.c src/func/prime.c -lm 

028: src/028.c
	$(CC) $(CFLAGS) -o bin/028 src/028.c

035: src/035.c
	$(CC) $(CFLAGS) -o bin/035 src/035.c -lm

036: src/036.c
	$(CC) $(CFLAGS) -o bin/036 src/036.c

040: src/040.c
	$(CC) $(CFLAGS) -o bin/040 src/040.c

042: src/042.c
	$(CC) $(CFLAGS) -o bin/042 src/042.c

045: src/045.c src/func/prime.c
	$(CC) $(CFLAGS) -o bin/045 src/045.c -lm

047: src/047.c
	$(CC) $(CFLAGS) -o bin/047 src/047.c src/func/prime.c -lm

048: src/048.c
	$(CC) $(CFLAGS) -o bin/048 src/048.c -lgmp

053: src/053.c
	$(CC) $(CFLAGS) -o bin/053 src/053.c -lgmp

055: src/055.c
	$(CC) $(CFLAGS) -o bin/055 src/055.c -lgmp

056: src/056.c
	$(CC) $(CFLAGS) -o bin/056 src/056.c -lgmp

059: src/059.c
	$(CC) $(CFLAGS) -o bin/059 src/059.c

065: src/065.c
	$(CC) $(CFLAGS) -o bin/065 src/065.c -lgmp

067: src/067.c
	$(CC) $(CFLAGS) -o bin/067 src/067.c -lm

097: src/097.c
	$(CC) $(CFLAGS) -o bin/097 src/097.c -lgmp

099: src/099.c
	$(CC) $(CFLAGS) -o bin/099 src/099.c -lm

# Misc targets
clean:
	@rm -f bin/*
