#include <stdio.h>

int main(void)
{
    /* Solve 2ab - 2000(a - b) + 1000000 = 0 */
    /* The substitute new b value back for c */
    int a, b, c;
    for (a = 1; a < 500; ++a) {
        b = 1000 * (a - 500) / (a - 1000);
        c = (-(a * a) + 1000 * a - 500000) / (a - 1000);
        if (a + b + c == 1000)
            break;
    }

    printf("%d\n", a*b*c);
    return 0;
}
