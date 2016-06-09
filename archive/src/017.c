#include <stdio.h>

/* one, two, ... */
#define _1to9   (3 + 3 + 5 + 4 + 4 + 3 + 5 + 5 + 4)
/* ten, eleven, ... */
#define _10to20 (3 + 6 + 6 + 8 + 8 + 7 + 7 + 9 + 8 + 8)
/* twenty, thirty, ... */
#define _10s    (6 + 6 + 5 + 5 + 5 + 7 + 6 + 6)
/* hundred */
#define _hundred 7
/* and */
#define _and     3

int main(void)
{
    int total_sum = 0;

    /* Get sum for < 100 */
    total_sum +=  9 * _1to9;
    total_sum +=      _10to20;
    total_sum += 10 * _10s;

    /* Sum up values for trailing from 1 to 1000 */
    total_sum *= 10;

    /* Add leading number for hundreds */
    total_sum += 100 * _1to9;

    /* Add 'hundreds' and 'ands' */
    total_sum += 900 * _hundred;
    total_sum += 891 * _and;

    /* Add 'one thousand' */
    total_sum += 11;

    printf("%d\n", total_sum);
    return 0;
}
