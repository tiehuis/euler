#include <stdio.h>
#include "func/prime.h"

extern const int prime_table[NUM_PRIMES];

int main(void)
{
    int maxseq  = 0;
    int maxprod = 0;

    int a, b;
    for (a = -999; a < 1000; ++a) {
        for (b = 0; b < NUM_PRIMES; ++b) {
            int seq = 1;
            int n   = 0;

            /* We know that the first value will be prime */
            do {
                ++seq;
                ++n;
            } while (mr_prime_test(n * n + a * n + prime_table[b]));

            if (seq > maxseq) {
                maxseq  = seq;
                maxprod = a * prime_table[b];
            }
        }
    }

    printf("%d\n", maxprod);
    return 0;
}
