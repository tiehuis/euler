#include <stdio.h>
#include <gmp.h>

int main(void)
{
    mpz_t f1, f2;
    mpz_init(f1);
    mpz_init(f2);

    mpz_set_ui(f1, 1);
    mpz_set_ui(f2, 1);

    int fibc = 3;
    while (mpz_sizeinbase(f2, 10) < 1000) {
        mpz_add(f2, f2, f1);
        mpz_sub(f1, f2, f1);
        ++fibc;
    }

    printf("%d\n", fibc);
    return 0;
}
