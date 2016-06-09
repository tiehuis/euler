#include <stdio.h>

#define CACHE_THRESH 1000000

int main(void)
{
    int cache[CACHE_THRESH] = { 0 };
    int maxstart;
    int maxchain = 0;

    int i;
    for (i = 1; i < 1000000; ++i) {
        unsigned long long a = i;
        int chain = 1;

        while (a > 1) {
            if (a < CACHE_THRESH && cache[a]) {
                chain += cache[a] - 1;
                break;
            }

            a = a & 1 ? a * 3 + 1 : a >> 1;
            ++chain;
        }

        if (i < CACHE_THRESH)
            cache[i] = chain;

        if (chain > maxchain) {
            maxstart = i;
            maxchain = chain;
        }
    }

    printf("%d\n", maxstart);
    return 0;
}
