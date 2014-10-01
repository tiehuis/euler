#ifndef _PRIME_H_
#define _PRIME_H_

#include "types.h"

#define swap(x,y)\
    do {\
        typeof(x) _ = x;\
        x = y;\
        y = _;\
    } while (0)

/* Factorization */
#define MAX_NFACTS (26 + 1)
struct pfact {
    ull_t factors[MAX_NFACTS];
    ull_t powers[MAX_NFACTS];
};

void          factor_print  (struct pfact *f);
struct pfact* factor        (ull_t val);

/* Primes */
#define NUM_PRIMES 168

int           eratos_check  (si_t *sieve, const ull_t n);
si_t*         eratos_sieve  (const ull_t ulim);
ull_t         modular_exp   (ull_t base, ull_t exp, ull_t mod);
int           mr_prime_test (const ull_t val);
ull_t         totient       (ull_t val);
struct pfact* factor	    (ull_t val);

#endif
