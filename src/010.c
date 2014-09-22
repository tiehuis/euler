#include <stdio.h>
#include "func/prime.h"

#define ULIM 2000000

int main(void)
{
    int *primes = eratos_sieve(ULIM);

    long long s = 2;
    int i;
    for (i = 3; i <= ULIM; i += 2) {
        if (eratos_check(primes, i))
            s += i;
    }

    printf("%lld\n", s);
    return 0;
}
