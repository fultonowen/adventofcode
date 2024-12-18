#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

// Read input:
void read_file(std::vector<std::pair<int, int>>& updates) {
    std::ifstream ifs;
    ifs.open("input.txt");
    std::string line;
    if (ifs.is_open()) {
        while (getline(ifs, line)) {
            int r_coord, c_coord;
            std::stringstream ss(line);
            ss >> c_coord;
            ss.ignore(1);
            ss >> r_coord;
            updates.emplace_back(r_coord, c_coord);
        }
        ifs.close();
    } else std::cout << "Unable to open file" << std::endl;
}

bool is_valid(int to_row, int to_col, int m, int n) {
    return to_row >=0 && to_row < m && to_col >=0 && to_col < n;
}

struct Path {
    uint64_t curr_cost;
    int row;
    int col;
    Path(uint64_t _cost, int _row, int _col)
            : curr_cost(_cost), row(_row), col(_col) {}
};

struct PathComparator {
    bool operator() (const Path& lhs, const Path& other) {
        return lhs.curr_cost > other.curr_cost;
    }
};

void simulate_n_bytes_falling(std::vector<std::vector<char>>&grid,
                              std::vector<std::pair<int, int>>&updates, int bytes) {
    for (int i = 0; i < bytes; i++) {
        auto [r, c] = updates[i];
        grid[r][c] = '#';
    }
};

// Djikstras Algorithm
uint64_t min_cost(std::vector<std::vector<char>>& input, int r, int c, int end_r, int end_c) {
    int m = input.size(), n = input[0].size();
    std::vector<std::vector<uint64_t>> min_cost_cell(m, std::vector<uint64_t>(n, UINT64_MAX));
    int dir[5] = {-1, 0, 1, 0, -1}; // N, E, S, W

    std::priority_queue<Path, std::vector<Path>, PathComparator> min_q;
    min_cost_cell[r][c] = 0;
    min_q.emplace(0, r, c);
    while (!min_q.empty()) {
        auto node = min_q.top();
        min_q.pop();
        if (min_cost_cell[node.row][node.col] < node.curr_cost) continue;
        for (int i = 0; i < 4; i++) {
            int change_r = node.row + dir[i], change_c = node.col + dir[i+1];
            if (is_valid(change_r, change_c, m, n) && input[change_r][change_c] != '#') {
                if (node.curr_cost + 1 < min_cost_cell[change_r][change_c]) {
                    min_q.emplace(node.curr_cost + 1, change_r, change_c);
                    min_cost_cell[change_r][change_c] = node.curr_cost + 1;
                }
            }
        }
    }
    return min_cost_cell[end_r][end_c];
}


// Part 1:
void evaluate1(std::vector<std::pair<int, int>>& updates) {
    int end_r = 70, end_c = 70;
    std::vector<std::vector<char>> grid(end_r+1, std::vector<char>(end_c+1, '.'));
    simulate_n_bytes_falling(grid, updates, 1024);
    uint64_t ans = min_cost(grid, 0, 0, end_r, end_c);
    std::cout << "Answer: " << ans << std::endl;
}

// Part 2:
void evaluate2(std::vector<std::pair<int, int>>& updates) {
    int end_r = 70, end_c = 70;
    std::vector<std::vector<char>> grid(end_r+1, std::vector<char>(end_c+1, '.'));
    auto add_one_byte = [&grid, &updates](int update_bit) {
        auto [r, c] = updates[update_bit];
        grid[r][c] = '#';
    };

    simulate_n_bytes_falling(grid, updates, 1024);

    for (int i = 1024; i < updates.size(); i++) {
        add_one_byte(i);
        if (min_cost(grid, 0, 0, end_r, end_c) == UINT64_MAX) {
            std::cout << "Answer: " << updates[i].second << "," << updates[i].first << std::endl;
            break;
        }
    }
}

int main() {
    std::vector<std::pair<int, int>> input;
    read_file(input);
    evaluate1(input);
    evaluate2(input);
    return 0;
}
