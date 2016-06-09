#include <stdio.h>
#include <gmp.h>

int main(void)
{
    mpz_t a, r;
    mpz_init(a);
    mpz_init(r);

    int digsum = 0;
    mpz_fac_ui(a, 100);

    while (mpz_cmp_ui(a, 0)) {
        mpz_tdiv_qr_ui(a, r, a, 10);
        digsum += mpz_get_ui(r);
    }

    printf("%d\n", digsum);
    return 0;
}
