#include <stdio.h>
#include <gmp.h>

int main(void)
{
    mpz_t b;
    mpz_init(b);

    int n, r;
    int tc = 0;
    for (n = 23; n <= 100; ++n) {
        r = n >> 1;
        if (~n & 1) {
            ++tc; 
            --r;
        }

        int c = 0;
        mpz_bin_uiui(b, n, r);
        while (mpz_cmp_ui(b, 1000000) >= 0) {
           ++c;
           --r;
           mpz_bin_uiui(b, n, r);
        }

        tc += (c << 1);
    }

    printf("%d\n", tc);
    return 0;
}
