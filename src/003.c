#include <stdio.h>
#include "func/prime.h"

int main(void)
{
    struct pfact *f = factor(600851475143LL);
    printf("%llu\n", f->factors[f->nfacts - 1]);
    return 0;
}
