#include <stdio.h>
#include <gmp.h>

int main(void)
{
    mpz_t r, q;
    mpz_init(r);
    mpz_init(q);

    size_t maxsum = 0;
    int a, b;
    for (a = 99; a > 0; --a) {
        for (b = 99; b > 0; --b) {
            mpz_ui_pow_ui(r, a, b);
            if (mpz_sizeinbase(r, 10) * 9 < maxsum)
                continue;

            size_t digsum = 0;
            while (mpz_cmp_ui(r, 0)) {
                mpz_tdiv_qr_ui(r, q, r, 10);
                digsum += mpz_get_ui(q);
            }

            if (digsum > maxsum)
                maxsum = digsum;
        }
    }

    printf("%zu\n", maxsum);
    return 0;
}
