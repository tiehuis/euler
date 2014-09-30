#include <stdio.h>
#include <math.h>
#include "func/prime.h"

#define ulim 10000

/* Divisor function sigma(1) */
int divisor_function(int *sieve, const int v)
{
    if (eratos_check(sieve, v))
        return 1;

    int total = 1;
    int n     = v;
    int i     = 2;
    while (n != 1 && i < ulim / 2 + 1) {
        if (!eratos_check(sieve, i))
            goto nextiteration;

        int d = 1;
        int p = 0;
        while (n % i == 0) {
            n /= i;
            d += pow(i, ++p);
        }
        
        if (p)
            total *= d;

nextiteration:;
        if (i & 1)
            i += 2;
        else
            ++i;
    }

    return total - v;
}

int main(void)
{
    int *sieve = eratos_sieve(ulim);
    int cache[ulim] = { 0 };    /* Cache divisor sums */
    
    int sum = 0;
    int i;
    for (i = 1; i < ulim; ++i) {
        int div  = divisor_function(sieve, i);
        cache[i] = div;

        /* Since pairs are 1-1, just check the back case */
        if (div < i && cache[div] == i)
            sum += (div + i);
    }

    printf("%d\n", sum);
    return 0;
}
