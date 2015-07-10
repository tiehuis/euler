#include <stdio.h>
#include <ntc/common.h>

int main(void)
{
    const long val[] = { 20, 19, 18, 17, 16, 15, 14, 13, 12, 11 };
    const long size = sizeof(val) / sizeof(val[0]);

    long i = 1;
    long k = val[0];
    long d = val[0];

    for (i = 1; i < size; ++i) {
        while (k % val[i])
            k += d;
        d = lcm(d, val[i]);
    }

    printf("%ld\n", k);
    return 0;
}
