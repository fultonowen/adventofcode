#include <iostream>
#include <fstream>
#include <string>


void read_file(std::vector<unsigned long long>& input) {
    std::ifstream ifs;
    ifs.open("input.txt");
    std::string line;
    if (ifs.is_open()) {
        while (getline(ifs, line, ' ')) {
            input.push_back(std::stoull(line));
        }
        ifs.close();
    } else std::cout << "Unable to open file" << std::endl;
}

// Part 1:
std::unordered_map<unsigned long long, unsigned long long> blink(std::unordered_map<unsigned long long, unsigned long long>& stones) {
    std::unordered_map<unsigned long long, unsigned long long> next;
    for (auto& [stone, freq] : stones) {
        std::string s = std::to_string(stone);
        if (stone == 0) {
            next[1ULL] += freq;
        } else if (s.length() % 2 == 0) {
            int split_idx = s.length() / 2;
            std::string first = s.substr(0, split_idx);
            std::string second = s.substr(split_idx, split_idx);

            next[std::stoull(first)] += freq;
            next[std::stoull(second)] += freq;
        } else {
            next[stone*2024ULL] += freq;
        }
    }
    return next;
}
unsigned long long evaluate(std::vector<unsigned long long>& xs, int blinks) {
    std::unordered_map<unsigned long long, unsigned long long> stones;
    for (unsigned long long x : xs) {
        stones[x]++;
    }
    for (int i = 0; i < blinks; i++) {
        stones = std::move(blink(stones));
    }
    unsigned long long ans = 0;
    for (auto& [stone, freq] : stones) {
        ans += freq;
    }
    return ans;
}

void evaluate1(std::vector<unsigned long long>& xs) {
    unsigned long long ans = evaluate(xs, 25);
    std::cout << "Answer: " << ans << std::endl;
}

//Part2:
void evaluate2(std::vector<unsigned long long>& xs) {
    unsigned long long ans = evaluate(xs, 75);
    std::cout << "Answer: " << ans << std::endl;
}


int main() {
    std::vector<unsigned long long> input;
    read_file(input);
    evaluate1(input);
    evaluate2(input);
    return 0;
}


