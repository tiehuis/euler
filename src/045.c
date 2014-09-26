#include <stdio.h>
#include <math.h>
#include "func/types.h"

inline int is_pent(const ull_t n)
{
    double f = (sqrt(24 * n + 1) + 1) / 6;
    return rint(f) == f;
}

int main(void)
{
    /* Every hexagonal is triangular */
    ull_t h;
    int i = 143;
    do {
        ++i;
        h = i * ((i << 1) - 1); 
    } while (!is_pent(h));

    printf("%llu\n", h);
    return 0;
}
