#include <gmp.h>

int main(void)
{
    mpz_t a, _10;
    mpz_init_set_ui(a, 2);
    mpz_init_set_str(_10, "10000000000", 10);

    /* 28433 * 2^7830457 + 1 */
    mpz_powm_ui (a, a, 7830457L, _10);
    mpz_mul_ui  (a, a, 28433L);
    mpz_add_ui  (a, a, 1);
    mpz_mod     (a, a, _10);

    gmp_printf("%Zd\n", a);
    return 0;
}
