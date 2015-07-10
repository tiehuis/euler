#ifndef _FRACTION_H_
#define _FRACTION_H_

#include "types.h"

typedef struct {
    ull_t p;
    ull_t q;
} fraction;

fraction* fract_reduce(fraction *f);

#endif
