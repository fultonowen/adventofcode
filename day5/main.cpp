#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_set>
#include <algorithm>

template <typename T>
void print_vec(std::vector<T>& xs) {
    std::cout << "{ ";
    for (T val : xs) {
        std::cout << val << ", ";
    }
    std::cout << "}" << std::endl;
}

// Read input:
// map in order (blocked - blocked by)
void read_file(std::unordered_set<std::string>& order,
               std::vector<std::vector<int>>& updates) {
    std::ifstream ifs;
    ifs.open("input.txt");
    std::string line;
    if (ifs.is_open()) {
        while (getline(ifs, line)) {
            if (line.empty()) break;
            std::string first, second;
            first.push_back(line[0]); first.push_back(line[1]);
            second.push_back(line[3]); second.push_back(line[4]);
            int blocked_by = std::stoi(first), blocked = std::stoi(second);
            order.insert(line);
        }

        while (getline(ifs, line)) {
            std::vector<int> update;
            std::string sub_update;
            std::stringstream ss(line);
            while (getline(ss, sub_update, ',')) {
                update.push_back(std::stoi(sub_update));
            }
            updates.push_back(update);
        }
        ifs.close();
    } else std::cout << "Unable to open file" << std::endl;
}


bool is_valid_update(std::unordered_set<std::string>& ord, std::vector<int>& update) {
    auto compare = [&ord](const int& p1, const int& p2) {
        std::string f = std::to_string(p1) + "|" + std::to_string(p2);
        return ord.contains(f);
    };

    bool res = std::is_sorted(update.begin(), update.end(), compare);
    return std::is_sorted(update.begin(), update.end(), compare);
}


// Part 1:
void evaluate1(std::unordered_set<std::string>& order, std::vector<std::vector<int>>& updates) {
    int ans = 0;
    for (std::vector<int>& update: updates) {
        if (is_valid_update(order, update)) {
            int n = update.size();
            ans += update[n/2];
        }
    }
    std::cout << "Answer: " << ans << std::endl;
}

// Part 2:
int correct_invalid_input(std::unordered_set<std::string>& ord, std::vector<int>& update) {
    auto compare = [&ord](const int& p1, const int& p2) {
        std::string f = std::to_string(p1) + "|" + std::to_string(p2);
        return ord.contains(f);
    };
    bool res = std::is_sorted(update.begin(), update.end(), compare);
    if (!res) {
        std::sort(update.begin(), update.end(), compare);
        return update[update.size()/2];
    }
    return 0;


}

void evaluate2(std::unordered_set<std::string>& order, std::vector<std::vector<int>>& updates) {
    int ans = 0;
    for (std::vector<int>& update: updates) {
        ans += correct_invalid_input(order, update);
    }
    std::cout << "Answer: " << ans << std::endl;
}

int main() {
    std::unordered_set<std::string> in1;
    std::vector<std::vector<int>> in2;
    read_file(in1, in2);
    evaluate1(in1, in2);
    evaluate2(in1, in2);
    return 0;
}
