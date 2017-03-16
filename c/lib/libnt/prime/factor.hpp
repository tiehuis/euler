#pragma once

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <vector>
#include "test.hpp"
#include "sieve.hpp"
#include "../nt.hpp"

namespace {
    static const int ptable__[] = {
        2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61,
        67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137,
        139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211,
        223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283,
        293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379,
        383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461,
        463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563,
        569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643,
        647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739,
        743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829,
        839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937,
        941, 947, 953, 967, 971, 977, 983, 991, 997
    };

    static const int ptable_size__ = sizeof(ptable__) / sizeof(ptable__[0]);
}

namespace nt {
namespace prime {

typedef std::vector<uint64_t> factors;

namespace factor {

// not working
uint64_t squfof(uint64_t n)
{
    const uint64_t kt__[] = {
        3, 5, 7, 11, 15, 21, 33, 35, 55, 77, 105, 165, 231, 385, 1155
    };

    const size_t ks__ = sizeof(kt__) / sizeof(kt__[0]);

    while (nt::is_square(n)) {
        uint64_t f = std::sqrt(n);
        while (n % f == 0)
            n /= f;

        if (n == 1) {
            if (prime::test::mr(f))
                return f;
            else
                n = f;
        }
    }

    const size_t cycle_max__ = 10000;

#define squfof_loop__(cond)                             \
    do {                                                \
        size_t cc = 0;                                  \
        do {                                            \
            bi = (sqrtkn + p[il]) / q[ic];              \
            p[ic] = bi * q[ic] - p[il];                 \
            q[in] = q[il] + bi * (p[il] - p[ic]);       \
            parity |= 1;                                \
            il = il + 1 == 3 ? 0 : il + 1;              \
            ic = ic + 1 == 3 ? 0 : ic + 1;              \
            in = in + 1 == 3 ? 0 : in + 1;              \
        } while ((cond) && cc++ < cycle_max__);         \
        if (cc >= cycle_max__) goto continue__;         \
    } while (0)

    size_t ki = 0, parity = 0;
    uint64_t factor = 0;

    do {
        size_t il = 0, ic = 1, in = 2;
        uint64_t p[3]{0}, q[3]{0}, bi;
        const uint64_t k = kt__[ki], sqrtkn = std::sqrt(k * n);

        // First iteration
        p[0] = sqrtkn;
        q[0] = 1;
        q[1] = k * n - p[0] * p[0];
        squfof_loop__(!nt::is_square(q[ic]) && parity % 2 == 0);

        // Second iteration
        bi = (sqrtkn - p[il]) / q[ic];
        p[0] = bi * std::sqrt(q[ic]) + p[il];
        q[0] = std::sqrt(q[ic]);
        q[1] = (k * n - p[0] * p[0]) / q[0];
        squfof_loop__(p[ic] != p[il]);
        factor = nt::gcd(n, p[ic]);
continue__:;
    } while ((factor == 1 || factor == n) && ++ki < ks__);

#undef squfof_loop__

    if (ki > ks__)
        return 0;
    else
        return factor;
}

uint64_t naive(nt::prime::sieve &ps, const uint64_t n, const uint64_t start = 2)
{
    if (n < 2)
        return 0;

    if (start < 1000) {
        for (size_t i = 0; i < ptable_size__ && i < std::sqrt(n) ; ++i) {
            if (n * n > ptable__[i])
                break;
            if (n % ptable__[i] == 0)
                return ptable__[i];
        }
    }

    uint64_t i = 1001, ns = ps.nelements();

    while (i >= ns) {
        ns = 2 * ns + 1;
    }

    if (ns != ps.nelements())
        ps.resieve(2 * ps.nelements());

    while ((!ps.is_prime(i) || n % i != 0) && i < std::sqrt(n)) {
        i += 2;
        if (i >= ps.nelements()) {
            ps.resieve(2 * ps.nelements());
        }
    }

    return i < std::sqrt(n) ? i : n;
}

uint64_t fermat(const uint64_t n)
{
    const uint64_t cycle_max__ = 10000;
    uint64_t a = std::ceil(std::sqrt(n)),
             b = a * a - n,
             c = 0;

    while (!nt::is_square(b) && ++c < cycle_max__) {
        a = a + 1;
        b = a * a - n;
    }

    return c >= cycle_max__ ? 0 : a - std::sqrt(b);
}

uint64_t pollard_rho(const uint64_t n)
{
    uint64_t xa = 2, xb = 2;

    do {
        uint64_t s, a = std::pow(xa, 2) + 1,
                 b = std::pow(std::pow(xb, 2), 2) + 1;

        xa = a % n;
        xb = b % n;
        s = nt::gcd(xa > xb ? xa - xb : xb - xa, n);

        if (s > 1)
            return s;

    } while (xa != xb);

    return 0;
}

uint64_t pollard_p1(uint64_t n)
{
    const uint64_t cycle_max__ = 10000;
    uint64_t k2f = 1, k = 1, rk;

    while (++k < cycle_max__) {
        k2f = nt::powm(k2f, k, n);
        rk  = nt::gcd(k2f - 1, n);

        if (rk > 1)
            return rk;
    }

    return 0;
}

factors get(uint64_t n)
{
    factors fa;

    for (size_t i = 0; i < ptable_size__ && n > 1; ++i) {
        while (n % ptable__[i] == 0) {
            fa.push_back(ptable__[i]);
            n /= ptable__[i];
        }
    }

    if (n <= 1)
        return fa;

    if (prime::test::mr(n)) {
        fa.push_back(n);
    }
    else {
        uint64_t k = 1001;
        nt::prime::sieve ps(1001);
        while (!prime::test::mr(n)) {
            uint64_t c = squfof(n);

            //  squfof fails
            if (c == 0) {
                c = naive(ps, n, k);
                k = c; // store largest prime factor found so far
            }

            while (n % c == 0) {
                fa.push_back(c);
                n /= c;
            }
        }

        // add last prime value to factors
        if (n != 1) {
            fa.push_back(n);
        }
    }

    std::sort(fa.begin(), fa.end());
    return fa;
}

factors get(nt::prime::sieve &ps, uint64_t n)
{
    factors fa;

    for (size_t i = 0; i < ptable_size__ && n > 1; ++i) {
        while (n % ptable__[i] == 0) {
            fa.push_back(ptable__[i]);
            n /= ptable__[i];
        }
    }

    if (n <= 1)
        return fa;

    if (prime::test::mr(n)) {
        fa.push_back(n);
    }
    else {
        uint64_t k = 1001;
        while (!prime::test::mr(n)) {
            uint64_t c = 0;//squfof(n);

            //  squfof fails
            if (c == 0) {
                c = naive(ps, n, k);
                k = c; // store largest prime factor found so far
            }

            while (n % c == 0) {
                fa.push_back(c);
                n /= c;
            }
        }

        // add last prime value to factors
        if (n != 1) {
            fa.push_back(n);
        }
    }

    std::sort(fa.begin(), fa.end());
    return fa;
}

} // end factor namespace
} // end prime namespace
} // end nt namespace
