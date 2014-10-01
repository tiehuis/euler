#include <stdio.h>
#include "func/prime.h"

#define NDISTINCT 4

int main(void)
{
    struct pfact p;
    int chain = 0;
    ull_t i   = 644;

    for (;;) {
        __factor(&p, i + (NDISTINCT - chain));
        if (p.nfacts != NDISTINCT) {
            i += (NDISTINCT - chain);
            chain = 0;
        }
        else {
            if (++chain == NDISTINCT)
                break;
        }
    }

    printf("%llu\n", i + 1);
    return 0;
}
