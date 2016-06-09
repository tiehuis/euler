#include <stdio.h>
#include <math.h>

const int pow10table[] = 
{ 
    1, 10, 100, 1000, 10000, 100000, 1000000, 
    10000000, 100000000, 1000000000 
};

int base10len(int n)
{
    int len = 0;
    while (n) {
        n /= 10;
        ++len;
    }
    return len;
}

int prev_palindrome(const int n)
{
    int val = n - 1;

restart:;
    int right  = 0;
    int left   = base10len(val) - 1;
    int thresh = pow10table[left];

    while (left > right) {
        /* Store the trailing bits we have changed */
        int trailing = (val / pow10table[right]);
        int leftdig  = (val / pow10table[left]) % 10;
        int rightdig = (val / pow10table[right]) % 10;

        if (rightdig != leftdig) {
            /* Calculate the amount we need to subtract by to match digits */
            int sub = rightdig > leftdig 
                    ? (rightdig - leftdig) * pow10table[right]
                    : (10 - (leftdig - rightdig)) * pow10table[right];

            /* If the subtraction is going to enter new length range then set to upper
             * limit of this range */
                val = val - sub < thresh
                    ? thresh - 1
                    : val - sub;
        }

        /* If we are now in a lower number of digits or we altered trailing restart */
        if (val / pow10table[right] != trailing || val < thresh)
            goto restart;

        --left;
        ++right;
    }

    return val;
}

int has3digitfactor(int n)
{
    int i;
    for (i = 999; i > 99; --i) {
        if ((n / i) > 999 || n > i*i)
            return 0;
        if (!(n % i))
            return 1;
    }

    return 0;
}

int main(void)
{
    int s     = (999*999) + 1;
    int match = 0;

    while (!match) {
        s     = prev_palindrome(s);
        match = has3digitfactor(s);
    }

    printf("%d\n", s);
    return 0;
}
