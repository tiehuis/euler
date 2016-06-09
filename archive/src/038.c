#include <stdio.h>
#include <ntc/types.h>

int intlen(ull_t n)
{
    int s = 0;
    while (n) n /= 10, ++s;
    return s;
}

int pandigital(ull_t n)
{
    int c = 0;
    int last;

    while (n) {
        last = n % 10;
        if ((c & (1 << last)) != 0 || last == 0)
            return 0;
        c |= (1 << last);
        n /= 10;
    }

    return 1;
}

ull_t concat(const int front, const int back)
{
    const ull_t pow10t[] = { 
        0, 1, 10, 100, 1000, 10000, 100000, 1000000,
        10000000, 100000000, 1000000000, 10000000000
    };

    return front * pow10t[intlen(back) + 1] + back;
}

int main(void)
{
    ull_t s = 12;
    ull_t i = 9876;

    do {
        if (pandigital(i))
            s = concat(i, 2*i);
        --i;
    } while (!pandigital(s));

    printf("%llu\n", s);
    return 0;
}
