#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Flip the corresponding bit associated with the value */
void eratos_flip(int *sieve, unsigned long n)
{
    sieve[n >> 6] ^= (1 << (n >> 1 & 31));
}

int eratos_check(int *sieve, const unsigned long n)
{
    if ((n != 2 && ~n & 1) || (n < 2)) 
        return 0;
    else
        return !(sieve[n >> 6] & (1 << (n >> 1 & 31)));
}

int *eratos_sieve(const unsigned long ulim)
{
    unsigned long i, j;
    int *sieve = calloc((ulim >> 6) + 1, sizeof(int));

    for (i = 3; i < sqrt(ulim) + 1; i += 2)
        if (!(sieve[i >> 6] & (1 << (i >> 1 & 31))))
            for (j = i*i; j < ulim; j += (i << 1))
                sieve[j >> 6] |= (1 << (j >> 1 & 31));

    return sieve;
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
