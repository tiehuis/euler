#include <stdio.h>

#define swap(x,y)\
    do {\
        typeof(x) _ = x;\
        x = y;\
        y = _;\
    } while (0)

int next_permutation(int *a, int len)
{
    int s = -1;
    int k;
    for (k = 0; k < len - 1; ++k) {
        if (a[k] < a[k+1])
            s = k;
    }

    /* We are done if in order. Indicate end with 0 */
    if (s == -1) return 0;

    int l = 0;
    for (k = 0; k < len; ++k) {
        if (a[s] < a[k]) 
            l = k;
    }

    /* Swap values */
    swap(a[s], a[l]);

    /* Reverse sequence from k + 1 */
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
    int s[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int slen = sizeof(s) / sizeof(s[0]);
    int perm = 1;

    do {
        next_permutation(s, slen);
    } while (++perm < 1000000);

    int i;
    for (i = 0; i < slen; ++i)
        printf("%d", s[i]);
    printf("\n");
    return 0;
}
