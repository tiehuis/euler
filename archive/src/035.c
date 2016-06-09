#include <stdio.h>
#include <stdlib.h>
#include <ntc/prime.h>

/* Flip the corresponding bit associated with the value */
void eratos_flip(int *sieve, unsigned long n)
{
    sieve[n >> 6] ^= (1 << (n >> 1 & 31));
}

int base10_len(int n)
{
    int len = 0;
    while (n)
        ++len, n /= 10;
    return len;
}

int pow10_table[] = 
{ 
    1, 10, 100, 1000, 10000, 100000, 1000000 
};

int next_rotation(int n, int len)
{
    int lead = n % 10;
    len--;
    n /= 10;
    n += lead * pow10_table[len];
    return n;
}

int main(void)
{
    const int ulim = 1000000;
    int *sieve = eratos_sieve(ulim);
    int sum = 1; /* Add 2 initially */

    int i;
    for (i = 3; i < ulim; i += 2) {
        if (!eratos_check(sieve, i))
            continue;

        int rot = i;
        int len = base10_len(rot);

        /* Cycle through all rotations and check if all are prime */
        do {
            rot = next_rotation(rot, len);
            if (rot > ulim || !eratos_check(sieve, rot))
                break;
        } while (rot != i);

        if (rot != i)
            continue;

        /* Discard all primes from the rotations we just checked */
        do {
            rot = next_rotation(rot, len);
            eratos_flip(sieve, rot);
            ++sum;
        } while (rot != i);
    }

    printf("%d\n", sum);
    return 0;
}
