#include <stdio.h>
#include <gmp.h>

#define CYCLE 100

inline int econv(int n)
{
    return n % 3 ? 1 : n - (int)(n / 3);
}

int main(void)
{
    mpz_t p, q, t;
    mpz_init(t);
    mpz_init_set_ui(p, 1);
    mpz_init_set_ui(q, econv(CYCLE));

    /* Work from inside and roll up */
    int i;
    for (i = CYCLE - 1; i > 1; --i) {
        mpz_set(t, p);
        mpz_addmul_ui(t, q, econv(i));
        mpz_set(p, q);
        mpz_set(q, t);
    }
    mpz_addmul_ui(p, q, 2);

    /* Sum digits */
    unsigned long sum = 0;
    while (mpz_cmp_ui(p, 0))
        sum += mpz_tdiv_q_ui(p, p, 10);

    printf("%lu\n", sum);
    return 0;
}
