#include <stdlib.h>
#include <math.h>
#include "prime.h"

inline int eratos_check(int *sieve, const unsigned int n)
{
    if ((n != 2 && ~n & 1) || (n < 2)) 
        return 0;
    else
        return !(sieve[n >> 6] & (1 << (n >> 1 & 31)));
}

int *eratos_sieve(int ulim)
{
    int i, j;
    int *sieve = calloc((ulim >> 6) + 1, sizeof(int));

    for (i = 3; i < sqrt(ulim) + 1; i += 2)
        if (!(sieve[i >> 6] & (1 << (i >> 1 & 31))))
            for (j = i*i; j < ulim; j += 2*i)
                sieve[j >> 6] |= (1 << (j >> 1 & 31));

    return sieve;
}
