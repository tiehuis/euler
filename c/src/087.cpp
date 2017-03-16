#include <array>
#include <bitset>
#include <iostream>
#include <libnt/prime/sieve.hpp>

int main(void)
{
    // 7100 ^ 2 > 50e6
    const int bound = 7100;
    const uint64_t bbound = 50000000;

    nt::prime::iterator ps = nt::prime::sieve(bound).get_iterator();
    std::array<std::array<uint64_t, 3>, bound> powers;
    std::bitset<bbound> bset;

    for (auto a : ps) {
        powers[a] = {{
            static_cast<uint64_t>(std::pow(a, 2)),
            static_cast<uint64_t>(std::pow(a, 3)),
            static_cast<uint64_t>(std::pow(a, 4))
        }};
    }

    int sm = 0;

    for (auto a : ps) {
        for (auto b : ps) {
            for (auto c : ps) {
                const uint64_t p = powers[a][0] + powers[b][1] + powers[c][2];
                if (p > bbound)
                    break;

                if (bset.test(p) == false) {
                    bset.set(p);
                    sm++;
                }
            }
        }
    }

    std::cout << sm << "\n";
}
