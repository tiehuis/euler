#include <stdio.h>
#include <string.h>
#include <gmp.h>

#define ITERATIONS 1000

/* mpz_sizeinbase may have off by one errors */
size_t mpz_length(mpz_t a)
{
    /* Won't exceed ITERATIONS digits */
    static char str[ITERATIONS];
    return strlen(mpz_get_str(str, 10, a));
}

int main(void)
{
    mpz_t p, q, t;
    mpz_init(t);
    mpz_init_set_ui(p, 1);
    mpz_init_set_ui(q, 2);

    /* Work from inside and roll up */
    int sum = 0;
    int i;
    for (i = 1; i < ITERATIONS; ++i) {
        mpz_add(p, p, q);
        if (mpz_length(p) > mpz_length(q))
            ++sum;

        mpz_sub(p, p, q);
        mpz_set(t, p);
        mpz_addmul_ui(t, q, 2);
        mpz_set(p, q);
        mpz_set(q, t);
    }

    printf("%d\n", sum);
    return 0;
}
