#include <iostream>
#include <libnt/nt.hpp>

int main(void)
{
    int r = 0;
    for (int i = 2; i != -1; ++i) {
        int n = i * (3 * i - 1) / 2;

        for (int j = i - 1; j > 0; --j) {
            int m = j * (3 * j - 1) / 2;

            if (nt::is_pentagonal(n - m) & nt::is_pentagonal(n + m)) {
                r = n - m;
                i = -2;
                break;
            }
        }
    }

    std::cout << r << "\n";
}
