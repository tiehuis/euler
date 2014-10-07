#include <stdio.h>

#define pancheck(a)\
    do {\
        while (a) {\
            const int t = a % 10;\
            if (t == 0 || seen[t])\
                return 0;\
            seen[t] = 1;\
            a /= 10;\
        }\
    } while (0)

int pandigital(int a, int b, int c)
{
    int seen[10] = { 0 };
    pancheck(a);
    pancheck(b);
    pancheck(c);
    return 1;
}

int intable(const int *table, const int tlen, const int value)
{
    int i;
    for (i = 0; i < tlen; ++i)
        if (table[i] == value)
            return 1;
    return 0;
}

int main(void)
{
    int table[100] = { 0 };
    int tlen = 0;
    int sum  = 0;

    int i, j;
    for (i = 2; i < 1000; ++i) {
        const int start = i > 9 ? 123 : 1234;
        const int end   = 10000 / i + 1;

        for (j = start; j < end; ++j) {
            const int p = i * j;
            if (pandigital(i, j, p) && !intable(table, tlen, p)) {
                table[tlen++] = p;
                sum += p;
            }
        }
    }

    printf("%d\n", sum);
    return 0;
}
