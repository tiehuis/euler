#include <iostream>

// 1_2_3_4_5_6_7_8_9_0
//
// The square of an even number n -> n % 4 == 0
// This implies the last digit must be even.

bool of_form(uint64_t p)
{
    unsigned long r[] = { 0, 9, 8, 7, 6, 5, 4, 3, 2, 1 };

    for (int i = 0; p != 0; ++i, p /= 100) {
        if (p % 10 != r[i])
            return false;
    }

    return true;
}

int main(void)
{
    uint64_t r;

    for (r = 1010101010ULL; !of_form(r * r); r += 10);

    std::cout << r << "\n";
}
