#pragma once

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <random>
#include "../nt.hpp"

namespace {

    #define NT_PRIME_QUICK_BREAK__(x)\
        do {\
            if ((x) <= 3)\
                return (x) & 2;\
            else if ((x) % 2 == 0 || (x) % 3 == 0)\
                return false;\
        } while (0)

    bool mr_witness__(uint64_t n, uint64_t v, uint64_t e, uint64_t r)
    {
        uint64_t x = nt::powm(n, r, v), y = 0;

        while (e) {
            y = (x * x) % v;
            if (y == 1 && x != 1 & x != v - 1)
                return false;
            x = y;
            --e;
        }

        return y != 1 ? 0 : 1;
    }

} // end anonymous namespace

namespace nt {
namespace prime {
namespace test {

bool mr(const uint64_t v)
{
    NT_PRIME_QUICK_BREAK__(v);

    uint64_t r = v >> 1, e = 1;

    while (~r & 1) {
        r >>= 1;
        ++e;
    }

#define m_(x) mr_witness__((x), v, e, r)

    if (v < 1373653)
        return m_(2) && m_(3);
    else if (v < 9080191)
        return m_(31) && m_(73);
    else if (v < 4759123141ULL)
        return m_(2) && m_(7) && m_(61);
    else if (v < 1122004669633ULL)
        return m_(2) && m_(13) && m_(23) && m_(1662803);
    else if (v < 2152302898747ULL)
        return m_(2) && m_(3) && m_(5) && m_(7) && m_(11);
    else if (v < 3474749660383ULL)
        return m_(2) && m_(3) && m_(5) && m_(7) && m_(11) && m_(13);
    else
        return m_(2) && m_(3) && m_(5) && m_(7) && m_(11) && m_(13) && m_(17);

#undef m_
}

bool naive(const uint64_t n)
{
    NT_PRIME_QUICK_BREAK__(n);

    uint64_t i = 5;
    while (i * i <= n) {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
        i += 6;
    }

    return true;
}

bool fermat(const uint64_t n, uint64_t reps = 100)
{
    NT_PRIME_QUICK_BREAK__(n);

    std::default_random_engine generator;
    std::uniform_int_distribution<uint64_t> distribution(2, n - 2);

    while (reps--) {
        uint64_t a = distribution(generator);
        if (nt::powm(a, n - 1, n) != 1)
            return false;
    }

    return true;
}

// Unfinished
bool aks(const uint64_t n)
{
    NT_PRIME_QUICK_BREAK__(n);

    for (uint64_t b = 2; b < std::log2(n); ++b) {
        const double a = std::pow(n, 1.0 / b);
        if (std::trunc(a) == a)
            return false;
    }

    uint64_t r, l2n = std::log2(n) * std::log2(n),
             l2r = std::max(3UL, static_cast<uint64_t>(pow(std::log2(n), 5)));

    for (r = 2; r < l2r; ++r) {
        for (uint64_t k = 1; k <= l2n; ++k) {
            if (nt::powm(n, k, r) == 1 || nt::powm(n, k, r) == 0)
                goto break_loop__;
        }
    }

break_loop__:

    for (uint64_t a = r; a > 1; --a) {
        const uint64_t g = nt::gcd(a, n);
        if (1 < g && g < n)
            return false;
    }

    if (n <= r || n > 5690034)
        return true;

    // Step 6
    return false;

}

} // end test namespace
} // end prime namespace
} // end nt namespace
