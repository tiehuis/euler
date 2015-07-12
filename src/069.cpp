#include <iostream>
#include <libnt/nt/ntf.hpp>

int main(void)
{
    const int bound = 1000001;
    std::vector<uint64_t> ts = nt::ntf::totient_sieve(bound);

    float mv = 0;
    int mi = 0;

    for (int i = 2; i < bound; ++i) {
        const float tv = i / static_cast<float>(ts[i]);
        if (tv > mv) {
            mv = tv;
            mi = i;
        }
    }

    std::cout << mi << "\n";
}
