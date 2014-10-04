#include <stdio.h>
#include "func/prime.h"

const int pow10_table[] = {
    1, 10, 100, 1000, 10000, 100000, 1000000,
    10000000, 100000000, 1000000000
};

int truncatable(const int n)
{
    /* Right truncatable */
    int left  = n;
    int right = n;
    int mod   = 10;

    while (left / 10) {
        right = n % mod;
        left /= 10;
        mod  *= 10;

        if (!mr_prime_test(right) || !mr_prime_test(left))
            return 0;
    }

    return 1;
}

int base10_len(int n)
{
    int len = 0;
    while (n)
        ++len, n /= 10;
    return len;
}

int main(void)
{
    int count = 0;
    int sum   = 0;

    int i = 13;
    while (count < 11) {
        /* Check if value matches conditions */
        if (mr_prime_test(i) && truncatable(i)) {
            sum += i;
            ++count;
        }

        /* Cycle if our leading term cannot be truncatable */
        int len  = base10_len(i) - 1;
        int head = i / pow10_table[len];
        switch (head) {
            case 8:
                i += pow10_table[len];
            case 1:
            case 4:
            case 6:
            case 9:
                i += pow10_table[len];
                break;
            default:
                i += i % 10 == 3 ? 4 : 6;
                break;
        }
    }

    printf("%d\n", sum);
    return 0;
}
