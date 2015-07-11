#pragma once

#include <algorithm>
#include <array>
#include <cstdint>
#include <string>

// This is a translation of 'https://github.com/eljefeo/DeadHorseEval'
// We expect cards to be of the form SUIT - VALUE, where value is always
// uppercase.
namespace nt {
namespace misc {
namespace poker {

    typedef std::array<std::string, 5> hand;

namespace {

    static const size_t tl_offset__ = 50;
    static const uint_fast32_t tl__[] = {
         0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80,  0,  0,
         0,  0,  0,  0,  0, 0x1000,  0,  0x4000,  0x2000,  0,
         0,  0,  0x8000,  0, 0x200, 0x800,  0,  0,  0,  0,
         0, 0x400,  0,  0x10000, 0x100,  0,  0,  0,  0,  0
    };

    typedef std::array<uint_fast32_t, 5> internal_hand__;

    void get_internal_hand__(internal_hand__ &ih, const hand &p)
    {
        std::fill(ih.begin(), ih.end(), 0);

        for (size_t i = 0; i < p.size(); ++i)
            ih[i] = tl__[p[i][0] - tl_offset__] | tl__[p[i][1] - tl_offset__];
    }
}

    uint64_t eval(const hand &p)
    {
        internal_hand__ h;
        get_internal_hand__(h, p);

        uint_fast32_t x, y, z, v, u,
                      a = h[0], b = h[1], c = h[2], d = h[3], e = h[4];

        x = (a ^ b ^ c ^ d ^ e) & 0x1fff;
        y = (a | b | c | d | e) & 0x1fff;
        z = y ^ x;
        v = y & (y - 1);
        v = !(v &= v - 1) ? 2 : !(v &= v - 1) ? 3 : !(v &= v - 1) ? 4 : 5;

        switch (v) {
        case 4:
            return 0x4000000ULL | x | (z << 13);
        case 3:
            return z != 0 ? 0x8000000ULL | x | (z << 13)
                : 0xc000000ULL |
                ((a & b) == (a & 0x1fff) ? a : (c & d) == (c & 0x1fff) ? c : e)
                & 0x1fff ^ y | (v << 13);
        case 2:
            return ((a + b + c + d + e - x) & 0x1fff) == (0x1fff & (y ^ x) << 2)
                    ? 0x1c000000ULL | x | (z << 13) : 0x18000000ULL | z | (x << 13);
        default:
            break;
        }

        bool s = 0x1f1d100 % y == 0, f = (a & b & c & d & e) != 0;

        return s && f ? 0x20000000ULL | (x == 0x100f ? 15 : x) : s
            ? 0x10000000ULL | (x == 0x100f ? 15 : x) : f ? 0x1f000000ULL | x : x;
    }

} // end poker namespace
} // end misc namespace
} // end nt namespace
