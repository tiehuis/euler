#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>

struct cube_pair {
    int n;
    std::string smallest;
};

int main(void)
{
    std::unordered_map<std::string, cube_pair> cubes;
    std::string sr;
    bool end_cond = false;

    for (uint64_t i = 345; !end_cond; ++i) {
        std::string p = std::to_string(i * i * i);
        std::string s(p);
        std::sort(s.begin(), s.end());

        if (cubes.find(s) == cubes.end()) {
            cubes[s] = { 1, p };
        }
        else {
            if (++cubes[s].n == 5) {
                sr = cubes[s].smallest;
                end_cond = true;
            }
        }
    }

    std::cout << sr << "\n";
}
