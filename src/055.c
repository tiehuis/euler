#include <stdio.h>
#include <string.h>
#include <gmp.h>

void mpz_rotate_sum(mpz_t rop)
{
    char str[500];
    mpz_get_str(str, 10, rop);
    size_t l = strlen(str) - 1;

    size_t i;
    for (i = 0; i < l / 2 + 1; ++i) {
        char t   = str[l-i];
        str[l-i] = str[i];
        str[i]   = t;
    }

    mpz_t s;
    mpz_init(s);
    mpz_set_str(s, str, 10);
    mpz_add(rop, rop, s);
    mpz_clear(s);
}

int mpz_palindrome(mpz_t rop)
{
    char str[500];
    mpz_get_str(str, 10, rop);
    size_t l = strlen(str) - 1;

    size_t i;
    for (i = 0; i < l / 2 + 1; ++i) {
        if (str[i] != str[l-i])
            return 0;
    }

    return 1;
}

int main(void)
{
    mpz_t a;
    mpz_init(a);

    int lychrel_sum = 0;
    unsigned int i;
    for (i = 1; i < 10000; ++i) {
        mpz_set_ui(a, i);

        int j;
        for (j = 0; j < 50; ++j) {
            mpz_rotate_sum(a);
            if (mpz_palindrome(a))
                break;
        }

        if (j == 50)
            ++lychrel_sum;
    }

    printf("%d\n", lychrel_sum);
    return 0;
}
