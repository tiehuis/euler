#include <cmath>
#include <iostream>

int main(void)
{
    const float actual = 3.0f / 7.0f;
    float epsilon = 10;
    int n = 0;

    for (int d = 7; d < 1000000; ++d) {
        int nm = std::floor(d * actual);
        float tv = nm / static_cast<float>(d);

        if (actual == tv)
            continue;
        else if (actual - tv < epsilon) {
            epsilon = actual - tv;
            n = nm;
        }
    }

    std::cout << n << "\n";
}
