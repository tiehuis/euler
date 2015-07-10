#include <cstdint>

namespace {

    const uint64_t ftable__[] = {
        1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 81
    };

    const size_t ftable_size__ = sizeof(ftable__) / sizeof(ftable__[0]);

    uint64_t fib__(const uint64_t n)
    {
        if (n < ftable_size__)
            return ftable__[n];

        return fib__
    }
}

namespace nt {
namespace fib {

uint64_t get_nth(const uint64_t n)
{
    return
}

uint64_t next(const uint64_t n, const size_t skip = 1)
{
    for (size_t i = 0; i < skip; ++i) {

    }
}

} // end fib namespace
} // end nt namespace

