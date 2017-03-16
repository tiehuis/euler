#include <stdio.h>

int main(void)
{
    int i    = 1;
    int s    = 1;
    int step = 2;

    while (i < 1001*1001) {
        i += step;
        s += i;
        i += step;
        s += i;
        i += step;
        s += i;
        i += step;
        s += i;
        step += 2;
    }

    printf("%d\n", s);
    return 0;
}
