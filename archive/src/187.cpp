#include <iostream>
#include <libnt/prime/sieve.hpp>

int main(void)
{
    const uint64_t bound = 50000000ULL;
    nt::prime::sieve ps(bound);
    int sm = 0;

    #pragma omp parallel for
    for (uint64_t i = 2; i < ps.nelements(); i += i & 1 ? 2 : 1) {
        if (!ps.is_prime(i))
            continue;

        for (uint64_t j = i; j < ps.nelements(); j += j & 1 ? 2 : 1) {
            if (!ps.is_prime(j))
                continue;

            if (i * j > 2 * bound)
                break;

            sm++;
        }
    }

    std::cout << sm << "\n";
}
