#include <iostream>
#include "../prime/factor.hpp"

using namespace nt::prime;

int main(void)
{
    factors pf = factor::get(600851475143ULL);

    for (auto i : pf)
        std::cout << i << " ";
    std::cout << "\n";
}
