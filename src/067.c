#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define max(x,y)  ((x) > (y) ? (x) : (y))

int main(void)
{
    size_t cap   = 4096;
    size_t nmemb = 0;

    /* We know the array size we need, but this is more general and will
     * work for any input of triangles */
    FILE *fd = fopen("res/067.data", "r");
    int *tri = malloc(cap * sizeof(int));
    while (fscanf(fd, "%d ", &tri[nmemb]) != EOF) {
        if (++nmemb == cap) {
            cap <<= 1;
            tri = realloc(tri, cap * sizeof(int));
        }
    }
    fclose(fd);

    const int base = (sqrt(8*nmemb + 1) - 1) / 2;
    int step       = base - 1;
    int stepc      = 0;

    int i;
    for (i = nmemb - base - 1; i >= 0; --i) {
        tri[i] += max(tri[i + step], tri[i + step + 1]);
        if (++stepc == step) {
            --step;
            stepc = 0;
        }
    }

    printf("%d\n", tri[0]);
    return 0;
}
