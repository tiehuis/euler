#include <algorithm>
#include <iostream>
#include <string>
#include <libnt/prime/sieve.hpp>

int main(void)
{
    nt::prime::sieve ps(10000);
    std::vector<uint64_t> pr;

    for (auto i : ps.get_iterator()) {
        if (i < 1000) continue;

        pr.clear();
        std::string s = std::to_string(i);

        do {
            const uint64_t si = std::stoi(s);
            if (ps.is_prime(si))
                pr.push_back(si);
        } while (std::next_permutation(s.begin(), s.end()));

        for (int i = 0; i < pr.size(); ++i) {
            for (int j = i + 1; j < pr.size(); ++j) {
                for (int k = j + 1; k < pr.size(); ++k) {
                    if (pr[k] - pr[j] == pr[j] - pr[i] && pr[i] != 1487) {
                        std::cout << pr[i] << pr[j] << pr[k] << "\n";
                        goto end__;
                    }
                }
            }
        }
    }

end__:;
}
