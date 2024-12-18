#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <algorithm>
#include <set>

void read_file(std::vector<std::string>& input) {
    std::ifstream ifs;
    ifs.open("input.txt");
    std::string line;
    if (ifs.is_open()) {
        while (getline(ifs, line)) {
            input.push_back(line);
        }
        ifs.close();
    } else std::cout << "Unable to open file" << std::endl;
}

bool is_valid(int x, int y, int m, int n) {
    return x >= 0 && x < m && y < n && y >=0;
}

struct Path {
    uint64_t curr_cost;
    int row;
    int col;
    int direction;
    std::vector<int> path;
    Path(uint64_t _cost, int _row, int _col, int _direction, std::vector<int> path)
        : curr_cost(_cost), row(_row), col(_col), direction(_direction), path(path) {}
};

struct PathComparator {
    bool operator() (const Path& lhs, const Path& other) {
        return lhs.curr_cost > other.curr_cost;
    }
};

int hash_r_c(int r, int c, int m) {
    return r * m + c;
}

// Part 1:
void min_cost(std::vector<std::string>& input, int r, int c, int end_r, int end_c) {
    int m = input.size(), n = input[0].length();
    std::vector<std::vector<std::vector<uint64_t>>>
        min_cost_cell(m,
                      std::vector<std::vector<uint64_t>>(n, std::vector<uint64_t>(4, UINT64_MAX)));
    int dir[5] = {-1, 0, 1, 0, -1}; // N, E, S, W

    std::priority_queue<Path, std::vector<Path>, PathComparator> min_q;
    min_cost_cell[r][c][1] = 0;
    std::vector<int> first_path{hash_r_c(r, c, m)};
    std::set<int> best_paths;
    min_q.emplace(0, r, c, 1, first_path);
    while (!min_q.empty()) {
        auto node = min_q.top();
        min_q.pop();
        if (node.row == end_r && node.col == end_c) {
            for (auto& hash_entry : node.path) {
                best_paths.insert(hash_entry);
            }
        }
        if (min_cost_cell[node.row][node.col][node.direction] < node.curr_cost) continue;

        for (int rotation = -1; rotation < 2; rotation++) {
            int i = (4 + (node.direction + rotation)) % 4;
            int change_r = node.row + dir[i], change_c = node.col + dir[i+1];
            if (is_valid(change_r, change_c, m, n) && input[change_r][change_c] != '#') {
                uint64_t cost_move = (rotation == 0) ? 1 : 1001;
                if (node.curr_cost + cost_move <= min_cost_cell[change_r][change_c][i]) {
                    auto path = node.path;
                    path.push_back(hash_r_c(change_r, change_c, m));
                    min_q.emplace(node.curr_cost + cost_move, change_r, change_c, i, path);
                    min_cost_cell[change_r][change_c][i] = node.curr_cost + cost_move;
                }
            }
        }
    }
    std::cout << "Answer (1): " << *std::min_element(min_cost_cell[end_r][end_c].begin(), min_cost_cell[end_r][end_c].end()) << std::endl;
    std::cout << "Answer (2): " << best_paths.size() << std::endl;
}

void evaluate1_and_2(std::vector<std::string>& xs) {
    int m = xs.size(), n = xs[0].size();
    int end_r = -1, end_c = -1;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (xs[i][j] == 'E') {
                end_r = i; end_c = j;
            }
            if (xs[i][j] != 'S') continue;

            min_cost(xs, i, j, end_r, end_c);
        }
    }
}

template <typename T>
void print_iterable(const T& xs) {
    std::cout << "[";
    for (int i = 0; i < xs.size(); i++) {
        if (i == xs.size() -1) std::cout << xs[i];
        else std::cout << xs[i] << ", ";
    }
    std::cout << "]" << std::endl;
}

template <typename T>
void print_vec(const T& xs) {
    std::for_each(xs.cbegin(), xs.cend(), print_iterable<typename T::value_type>);
}

int main() {
    std::vector<std::string> input;
    read_file(input);
    evaluate1_and_2(input);
    return 0;
}


