#include <iostream>
#include <unordered_set>

long rectangles(int w, int h)
{
    return w * (w + 1) * h * (h + 1) / 4;
}

int main(void)
{
    int mi = 0, threshold = 2000000;

    for (int i = 1; i < 100; ++i) {
        for (int j = i; j < 100; ++j) {
            long tv = rectangles(i, j);
            if (std::abs(tv - 2000000) < threshold) {
                threshold = std::abs(tv - 2000000);
                mi = i * j;
            }
        }
    }

    std::cout << mi << "\n";
}
