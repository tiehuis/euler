#include <iostream>
#include <libnt/nt/ntf.hpp>

// Compute the totient of each number n less than the limit.
// Note: -1 + 2 * sum_{k=1}^{n} phi(k) = sum_{k=1}^n mu(k) floor(n/k)^2

int main(void)
{
    const int bound = 1000000;
    const std::vector<int> ms = nt::ntf::mu_sieve(bound);
    uint64_t sm = 0;

    for (int i = 1; i < bound; ++i) {
        sm += ms[i] * std::pow(std::floor(bound / i), 2);
    }

    std::cout << (sm + 1) / 2 - 1 << "\n";
}
