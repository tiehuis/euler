#ifndef _PRIME_H_
#define _PRIME_H_

#include "types.h"

/* Factorization */
#define MAX_NFACTS (26 + 1)
struct pfact {
    ull_t factors[MAX_NFACTS];
    ull_t powers[MAX_NFACTS];
    size_t nfacts;
};

#define factor(v) __factor(NULL, v)

void          factor_print  (struct pfact *f);
struct pfact* __factor	    (struct pfact *f, ull_t val);

/* Primes */
#define NUM_PRIMES 168

int           eratos_check  (si_t *sieve, const ull_t n);
si_t*         eratos_sieve  (const ull_t ulim);
ull_t         modular_exp   (ull_t base, ull_t exp, ull_t mod);
int           mr_prime_test (const ull_t val);

/* Misc functions */
ull_t         totient       (ull_t val);
ull_t         divisor       (const int sigma, const ull_t n);

#endif
