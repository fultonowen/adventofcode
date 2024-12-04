#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>

void read_file(std::vector<int>& list1, std::vector<int>& list2) {
    std::ifstream ifs;
    ifs.open("input.txt");
    std::string line;
    if (ifs.is_open()) {
        while (getline(ifs, line)) {
            std::stringstream ss(line);
            int f, s;
            ss >> f >> s;
            list1.push_back(f);
            list2.push_back(s);
        }
        ifs.close();
    } else std::cout << "Unable to open file" << std::endl;
}

void evaluate(std::vector<int>& list1, std::vector<int>& list2) {
    long long total_diff = 0;
    std::priority_queue<int, std::vector<int>, std::greater<>> pq1(list1.begin(), list1.end()), pq2(list2.begin(), list2.end());
    if (pq1.size() != pq2.size()) {
        std::cerr << "Error: Priority queues of diff sizes" << std::endl;
        return;
    }

    while (!pq1.empty() && !pq2.empty()) {
        total_diff += abs(pq1.top() - pq2.top());
        pq1.pop();
        pq2.pop();
    }

    std::cout << "Total Difference: " << total_diff << std::endl;
}

void evaluate2(std::vector<int>& list1, std::vector<int>& list2) {
    std::unordered_map<int, int> freq;
    for (int n : list2) freq[n]++;
    int sim_score = 0;

    for (int n : list1) {
        sim_score += n * freq[n];
    }

    std::cout << "Similarity score: " << sim_score << std::endl;
}

int main() {
    std::vector<int> first, second;
    read_file(first, second);
    evaluate(first, second);
    evaluate2(first, second);
    return 0;
}


