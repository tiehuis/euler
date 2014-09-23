#include <stdio.h>
#include <math.h>

int main(void)
{
    FILE *fd = fopen("res/099.data", "r");
    
    int max  = 0;
    int maxl = 0;
    int line = 1;
    int base, exp;

    while (fscanf(fd, "%d,%d", &base, &exp) != EOF) {
        int cand = exp * log2(base);
        if (cand > max) {
            max  = cand;
            maxl = line;
        }
        ++line;
    }

    printf("%u\n", maxl);
    return 0;
}
