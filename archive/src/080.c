#include <stdio.h>
#include <math.h>
#include <gmp.h>

int is_perfect_sq(int n)
{
    int s = sqrt(n);
    return s * s == n;
}

int main(void)
{
    // 10^100 ~< 2^400
    mpf_set_default_prec(512);

    mpf_t a;
    mpf_init(a);
    int total_sum = 0;

    // Count through 100 irrational roots
    for (int i = 2; i <= 100; ++i) {
        if (is_perfect_sq(i)) {
            continue;
        }

        mpf_sqrt_ui(a, i);
        int digital_sum = 0;

        // Count 100 decimal digits
        for (int i = 0; i < 100; ++i) {
            long ip = mpf_get_ui(a);
            digital_sum += ip % 10;

            mpf_sub_ui(a, a, ip);
            mpf_mul_ui(a, a, 10);
        }

        total_sum += digital_sum;
    }

    printf("%d\n", total_sum);
    mpf_clear(a);
}
