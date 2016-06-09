#include <stdio.h>

int square_digits(int n)
{
    const int pow5[10] = { 
        0, 1, 32, 243, 1024, 3125, 7776, 16807, 32768, 59049 
    };

    int sum = 0;
    while (n) {
        sum += pow5[n % 10];
        n /= 10;
    }
    return sum;
}

/* 6 * 9^5 */
#define ulim 354295

int main(void)
{
    int sum = 0;
    int i;
    for (i = 2; i < ulim; ++i) {
        if (i == square_digits(i))
            sum += i;
    }

    printf("%d\n", sum);
    return 0;
}
