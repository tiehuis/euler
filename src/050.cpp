#include <algorithm>
#include <iostream>
#include <libnt/prime/sieve.hpp>

int main(void)
{
    const int lim = 1000000;

    nt::prime::sieve ps(lim);
    nt::prime::iterator pi = ps.get_iterator();
    std::vector<uint64_t> pm;

    pm.push_back(pi[0]);
    for (int i = 1; i < pi.size(); ++i) {
        pm.push_back(pm[i - 1] + pi[i]);
    }

    int r = 0, ns = 0;
    for (int i = ns; i < pm.size(); ++i) {
        for (int j = i - ns - 1; j >= 0; --j) {
            if (pm[i] - pm[j] > lim)
                break;

            if (std::binary_search(pi.begin(), pi.end(), pm[i] - pm[j])) {
                ns = i - j;
                r = pm[i] - pm[j];
            }
        }
    }

    std::cout << r << "\n";
}
