#include <stdio.h>

#define total 200

int main(void)
{
    const int coins[] = { 1, 2, 5, 10, 20, 50, 100, 200 };
    const int clen = sizeof(coins) / sizeof(coins[0]);

    int orderings[total + 1] = { 0 };
    orderings[0] = 1;

    int i, j;
    for (i = 0; i < clen; ++i)
        for (j = coins[i]; j <= total; ++j)
            orderings[j] += orderings[j - coins[i]];

    printf("%d\n", orderings[total]);
    return 0;
}
