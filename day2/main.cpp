#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

template <typename T>
void print_vec(std::vector<T>& xs) {
    std::cout << "{ ";
    for (T val : xs) {
        std::cout << val << ", ";
    }
    std::cout << "}" << std::endl;
}

void read_file(std::vector<std::vector<int>>& xs) {
    std::ifstream ifs;
    ifs.open("input.txt");
    std::string line;
    if (ifs.is_open()) {
        while (getline(ifs, line)) {
            std::stringstream ss(line);
            std::string level;
            std::vector<int> _xs;
            while (getline(ss, level, ' ')) {
                _xs.push_back(std::stoi(level));
            }
            xs.push_back(_xs);
        }
        ifs.close();
    } else std::cout << "Unable to open file" << std::endl;
}

int is_safe(const std::vector<int>& xs) {
    bool safe_dec = true, safe_inc = true;
    // safe decrease
    for (int i = 0; i < xs.size() - 1; i++) {
        if (!(xs[i] - xs[i+1] >= 1 && xs[i] - xs[i+1] <= 3)) {
            safe_dec = false;
            break;
        }
    }
    // safe increase
    for (int i = 0; i < xs.size() - 1; i++) {
        if (!(xs[i+1] - xs[i] >= 1 && xs[i+1] - xs[i] <= 3)) {
            safe_inc = false;
            break;
        }
    }
    return safe_dec || safe_inc ? 1 : 0;
}

int is_safe_with_dampening(const std::vector<int>& xs) {
    if (is_safe(xs)) return 1;
    int prev, i;
    for (int remove_level = 0; remove_level < xs.size(); remove_level++) {
        bool safe_dec = true, safe_inc = true;
        if (remove_level == 0) {
            i = 2; prev = xs[1];
        } else {
            i = 1; prev = xs[0];
        }

        // safe decrease
        for (i; i < xs.size(); i++) {
            if (i == remove_level) continue;
            if (!(prev - xs[i] >= 1 && prev - xs[i] <= 3)) {
                safe_dec = false;
                break;
            }
            prev = xs[i];
        }
        if (remove_level == 0) {
            i = 2; prev = xs[1];
        } else {
            i = 1; prev = xs[0];
        }
        // safe increase
        for (i; i < xs.size(); i++) {
            if (i == remove_level) continue;
            if (!(xs[i] - prev >= 1 && xs[i] - prev <= 3)) {
                safe_inc = false;
                break;
            }
            prev = xs[i];
        }
        if (safe_dec || safe_inc) return 1;

    }
    return 0;
}

void evaluate(std::vector<std::vector<int>>& list1) {
    int ans = 0;
    for (auto& v : list1) {
        ans += is_safe(v);
    }
    std::cout << "Answer: " << ans << std::endl;
}

void evaluate2(std::vector<std::vector<int>>& list1) {
    int ans = 0;
    for (auto & v : list1) {
        ans += is_safe_with_dampening(v);
    }
    std::cout << "Answer (with dampening): " << ans << std::endl;
}

int main() {
    std::vector<std::vector<int>> levels;
    read_file(levels);
    evaluate(levels);
    evaluate2(levels);
    return 0;
}


