#include <stdio.h>
#include <math.h>

int base10_len(int n)
{
    int len = 0;
    while (n)
        ++len, n /= 10;
    return len;
}

int main(void)
{
    int product = 1;
    int step = 1;
    int i1   = 1;
    int i2   = 10;

    int i;
    int index;
    for (i = 1, index = 1; index <= 1000000; index += step, ++i) {
        if (index >= i1) {
            int copy     = i;
            int copy_len = base10_len(copy) - 1;
            int shift    = copy_len - index + i1;

            while (shift--) copy /= 10;
            product *= copy % 10;
            i1 *= 10;
        }

        if (i == i2) {
            i2 *= 10;
            ++step;
        }
    }

    printf("%d\n", product);
    return 0;
}
