#include <stdio.h>

int main(void)
{
    int f1 = 1;
    int f2 = 2;
    int fs = 0;

    while (f1 < 4000000) {
        if (~f1 & 1) fs += f1;
        f2 += f1;
        f1 = f2 - f1;
    }

    printf("%d\n", fs);
    return 0;
}
