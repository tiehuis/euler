#include <stdio.h>
#include <math.h>

const int pow10_table[] = 
{ 
    1, 10, 100, 1000, 10000, 100000, 1000000, 
    10000000, 100000000, 1000000000 
};

int base10_len(int n)
{
    int len = 0;
    while (n) {
        n /= 10;
        ++len;
    }
    return len;
}

int base2_len(int n)
{
    int len = 0;
    while (n) {
        n >>= 1;
        ++len;
    }
    return len;
}

int next_base10_palin(const int n)
{
    int val = n + 1;

restart:;
    int right  = 0;
    int left   = base10_len(val) - 1;
    int thresh = pow10_table[left + 1];

    while (left > right) {
        int trailing = (val / pow10_table[right]);
        int leftdig  = (val / pow10_table[left]) % 10;
        int rightdig = (val / pow10_table[right]) % 10;

        if (rightdig != leftdig) {
            int add = rightdig > leftdig 
                    ? (10 - (rightdig - leftdig)) * pow10_table[right]
                    : (leftdig - rightdig) * pow10_table[right];

                val = val + add > thresh
                    ? thresh + 1
                    : val + add;
        }

        if (val / pow10_table[right] != trailing || val > thresh)
            goto restart;

        --left;
        ++right;
    }

    return val;
}

int chk_base2_palin(const int n)
{
    int right = 0;
    int left  = base2_len(n) - 1;

    while (left > right) {
        if (((n >> left) & 1) != ((n >> right) & 1))
            return 0;

        --left;
        ++right;
    }

    return 1;
}

int main(void)
{
    int s   = 0;
    int sum = 0;

    while (s < 1000000) {
        s = next_base10_palin(s);
        if (chk_base2_palin(s))
            sum += s;
    }

    printf("%d\n", sum);
    return 0;
}
