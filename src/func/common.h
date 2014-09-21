#ifndef _COMMON_H_
#define _COMMON_H_

#define swap(x,y)\
    do {\
        typeof(x) _ = x;\
        x = y;\
        y = _;\
    } while (0)

#define arrsiz(x) (sizeof (x) / sizeof (x[0]))

long rand_range(long llim, long ulim);
long gcd       (long u, long v);
long lcm       (long u, long v);

#endif
