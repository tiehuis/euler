#include <stdio.h>

#define ulim 1088641

const int fact[10] = { 
    1, 1, 2, 6, 24, 120, 720,
    5040, 40320, 362880
};

int fact_digsum(int n)
{
    int sum = 0;
    while (n) {
        sum += fact[n % 10];
        n /= 10;
    }
    return sum;
}

int main(void)
{
    int sum = 0;
    int i;
    for (i = 3; i < ulim; ++i)
        if (fact_digsum(i) == i)
            sum += i;

    printf("%d\n", sum);
    return 0;
}
