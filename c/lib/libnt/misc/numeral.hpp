#include <algorithm>
#include <string>

namespace {
    enum {
        I = 1,
        V = 5,
        X = 10,
        L = 50,
        C = 100,
        D = 500,
        M = 1000
    }
}

namespace misc {
namespace numeral {

int minimum_symbols(uint64_t n)
{
#define loop__(c, i)        \
    do {                    \
        while (n >= (c)) {  \
            n -= (c);       \
            c += (i);       \
        }                   \
    } while (0)

    int c = 0;

    loop__(M, 1);
    loop__(M - C, 2);
    loop__(D, 1);
    loop__(D - C, 2);
    loop__(C, 1);
    loop__(C - X, 2);
    loop__(L, 1);
    loop__(L - X, 2);
    loop__(X, 1);
    loop__(X - I, 2);
    loop__(V, 1);
    loop__(V - I, 2);
    loop__(I, 1);

    return c;

#undef loop__
}

uint64_t from(std::string &s)
{
    std::for_each(s.begin(), s.end(), std::toupper);

    int v = 0;
    for (int i = 0; i < s.size(); ++i) {
        switch (s[i]) {
        case 'I':
            v += (s[i + 1] == 'V' || s[i + 1] == 'X') ? -I : I;
            break;
        case 'V':
            v += V;
            break;
        case 'X':
            v += (s[i + 1] == 'L' || s[i + 1] == 'C') ? -X : X;
            break;
        case 'L':
            v += L;
            break;
        case 'C':
            v += (s[i + 1] == 'D' || s[i + 1] == 'M') ? -C : C;
            break;
        case 'D':
            v += D;
            break;
        case 'M':
            v += M;
            break;
        default:
            return -1;
        }
    }

    return v;
}

} // end numeral namespace
} // end misc namespace
