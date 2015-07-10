#include <algorithm>
#include <cstdint>
#include <iostream>
#include <string>
#include <libnt/prime/test.hpp>

int str3toi(std::string &s, int p)
{
    return (s[p] - '0') * 100 + (s[p + 1] - '0') * 10 + (s[p + 2] - '0');
}

bool is_divisible(std::string &s)
{
    int p[] = { 2, 3, 5, 7, 11, 13, 17 };

    for (int i = 1; i < 8; ++i) {
        if (str3toi(s, i) % p[i - 1] != 0)
            return false;
    }

    return true;
}

int main(void)
{
    std::string s = "0123456789";
    uint64_t sm = 0;

    do {
        if (is_divisible(s))
            sm += std::stoull(s);
    } while (std::next_permutation(s.begin(), s.end()));

    std::cout << sm << "\n";
}
