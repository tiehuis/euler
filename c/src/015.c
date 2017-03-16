#include <stdio.h>
#include <gmp.h>

int main(void)
{
    mpz_t a, b;
    mpz_init(a);
    mpz_init(b);

    /* 40C20 */
    mpz_fac_ui(a, 40);
    mpz_fac_ui(b, 20);
    mpz_mul(b, b, b);
    mpz_divexact(a, a, b);

    gmp_printf("%Zd\n", a);
    return 0;
}
