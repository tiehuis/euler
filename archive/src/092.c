#include <stdio.h>

/* 7 * 9^2 */
#define csize 567
#define ulim  10000000

inline int square_digits(int n)
{
    const int pow2[] = {
        0, 1, 4, 9, 16, 25, 36, 49, 64, 81, 100
    };

    int sum = 0;
    while (n) {
        sum += pow2[n % 10];
        n /= 10;
    }
    return sum;
}

int main(void)
{
    /* Compute cache endings first */
    int cache[csize] = { 0 };
    int i;
    for (i = 1; i < csize; ++i) {
        int t = i;
        while (t != 89 && t != 1)
            t = square_digits(t);

        if (t == 89)
            cache[i] = 1;
    }

    int sum = 0;
    for (i = 1; i < ulim; ++i) {
        int t = square_digits(i);
        if (cache[t])
            ++sum;
    }

    printf("%d\n", sum);
    return 0;
}
