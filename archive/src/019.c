#include <stdio.h>

int main(void)
{
    int year;
    int month;
    int day = 1;
    int s   = 1;

    for (year = 1901; year < 2001; ++year) {
        for (month = 15; month > 3; --month) {
            int Y = month > 12 ? year - 1 : year;
            if (((day + ((month + 1) * 13)/5 + Y
                + Y/4 + 6*(Y/100) + Y/400) % 7) == 1)
                ++s;
        }
    }

    printf("%d\n", s);
    return 0;
}
