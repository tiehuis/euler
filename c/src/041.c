#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ntc/prime.h>

#define swap(x,y)\
    do {\
        typeof(x) _ = x;\
        x = y;\
        y = _;\
    } while (0)

int prev_permutation(char *a, const size_t len)
{
    int s = -1;
    size_t k;
    for (k = 0; k < len - 1; ++k) {
        if (a[k] > a[k+1])
            s = k;
    }

    /* We are done if in order. Indicate end with 0 */
    if (s == -1) return 0;

    size_t l = 0;
    for (k = 0; k < len; ++k) {
        if (a[s] > a[k]) 
            l = k;
    }

    /* Swap values */
    swap(a[s], a[l]);

    /* Reverse sequence from s + 1 */
    l = len - 1;
    k = s + 1;
    while (k < l) {
        swap(a[k], a[l]);
        ++k;
        --l;
    }

    return 1;
}

int main(void)
{
    /* Must be 7 digits */
    char s[] = "7654321";
    const size_t slen = strlen(s);

    do {
        if (s[slen - 1] == '3' || s[slen - 1] == '7')
            if (mr_prime_test(atoi(s)))
                break;
    } while (prev_permutation(s, slen));

    printf("%s\n", s);
    return 0;
}
