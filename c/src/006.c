#include <stdio.h>

int main(void)
{
    long sum = 101*50 * 101*50;
    long i;
    for (i = 1; i <= 100; i++)
        sum -= i*i;

    printf("%ld\n", sum);
    return 0;
}
