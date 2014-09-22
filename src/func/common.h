#ifndef _COMMON_H_
#define _COMMON_H_

#include "types.h"

#define swap(x,y)\
    do {\
        typeof(x) _ = x;\
        x = y;\
        y = _;\
    } while (0)

#define arrsiz(x) (sizeof (x) / sizeof (x[0]))

ul_t  rand_range(ul_t llim, ul_t ulim);
ull_t gcd      (ull_t u, ull_t v);
ull_t lcm      (ull_t u, ull_t v);
ull_t factorial(ui_t n);

#endif
