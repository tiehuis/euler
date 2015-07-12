#include <algorithm>
#include <iostream>
#include <string>
#include <libnt/nt/ntf.hpp>

int main(void)
{
    const int bound = 10000000;
    std::vector<uint64_t> ts = nt::ntf::totient_sieve(bound);

    float mv = 100;
    int mi = 0;

    for (int i = 2; i < bound; ++i) {
        std::string s1 = std::to_string(i),
                    s2 = std::to_string(ts[i]);

        if (std::is_permutation(s1.begin(), s1.end(), s2.begin())) {
            float tv = static_cast<float>(i) / ts[i];
            if (tv < mv) {
                mv = tv;
                mi = i;
            }
        }
    }

    std::cout << mi << "\n";
}
