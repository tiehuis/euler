#include <stdio.h>
#include "func/prime.h"

/* table of primes < 1000 */
extern int prime_table[NUM_PRIMES];

int main(void)
{
    /* Iterate down our primes searching for the first prime with a primitive
     * root modulo 10 */
    int i;
    for (i = NUM_PRIMES - 1; i >= 0; --i) {
        int s = prime_table[i] - 1;
        struct pfact *p = factor(s);

        /* Cycle through factors checking residuals */
        int j   = 0;
        while (p->factors[j]) {
            if (modular_exp(10, (s / p->factors[j]), prime_table[i]) == 1)
                break;
            ++j;
        }
        
        if (!p->factors[j])
            break;
    }

    printf("%d\n", prime_table[i]);
    return 0;
}
