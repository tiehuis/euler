#include <stdio.h>

#define ulim   1000
#define ellim  1093 /* Sum 3 ^ i for i in [0, treelv] */
#define treelv 6 

typedef struct {
    int a;
    int b;
    int c;
} triple;

inline int perimeter(triple t)
{
    return t.a + t.b + t.c;
}

void calc_triple(triple *dst, triple *src)
{
#define mmult(src, x, y, z) (x*src->a + y*src->b + z*src->c)

    /* Calculate first triple */
    dst->a = mmult(src, 1,-2, 2);
    dst->b = mmult(src, 2,-1, 2);
    dst->c = mmult(src, 2,-2, 3);
    ++dst;
    
    /* Calculate second triple */
    dst->a = mmult(src, 1, 2, 2);
    dst->b = mmult(src, 2, 1, 2);
    dst->c = mmult(src, 2, 2, 3);
    ++dst;

    /* Calculate third triple */
    dst->a = mmult(src,-1, 2, 2);
    dst->b = mmult(src,-2, 1, 2);
    dst->c = mmult(src,-2, 2, 3);

#undef mmult
}

int main(void)
{
    /* Store all primitive triples perimeter < 1000. Worst case 6 levels
     * so sum 3 ^ i for i -> 0 to 6 */
    triple t[ellim];

    /* Initial generating primitive triple */
    t[0].a = 3;
    t[0].b = 4;
    t[0].c = 5;

    int number = 1; /* Number of parents in this row */
    int index  = 0; /* Offset for our parent */
    int offset = 1; /* Offset to place children */
    int i, j;
    for (i = 0; i < treelv; ++i) {
        for (j = 0; j < number; ++j) {
            calc_triple(t + offset, t + index); 
            offset += 3;
            ++index;
        }
        number *= 3;
    }

    /* Use our primitives and check through all non-primitives */
    int sums[ulim] = { 0 };
    for (i = 0; i < ellim; ++i) {
        int p;
        int k = 1;
        while ((p = k * perimeter(t[i])) <= ulim) {
            ++sums[p];
            ++k;
        }
    }

    int maxsum = 0;
    int maxind = 0;
    for (i = 0; i < ulim; ++i) {
        if (sums[i] > maxsum) {
            maxsum = sums[i];
            maxind = i;
        }
    }

    printf("%d\n", maxind);
    return 0;
}
