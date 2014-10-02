#include <stdio.h>
#include <math.h>
#include "func/prime.h"

#define ulim 10000

int main(void)
{
    int cache[ulim] = { 0 };    /* Cache divisor sums */
    int sum = 0;

    int i;
    for (i = 1; i < ulim; ++i) {
        int div  = divisor(1, i) - i;
        cache[i] = div;

        /* Since pairs are 1-1, just check the back case */
        if (div < i && cache[div] == i)
            sum += (div + i);
    }

    printf("%d\n", sum);
    return 0;
}
