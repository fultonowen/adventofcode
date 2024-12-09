#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

void read_file(std::vector<std::vector<uint64_t>>& xs) {
    std::ifstream ifs;
    ifs.open("input.txt");
    std::string line;
    if (ifs.is_open()) {
        while (getline(ifs, line)) {
            std::stringstream ss(line);
            std::string level;
            std::vector<uint64_t> _xs;
            getline(ss, level, ':');
            _xs.push_back(std::stol(level));
            getline(ss, level, ' ');
            while (getline(ss, level, ' ')) {
                _xs.push_back(std::stol(level));
            }
            xs.push_back(_xs);
        }
        ifs.close();
    } else std::cout << "Unable to open file" << std::endl;
}

uint64_t concat(uint64_t l, const uint64_t r) {
    uint64_t c = r;
    while (c!= 0u) {
        c/=10;
        l*=10;
    }
    return l+r;
}

bool backtrack(std::vector<uint64_t>& level, int i, uint64_t curr_total, bool enable_concat = false) {
    if (i == level.size()) return curr_total == level[0];
    if (curr_total > level[0]) return false;

    if (backtrack(level, i+1, curr_total + level[i], enable_concat) || backtrack(level, i+1, curr_total * level[i], enable_concat) || (enable_concat && backtrack(level, i+1, concat(curr_total, level[i]), true)))
        return true;

    return false;
}

void evaluate1(std::vector<std::vector<uint64_t>>& list1) {
    uint64_t ans = 0;
    for (std::vector<uint64_t>& xs : list1) {
        if (backtrack(xs, 2, xs[1])) ans += xs[0];
    }
    std::cout << "Answer: " << ans << std::endl;
}

void evaluate2(std::vector<std::vector<uint64_t>>& list1) {
    uint64_t ans = 0;
    for (std::vector<uint64_t>& xs : list1) {
        if (backtrack(xs, 2, xs[1], true)) ans += xs[0];
    }
    std::cout << "Answer: " << ans << std::endl;
}

int main() {
    std::vector<std::vector<uint64_t>> levels;
    read_file(levels);
    evaluate1(levels);
    evaluate2(levels);
    return 0;
}


