#include <stdlib.h>

long rand_range(long llim, long ulim)
{
    static int seeded = 0;
    if (!seeded) {
        seeded = 1;
        srand(time(NULL));
    }

    long n = ulim - llim + 1;
    long r = RAND_MAX % n;
    long x;

    do {
        x = rand();
    } while (x >= RAND_MAX - r);

    return llim + x % n;
}
