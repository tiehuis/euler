#include <stdio.h>

/* All triangular numbers below max score attainable */
#define T_LEN     27
#define MAX_WORD (15 + 1)

int triangle[T_LEN] = {
    1, 3, 6, 10, 15, 21, 28, 36,
    45, 55, 66, 78, 91, 105, 120,
    136, 153, 171, 190, 210, 231,
    253, 276, 300, 325, 351, 378
};

int is_triangle(const int n)
{
    int i;
    for (i = 0; i < T_LEN; ++i)
        if (n == triangle[i])
            return 1;

    return 0;
}

int main(void)
{
    FILE *fd = fopen("../res/042.data", "r");
    char word[MAX_WORD];
    int tri_num = 0;

    while (fscanf(fd, "%s", word) != EOF) {
        int wval = 0;
        char *s = word;

        while (*s)
            wval += *s++ - 64;

        if (is_triangle(wval))
            ++tri_num;
    }

    printf("%d\n", tri_num);
    return 0;
}
