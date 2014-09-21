#include <stdlib.h>
#include <time.h>
#include "common.h"

/* Binary gcd calculation */
long gcd(long u, long v)
{
    if (!u) return v;
    if (!v) return u;

    int shift;
    for (shift = 0; !((u | v) & 1); ++shift) {
        u >>= 1;
        v >>= 1;
    }

    while (!(u & 1))
        u >>= 1;

    do {
        while (!(v & 1)) v >>= 1;
        if (u > v) swap(u, v);
        v -= u;
    } while (v);

    return u << shift;
}

/* Lcm calculated via binary gcd */
long lcm(long u, long v)
{
    return abs(u * v) / gcd(u, v);
}

/* Calculate less-biased value between given ranges */
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
