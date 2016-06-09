#include <array>
#include <iostream>
#include <vector>

typedef std::array<int, 6> triangle;

bool contains_origin(const triangle &t)
{
    const double a = 1.0f / 2 * (-t[3] * t[4] + t[1] * (-t[2] + t[4]) +
                                   t[0] * (t[3] - t[5]) + t[2] * t[5]);
    const int p = a < 0 ? -1 : 1;
    const double s = (t[1] * t[4] - t[0] * t[5]) * p;
    const double r = (t[0] * t[3] - t[1] * t[2]) * p;

    return s > 0 && r > 0 && (s + r) < 2 * a * p;
}

int main(void)
{
    std::vector<triangle> triangles = {
        #include <102.data>
    };

    int sm = 0;

    for (auto &i : triangles) {
        if (contains_origin(i))
            ++sm;
    }

    std::cout << sm << "\n";
}
