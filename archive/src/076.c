#include <stdio.h>
#include <ntc/types.h> /* ull_t = unsigned long long */

#define memthresh 1000

/* Compute the sign required for the reccurence relation based on
 * our current index */
inline int psign(int n)
{
    if (n < 0) n *= -1;
    return ((n - 1) & 1) ? -1 : 1;
}

/* Pentagonal number generator */
inline int pentagonal(const int n)
{
    return (3*n*n - n) >> 1;
}

/* Calculate next generalized pentagonal index */
inline int next(const int n)
{
    return (n * -1) + (n <= 0 ? 1 : 0);
}

/* Eulers recurrence relation for partitions */
ull_t partition(const int n)
{
    static int memoize[memthresh] = { 0 };

    /* Build up partitions from 1 */
    if (n < memthresh && memoize[n])
        return memoize[n];

    /* P(0) && P(1) = 1 */
    if (n <= 1) {
        return 1;
    }
    else {
        int s  = 0;
        int pi = 1;
        int t  = pentagonal(pi);

        /* Compute the next partition and if it isn't saved, store it */
        while (t <= n) {
            int part = partition(n - t);
            if (n - t < memthresh) 
                memoize[n - t] = part;

            /* Adjust the sign then get the next pentagonal number */
            s  += psign(pi) * part;
            pi  = next(pi);
            t   = pentagonal(pi);
        }

        return s;
    }
}

int main(void)
{
    /* Subtract the 100 that is not counted */
    printf("%llu\n", partition(100) - 1);
    return 0;
}