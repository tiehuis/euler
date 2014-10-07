#include <stdio.h>

#define CYCLE 6

int same_digits(int x, int y)
{
    int digits[10] = { 0 };

    while (x) {
        digits[x % 10]++;
        x /= 10;
    }

    while (y) {
        if (!digits[y % 10]--)
            return 0;
        y /= 10;
    }

    return 1;
}

int ilen(int n)
{
    int s = 0;
    while (n) n /= 10, ++s;
    return s;
}

int main(void)
{
    const int pow10t[] = {
        1, 10, 100, 1000, 10000, 100000,
        1000000, 10000000, 100000000
    };

    int n   = 125874;
    int x   = 0;
    while (x < CYCLE) {
        int len = ilen(n);
        if (n / (len >= 3 ? pow10t[len - 3] : 1) > 1000 / CYCLE)
            n = pow10t[len + 1];
        else 
            ++n;

        int k;
        x = 0;
        do {
            k = ++x * n;   
        } while (same_digits(n, k));
    }

    printf("%d\n", n);
    return 0;
}
