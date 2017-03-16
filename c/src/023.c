#include <stdio.h>
#include <ntc/prime.h>

#define ulim 20161

int main(void)
{
    int abcnt = 0;
    int abundant[ulim] = { 0 };
    int absum[ulim]    = { 0 };

    /* Calc abundant numbers first */
    int i, j;
    for (i = 1; i <= ulim; ++i) {
        if (divisor(1, i) - i > (size_t)i)
            abundant[abcnt++] = i;
    }

    int sum = 0;
    for (i = 0; i < abcnt; ++i) {
        for (j = 0; j < abcnt; ++j) {
            int cand = abundant[i] + abundant[j];
            if (cand > ulim)
                break;
            if (!absum[cand]) {
                absum[cand] = 1;
                sum += cand;
            }
        }
    }

    sum = (ulim * (ulim + 1) / 2) - sum;
    printf("%d\n", sum);
    return 0;
}
