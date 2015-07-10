#pragma once

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <vector>

namespace nt {
namespace prime {

class sieve {
private:
    std::vector<bool> data;

    void extend__(const uint64_t ul)
    {
        const uint64_t nres = ul >> 1,
                       ores = data.size(),
                       sqrtul = std::sqrt(ul);

        data.reserve(nres);
        std::fill(data.begin(), data.end(), false);

        for (uint64_t i = 3; i < sqrtul + 1; i += 2) {
            if (!data[i >> 1]) {
                for (uint64_t j = i * i; j < ul; j += (i << 1))
                    data[j >> 1] = true;
            }
        }
    }

    uint64_t nth_prime_upper_bound__(const uint64_t n)
    {
        return n * std::log(n) + n * (std::log(std::log(n)) - 0.9385) + 1;
    }

public:
    enum class bound {
        limit, nth
    };

    int resieve(const uint64_t ul, bound s = bound::limit)
    {
        const uint64_t bound = s == bound::limit ?
                            ul : nth_prime_upper_bound__(ul);

        extend__(bound);
        return bound;
    }

    sieve(const uint64_t ul, bound s = bound::limit)
    {
        resieve(ul, s);
    }

    bool is_prime(const uint64_t n)
    {
        if ((~n & 1 && n != 2) || n < 2)
            return false;
        else
            return !data[n >> 1];
    }

    uint64_t get_nth(const uint64_t n)
    {
        if (n == 1)
            return 2;

        int pn = 1, i = 1;
        while (pn < n) {
            i += 2;
            if (is_prime(i))
                ++pn;
        }

        return i;
    }
};

} // end prime namespace
} // end nt namespace
