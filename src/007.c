#include <stdio.h>
#include <math.h>
#include "func/prime.h"

#define N 10001

int main(void)
{
    /* Pn <= n*logn + n*log(logn) */
    const int ulim = N*log(N) + N*log(log(N)) + 1;
    int *sieve  = eratos_sieve(ulim);
    
    int p = 1;
    int i = 3;
    while (p < N) {
        if (eratos_check(sieve, i))
            ++p;
        i += 2;
    }

    printf("%d\n", i - 2);
    return 0;
}
