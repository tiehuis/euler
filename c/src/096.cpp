#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <vector>

namespace sudoku {
    typedef std::array<int, 81> puzzle;

namespace {
    bool is_valid__(puzzle &g, int i, int v)
    {
        for (int j = i % 9; j < 81; j += 9) {
            if (g[j] == v)
                return false;
        }

        for (int j = i - (i % 9); j < i + 9 - (i % 9); ++j) {
            if (g[j] == v)
                return false;
        }

        for (int j = i - (i % 3) - 9 * std::floor((i % 27) / 9), k = 0;
                 k < 9; j += ++k % 3 ? 1 : 7) {
            if (g[j] == v)
                return false;
        }

        return true;
    }

    bool backtrack__(puzzle &g, int i)
    {
        if (i >= 81)
            return true;

        for (int v = 9; v > 0; --v) {
            if (!is_valid__(g, i, v))
                continue;

            g[i] = v;
            if (backtrack__(g, std::find(g.begin() + i, g.end(), 0) - g.begin()))
                return true;
        }

        g[i] = 0;
        return false;
    }
}

    puzzle solve(puzzle &g_)
    {
        puzzle g = g_;
        backtrack__(g, std::find(g.begin(), g.end(), 0) - g.begin());
        return g;
    }
}

int main(void)
{
    std::vector<sudoku::puzzle> sudoku_puzzles = {
        #include <096.data>
    };

    int sm = 0;

    for (auto &g : sudoku_puzzles) {
        sudoku::puzzle r = sudoku::solve(g);
        sm += r[0] * 100 + r[1] * 10 + r[2];
    }

    std::cout << sm << "\n";
}
