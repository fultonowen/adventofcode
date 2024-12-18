#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>

std::pair<int64_t, int64_t> find_between(std::string& s, char first, char second) {
    int x_idx = s.find(first), x_idx_2 = s.find(second);
    int y_idx = s.find(first, x_idx_2);
    int64_t dx = std::stoi(s.substr(x_idx+1, x_idx_2-(x_idx+1)));
    int64_t dy = std::stoi(s.substr(y_idx+1, s.length()-(y_idx+1)));
    return {dx, dy};
}

void read_file(std::vector<std::vector<std::pair<int64_t, int64_t>>>& input) {
    std::ifstream ifs;
    ifs.open("input.txt");
    std::string line;
    if (ifs.is_open()) {
        while (getline(ifs, line)) {
            std::vector<std::pair<int64_t, int64_t>> entry;
            auto p1 = find_between(line, '+', ','); entry.push_back(p1);
            getline(ifs, line);
            auto p2 = find_between(line, '+', ','); entry.push_back(p2);
            getline(ifs, line);
            auto goal = find_between(line, '=', ','); entry.push_back(goal);
            getline(ifs, line);
            input.push_back(entry);
        }
        ifs.close();
    } else std::cout << "Unable to open file" << std::endl;
}

int64_t min_cost(std::vector<std::pair<int64_t, int64_t>>& game) {
    int64_t min_cost = INT64_MAX;
    int64_t goal_x = game[2].first;
    int64_t goal_y = game[2].second;
    for (int A_press = 0; A_press <= 100; A_press++) {
        for (int B_press = 0; B_press <= 100; B_press++) {
            int64_t x = A_press * game[0].first + B_press * game[1].first;
            int64_t y = A_press * game[0].second + B_press * game[1].second;
            if (x == goal_x && y == goal_y) {
                int64_t cost = 3 * A_press + B_press;
                min_cost = std::min(min_cost, cost);
            }
        }
    }
    return min_cost;

}




//Part 2:
int64_t cost_solve(std::vector<std::pair<int64_t, int64_t>>& game) {
    int64_t shift = 10000000000000;
    int64_t B[2] = {game[1].first, game[1].second};
    int64_t A[2] = {game[0].first, game[0].second};
    int64_t P[2] = {game[2].first + shift, game[2].second + shift};
    const auto det = B[0] * A[1] - B[1] * A[0];
    if (det == 0) return INT64_MAX;
    auto p = P[0] * A[1] - P[1] * A[0];
    if (p % det != 0)
        return INT64_MAX;
    const auto b = p / det;
    p = P[0] - B[0] * b;
    if (p % A[0] != 0)
        return INT64_MAX;
    const auto a = p / A[0];
    return 3 * a + b;
}

// Part 1:
void evaluate1(std::vector<std::vector<std::pair<int64_t, int64_t>>>& xs) {
    int64_t ans = 0;
    for (auto& game : xs) {
        int64_t cost = min_cost(game);
        ans += cost != INT64_MAX ? cost : 0;
    }
    std::cout << "Answer: " << ans << std::endl;
}

void evaluate2(std::vector<std::vector<std::pair<int64_t, int64_t>>>& xs) {
    int64_t ans = 0;
    for (auto &game: xs) {
        int64_t cost = cost_solve(game);
        ans += cost != INT64_MAX ? cost : 0;
    }
    std::cout << "Answer: " << ans << std::endl;
}


int main() {
    std::vector<std::vector<std::pair<int64_t, int64_t>>> input;
    read_file(input);
    evaluate1(input);
    evaluate2(input);
    return 0;
}


