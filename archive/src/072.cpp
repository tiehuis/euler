#include <iostream>
#include <libnt/nt/ntf.hpp>

int main(void)
{
    const int bound = 1000000;
    std::cout << nt::ntf::totient_sum(bound, bound) - 1 << "\n";
}
