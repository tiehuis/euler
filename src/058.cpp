#include <iostream>
#include <libnt/prime/test.hpp>

int main(void)
{
    uint64_t i = 1,
             st = 2,
             tt = 1,
             sm = 0;

    do {
        for (int j = 0; j < 4; ++j) {
            i += st;
            sm += nt::prime::test::mr(i) ? 1 : 0;
        }

        st  += 2;
        tt += 4;
    } while (((100 * sm) / tt) >= 10);

    std::cout << ((tt - 1) / 2) + 1 << "\n";
}
