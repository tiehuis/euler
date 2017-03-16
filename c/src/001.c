#include <stdio.h>

int main(void)
{
    int i;
    int sum = 0;

    for (i = 3;  i < 1000; i += 3)  sum += i;
    for (i = 5;  i < 1000; i += 5)  sum += i;
    for (i = 15; i < 1000; i += 15) sum -= i;

    printf("%d\n", sum);
    return 0;
}
