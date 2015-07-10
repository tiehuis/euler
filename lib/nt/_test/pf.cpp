#include <iostream>
#include "../prime/factor.hpp"

int main(void)
{
    prime::factors pf = prime::factor::get(600851475143ULL);

    for (auto i : pf)
        std::cout << i << " ";
    std::cout << "\n";
}
