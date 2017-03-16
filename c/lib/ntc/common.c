#include <stdlib.h>
#include <time.h>
#include "common.h"

#define swap(x,y)\
    do {\
        typeof(x) _ = x;\
        x = y;\
        y = _;\
    } while (0)

/* Factorial function */
ull_t factorial(ui_t n)
{
    ull_t acc = 1;
    while (n) acc *= n--;
    return acc;
}

/* Binary gcd calculation */
ull_t gcd(ull_t u, ull_t v)
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
ull_t lcm(ull_t u, ull_t v)
{
    return abs(u * v) / gcd(u, v);
}

/* Calculate less-biased value between given ranges */
ul_t rand_range(ul_t llim, ul_t ulim)
{
    static int seeded = 0;
    if (!seeded) {
        seeded = 1;
        srand(time(NULL));
    }

    ul_t n = ulim - llim + 1;
    ul_t r = RAND_MAX % n;
    ul_t x;

    do {
        x = rand();
    } while (x >= RAND_MAX - r);

    return llim + x % n;
}
