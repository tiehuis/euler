#include <cstdint>
#include "../prime/sieve.hpp"
#include "../prime/factor.hpp"
#include "../prime/test.hpp"

namespace nt {
namespace ntf {

uint64_t totient(prime::factors pf)
{
    uint64_t r = 1;

    for (size_t i = 0; i < pf.size(); ++i) {
        uint64_t fc = 0, c = i;

        for (; i < pf.size() && pf[i] == pf[c]; ++i)
            ++fc;

        r *= std::pow(pf[i], fc) - std::pow(pf[i], fc - 1);
        --i; // decrement so we don't skip two
    }

    return r;
}

std::vector<int> mu_sieve(uint64_t n)
{
    std::vector<int> ts(n);
    std::fill(ts.begin(), ts.end(), 1);
    prime::sieve ps(n);

    for (uint64_t i = 2; i < n; i += n & 1 ? 2 : 1) {
        if (ps.is_prime(i)) {
            for (uint64_t j = i; j < n; j += i)
                ts[j] *= -1;
            for (uint64_t j = i * i; j < n; j += i * i)
                ts[j] = 0;
        }
    }

    return ts;
}

uint64_t totient(const uint64_t n)
{
    if (prime::test::mr(n))
        return n - 1;

    prime::factors pf = prime::factor::get(n);
    return totient(pf);
}

uint64_t divisor(prime::factors pf, const uint64_t sigma = 0)
{
    uint64_t r = 1;

    for (size_t i = 0; i < pf.size(); ++i) {
        uint64_t fc = 0, c = i, p = 1;

        for (; i < pf.size() && pf[i] == pf[c]; ++i)
            ++fc;

        while (fc)
            p += std::pow(pf[i], sigma * fc--);

        r *= p;
        --i; // decrement so we don't skip two
    }

    return 0;
}

uint64_t divisor(const uint64_t n, const uint64_t sigma = 0)
{
    prime::factors pf = prime::factor::get(n);
    return divisor(pf, sigma);
}

uint64_t permutation(uint64_t n, uint64_t k)
{
    double r = 1;
    for (int i = 1; i <= n; ++i) {
        r *= (n + 1 - i);
        if (i <= k)
            r /= (k + 1 - i);
    }

    return static_cast<uint64_t>(r);
}

uint64_t binomial(uint64_t n, uint64_t k)
{
    if (k > n / 2)
        k = n - k;

    double r = 1;
    for (int i = 1; i <= k; ++i)
        r *= (n + 1 - i) / i;

    return static_cast<uint64_t>(r);
}

bool is_pentagonal(uint64_t n)
{
    const double f = (std::sqrt(24 * n + 1) + 1) / 6;
    return std::round(f) == f;
}

} // end ntf namespace
} // end nt namespace
