#include <stdio.h>
#include "func/prime.h"

int main(void)
{
    struct pfact *f = factor(600851475143LL);

    /* Iterate to last factor */
    int i = 0;
    while (f->factors[i]) ++i;
    --i;

    printf("%llu\n", f->factors[i]);
    return 0;
}
