#include <gmp.h>

int main(void)
{
    mpz_t a, t, _10;
    mpz_init(a);
    mpz_init_set_ui(t, 0);
    mpz_init_set_str(_10, "10000000000", 10);

    unsigned int i;
    for (i = 1; i <= 1000; ++i) {
        mpz_set_ui(a, i);
        mpz_powm(a, a, a, _10);
        mpz_add(t, t, a);
    }

    mpz_mod(t, t, _10);
    gmp_printf("%Zd\n", t);
    return 0;
}
