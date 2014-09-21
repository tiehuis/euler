#include <stdlib.h>
#include <math.h>

#define eratos_check(sieve, n) (!(sieve[(n) >> 6] & (1 << (((n) >> 1) & 31))))

int *eratos_sieve(int ulim)
{
    int i, j;
    int *sieve = calloc(((n >> 5) + 1), sizeof(int));

    for (i = 3; i < sqrt(ulim) + 1; i += 2)
        if (!(sieve[i >> 6] & (1 << ((i >> 1) & 31))))
            for (j = i*i; j < ulim; j += (i << 1))
                sieve[j >> 6] |= (1 << ((j >> 1) & 31));

    return sieve;
}
