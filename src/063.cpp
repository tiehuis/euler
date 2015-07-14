#include <cmath>
#include <iostream>

int main(void)
{
    int sm = 0;

    for (int i = 1; i < 50; ++i)
        sm += 10 - std::ceil(std::pow(10, 1 - 1.0f / i));

    std::cout << sm << "\n";
}
