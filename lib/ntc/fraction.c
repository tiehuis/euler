#include <stdio.h>
#include <stdlib.h>
#include "fraction.h"
#include "common.h"

#define swap(x,y)\
    do {\
        typeof(x) _ = x;\
        x = y;\
        y = _;\
    } while (0)

/* Currently no implemented correctly. Will take a function which modifies
 * based on the current i position, an expr i.e (2:(1,3,1,8)) in array form
 * it's length, and the number of cycles to iterate through */
fraction* cont_fract(ull_t (*fn)(ull_t), const int *expr,
    const size_t exprlen, const size_t iter)
{
    fraction *f = malloc(sizeof(fraction));

    /* Start from bottom and roll up. We need to know the bottom q value */
    f->p = 1;
    f->q = expr[((iter) % (exprlen - 1)) + 1];

    int c;
    size_t i;
    for (i = iter; i >= 0; i = i == 1 ? iter : i - 1) {
        c = expr[(i % (exprlen - 1)) + 1];
        if (!c) (*fn)(i);

        ull_t t = c * f->q + 1 * f->p;
        f->p = f->q * 1;
        f->q = t;
    }

    f->p += f->q;
    return f;
}

fraction* fract_reduce(fraction *f)
{
    ull_t d;
    while ((d = gcd(f->p, f->q)) != 1) {
        f->p /= d;
        f->q /= d;
    }
    return f;
}
