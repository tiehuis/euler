#include <stdio.h>
#include "func/common.h"

int removable(const int p, const int q)
{
    const int p1 = p % 10;
    const int q1 = q % 10;

    if (p1 != 0 && q1 != 0) {
        const int p2 = p / 10;
        const int q2 = q / 10;

        if (p1 == q1 && p*q2 == p2*q)
            return 1;
        if (p2 == q1 && p*q2 == p1*q)
            return 1;
        if (p1 == q2 && p*q1 == p2*q)
            return 1;
    }

    return 0;
}

int main(void)
{
    int p, q;
    int rp = 1;
    int rq = 1;

    for (p = 10; p < 100; ++p) {
        for (q = p + 1; q < 100; ++q) {
            if (removable(p, q)) {
                rp *= p;
                rq *= q;
            }
        }
    }

    printf("%llu\n", rq / gcd(rp, rq));
    return 0;
}
