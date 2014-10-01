#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include "prime.h"

const ui_t prime_table[NUM_PRIMES] =
{
    2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71,
    73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 
    157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233,
    239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317,
    331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419,
    421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503,
    509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607,
    613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701,
    709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797, 809, 811,
    821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911,
    919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997
};

/* Pass in a sieve calculated from eratos_sieve to check a value < the lim the sieve
 * was created with */
int eratos_check(si_t *sieve, const ull_t n)
{
    if ((n != 2 && ~n & 1) || (n < 2)) 
        return 0;
    else
        return !(sieve[n >> 6] & (1 << (n >> 1 & 31)));
}

/* Convert to char* for guaranteed 8-bit size */
/* Calculates a true/false bit_sieve for all values up to ulim */
si_t *eratos_sieve(const ull_t ulim)
{
    ull_t i, j;
    si_t *sieve = calloc((ulim >> 6) + 1, sizeof(si_t));

    for (i = 3; i < sqrt(ulim) + 1; i += 2)
        if (!(sieve[i >> 6] & (1 << (i >> 1 & 31))))
            for (j = i*i; j < ulim; j += (i << 1))
                sieve[j >> 6] |= (1 << (j >> 1 & 31));

    return sieve;
}

/* Computes the mod_exp of the passed parameters */
ull_t modular_exp(ull_t base, ull_t exp, ull_t mod)
{
    ull_t result = 1;
    while (exp) {
        if (exp & 1)
            result = (result * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

/* Called by mr_prime_test when testing a potential candidate with a given rand value */
static int mr_witness(ull_t rand, ull_t val, ull_t exp, ull_t rem)
{
    ull_t x = modular_exp(rand, rem, val);
    ull_t y = 0;

    while (exp) {
        y = (x * x) % val;
        if (y == 1 && x != 1 && x != val - 1)
            return 0;
        x = y;
        --exp;
    }

    return y != 1 ? 0 : 1;
}

/* Miller-Rabin primality test */
int mr_prime_test(const ull_t val)
{
    if (((~val & 1) && val != 2) || (val < 2) || (!(val % 3) && val != 3))
        return 0;
    if (val <= 3)
        return 1;

    /* Check prime_table for small primes */
    if (val <= 1000) {
        int i;
        for (i = NUM_PRIMES - 1; i >= 0; --i) {
            if (val == prime_table[i])
                return 1;
            if (val > prime_table[i])
                return 0;
        }
    }

    int rem = val >> 1;
    int exp = 1;
    while (~rem & 1) {
        rem >>= 1;
        exp++;
    }

    /* Return correct deterministic witnesses depending on the input range */
    if (val < 1373653)
        return mr_witness(2, val, exp, rem) && mr_witness(3, val, exp, rem);
    else if (val < 9080191)
        return mr_witness(31, val, exp, rem) && mr_witness(73, val, exp, rem);
    else if (val < 4759123141)
        return mr_witness(2, val, exp, rem) && mr_witness(7, val, exp, rem) &&
               mr_witness(61, val, exp, rem);
    else if (val < 1122004669633)
        return mr_witness(2, val, exp, rem) && mr_witness(13, val, exp, rem) &&
               mr_witness(23, val, exp, rem) && mr_witness(1662803, val, exp, rem);
    else if (val < 2152302898747)
        return mr_witness(2, val, exp, rem) && mr_witness(3, val, exp, rem) &&
               mr_witness(5, val, exp, rem) && mr_witness(7, val, exp, rem) &&
               mr_witness(11, val, exp, rem);
    else if (val < 3474749660383)
        return mr_witness(2, val, exp, rem) && mr_witness(3, val, exp, rem) &&
               mr_witness(5, val, exp, rem) && mr_witness(7, val, exp, rem) &&
               mr_witness(11, val, exp, rem) && mr_witness(13, val, exp, rem);
    else 
        return mr_witness(2, val, exp, rem) && mr_witness(3, val, exp, rem) &&
               mr_witness(5, val, exp, rem) && mr_witness(7, val, exp, rem) &&
               mr_witness(11, val, exp, rem) && mr_witness(13, val, exp, rem) &&
               mr_witness(17, val, exp, rem);
}

/* Print out a struct pfact */
void factor_print(struct pfact *f)
{
    int f_idx;
    for (f_idx = 0; f->factors[f_idx]; ++f_idx) {
        int p_idx = f->powers[f_idx];
        while (p_idx) {
            printf("%llu ", f->factors[f_idx]);
            --p_idx;
        }
    }

    printf("\n");
}

/* Binary gcd calculation */
ull_t gcd(ull_t u, ull_t v)
{
    if (!u) return v;
    if (!v) return u;

    int shift;
    for (shift = 0; !((u | v) & 1); ++shift) {
        u >>= 1;
        v >>= 1;
    }

    while (!(u & 1))
        u >>= 1;

    do {
        while (!(v & 1)) v >>= 1;
        if (u > v) swap(u, v);
        v -= u;
    } while (v);

    return u << shift;
}

static int perfect_sq(const ull_t n)
{
    /* Filter obvious non-squares */
    if ( (n & 2)   == 2   || (n & 7)   == 5
      || (n & 11)  == 8   || (n & 32)  == 20
      || (n & 47)  == 32  || (n & 127) == 80
      || (n & 191) == 128 || (n & 511) == 320)
        return 0;

    ull_t r = sqrt(n) + 0.5;
    return r * r == n;
}

/* Shanks square-form factorization method */
static ull_t squfof(ull_t n)
{
#define pre(x)  ((x) == 0 ? 2 : (x) - 1)
#define post(x) ((x) == 2 ? 0 : (x) + 1)
#define __squfofloop__(expr)\
    do {\
        i = 1;\
        do {\
            bi         = (_sqrtkn + p[pre(i)]) / q[i];\
            p[i]       = bi * q[i] - p[pre(i)];\
            q[post(i)] = q[pre(i)] + bi * (p[pre(i)] - p[i]);\
            i          = post(i);\
        } while (expr);\
    } while (0)

    /* Filter any squares first */
    if (perfect_sq(n)) {
        /* Reduce n to lowest power */
        const ull_t v = sqrt(n);
        while (!(n % v))
            n /= v;
        
        /* Return this value if it was square, else continue */
        if (mr_prime_test(n))
            return n;
    }

    /* Just use integer successive multipliers */
    int k = 2;
    int i;
    ull_t f;

    do {
        const ull_t _sqrtkn = sqrt(k*n);
        ull_t p[3];
        ull_t q[3];
        ull_t bi;

        /* Init values for first pass */
        p[0] = _sqrtkn;
        q[0] = 1;
        q[1] = k*n - p[0] * p[0];
        __squfofloop__(!perfect_sq(q[i]));

        /* Init values for second pass */
        ull_t b0 = (_sqrtkn - p[pre(i)]) / sqrt(q[i]);
        p[0]     = b0 * sqrt(q[i]) + p[pre(i)];
        q[0]     = sqrt(q[i]);
        q[1]     = (k*n - p[0] * p[0]) / q[0];
        __squfofloop__(p[post(i)] != p[i]);

        f = gcd(n, p[i]);
        ++k;
    } while (f == 1 || f == n);
    
    return f;
}

/* Get a struct containing all prime factors and powers of val */
struct pfact* factor(ull_t val)
{
    struct pfact *f = malloc(sizeof(struct pfact));
    memset(f, 0, sizeof(struct pfact));

    /* Trial divide small primes first */
    int f_idx = 0;
    int i;
    for (i = 0; i < NUM_PRIMES && val != 1; ++i) {
        if (!(val % prime_table[i])) {
            f->factors[f_idx] = prime_table[i];
            do {
                f->powers[f_idx]++;
                val /= prime_table[i];
            } while (!(val % prime_table[i]));
            f_idx++;
        }
    }

    /* Check if we finished factorization. If we didn't, use squfof method */
    if (val != 1) {
        if (mr_prime_test(val)) {
            f->factors[f_idx] = val;
            f->powers[f_idx]  = 1;
        }
        else {
            /* If we found a factor, then divide through by all powers of this */
            while (val != 1 && !mr_prime_test(val)) {
                ull_t candidate = squfof(val);
                f->factors[f_idx] = candidate;
                do {
                    f->powers[f_idx]++;
                    val /= candidate;
                } while (val != 1 && val % candidate == 0);
                f_idx++;
            }

            /* If we exit with a prime value, ensure we add this to factor */
            if (val != 1) {
                f->factors[f_idx] = val;
                f->powers[f_idx]++;
            }
        }
    }

    return f;
}

/* Calculates the totient of a value */
ull_t totient(ull_t val)
{
    if (mr_prime_test(val)) return val - 1;

    struct pfact *p = factor(val);
    ull_t prod = 1;

    size_t i;
    for (i = 0; p->factors[i]; ++i) {
        prod *= (pow(p->factors[i], p->powers[i]) 
               - pow(p->factors[i], p->powers[i] - 1));
    }

    return prod;
}
