#pragma once

// This file cannot include other files in this library, and is where base
// functions with no dependencies should probably be kept

#include <algorithm>
#include <cmath>
#include <cstdint>

namespace {

uint64_t gcd__(uint64_t a, uint64_t b)
{
    if (a == 0)
        return b;
    if (b == 0)
        return a;

    int s = 0;
    for (s = 0; ((a | b) & 1) == 0; ++s) {
        a >>= 1;
        b >>= 1;
    }

    while ((a & 1) == 0)
        a >>= 1;

    do {
        while ((b & 1) == 0)
            b >>= 1;
        if (a > b)
            std::swap(a, b);
        b -= a;
    } while (b);

    return a << s;
}

uint64_t lcm__(uint64_t a, uint64_t b)
{
    return a / gcd__(a, b) * b;
}

bool coprime__(uint64_t a, uint64_t b)
{
    return gcd__(a, b) == 1;
}

} // end anonymous namespace

namespace nt {


bool is_square(const uint64_t n)
{
    if ((n & 2) == 2 || (n & 7) == 5 || (n & 11) == 8 || (n & 32) == 20 ||
        (n & 47) == 32 || (n & 127) == 80 || (n & 191) == 128 ||
        (n & 511) == 320)
        return false;

    const uint64_t r = std::sqrt(n) + 0.5f;
    return r * r == n;
}

uint64_t modm(uint64_t a, uint64_t b, uint64_t m)
{
    return 0;
}

uint64_t powm(uint64_t b, uint64_t e, uint64_t m)
{
    uint64_t r = 1;

    while (e) {
        if (e & 1)
            r = (r * b) % m;
        b = (b * b) % m;
        e >>= 1;
    }

    return r;
}

uint64_t factorial(uint64_t n)
{
    uint64_t s = 1;
    while (n)
        s *= n--;
    return s;
}

template <typename T>
T gcd(T first)
{
    return first;
}

template <typename T, typename... Args>
T gcd(T first, Args... args)
{
    return gcd__(first, gcd(args...));
}

template <typename T>
T lcm(T first)
{
    return first;
}

template <typename T, typename... Args>
T lcm(T first, Args... args)
{
    return lcm__(first, lcm(args...));
}

template <typename T>
bool coprime(T first)
{
    return true;
}

template <typename T, typename... Args>
bool coprime(T first, T second, Args... args)
{
    return coprime__(first, second) && coprime(first + second, args...);
}

} // end namespace nt
