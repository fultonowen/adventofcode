#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_set>

// Each stripe can be white (w), blue (u), black (b), red (r), or green (g)
void read_file(std::unordered_set<std::string>& sub_towels, std::vector<std::string>& towels) {
    std::ifstream ifs;
    ifs.open("input.txt");
    std::string line;
    if (ifs.is_open()) {
        getline(ifs, line);
        std::stringstream ss(line);
        std::string pattern;
        while (ss >> pattern) {
            if (pattern.empty()) break;
            if (pattern[pattern.size()-1] == ',') {
                pattern = pattern.substr(0, pattern.size() -1);
            }
            sub_towels.insert(pattern);
        }
        getline(ifs, line);
        while (getline(ifs, line)) {
            towels.push_back(line);
        }
        ifs.close();
    } else std::cout << "Unable to open file" << std::endl;
}

uint64_t can_make(const std::unordered_set<std::string>& designs, const std::string& x, std::unordered_map<std::string, uint64_t>& cache) {
    if (cache.contains(x)) {
        return cache[x];
    }
    uint64_t count = 0;
    if (designs.contains(x)) {
        count++;
    }

    for (int i = 1; i < x.size(); i++) {
        const auto left = x.substr(0, i);
        if (!designs.contains(left)) {
            continue;
        }
        if (can_make(designs, left, cache) == 0) continue;
        const auto right = x.substr(i, x.size()-i);
        count += can_make(designs, right, cache);
    }
    cache[x] = count;
    return count;
}

// Part 1:
void evaluate1(std::unordered_set<std::string>& designs, std::vector<std::string>& xs) {
    int ans = 0;
    std::unordered_map<std::string, uint64_t> c;
    for (std::string& x : xs) {
        if (can_make(designs, x, c) > 0) ans++;
    }
    std::cout << "Answer: " << ans << std::endl;
}

// Part 2:
void evaluate2(std::unordered_set<std::string>& designs, std::vector<std::string>& xs) {
    uint64_t ans = 0;
    std::unordered_map<std::string, uint64_t> c;
    for (std::string& x : xs) {
        ans += can_make(designs, x, c);
    }
    std::cout << "Answer: " << ans << std::endl;
}

int main() {
    std::unordered_set<std::string> designs;
    std::vector<std::string> towels;
    read_file(designs, towels);
    evaluate1(designs, towels);
    evaluate2(designs, towels);
    return 0;
}

