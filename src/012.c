#include <stdio.h>
#include <ntc/prime.h>

int main(void)
{
    int t = 0;
    int s = 0;
    do {
        t += ++s;
    } while (divisor(0, t) < 500);

    printf("%d\n", t);
    return 0;
}
