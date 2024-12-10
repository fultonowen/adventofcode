#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

void read_file(std::vector<std::string>& xs) {
    std::ifstream ifs;
    ifs.open("input.txt");
    std::string line;
    if (ifs.is_open()) {
        while (getline(ifs, line)) {
            xs.push_back(line);
        }
        ifs.close();
    } else std::cout << "Unable to open file" << std::endl;
}

auto build_map(std::vector<std::string>& board) {
    std::unordered_map<char, std::vector<std::pair<int, int>>> nodes;
    int m = board.size(), n = board[0].length();
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] != '.')  nodes[board[i][j]].emplace_back(i, j);
        }
    }
    return nodes;
}

std::pair<int, int> left_node(const std::pair<int, int>& lhs, const std::pair<int, int>& rhs) {
    int dr = lhs.first - rhs.first;
    int dc = lhs.second - rhs.second;
    return { lhs.first + dr, lhs.second + dc };
}

std::pair<int, int> right_node(const std::pair<int, int>& lhs, const std::pair<int, int>& rhs) {
    int dr = rhs.first - lhs.first;
    int dc = rhs.second - lhs.second;
    return { rhs.first + dr, rhs.second + dc };
}
bool is_valid_location(int x, int y, int m, int n) {
    return x >= 0 && x < m && y >=0 && y < n;
}

// Part 1:
void evaluate1(std::vector<std::string>& board) {
    int ans = 0;
    int m = board.size(), n = board[0].size();
    std::vector<std::vector<bool>> seen(m, std::vector<bool>(n, false));
    auto frequencies = build_map(board);
    for (auto [key, node_locations] : frequencies) {
        int nodes_s = node_locations.size();
        for (int i = 0; i < nodes_s-1; i++) {
            for (int j = i+1; j < nodes_s; j++) {
                auto [left_r, left_c] = left_node(node_locations[i], node_locations[j]);
                auto [right_r, right_c] = right_node(node_locations[i], node_locations[j]);
                if (is_valid_location(left_r, left_c, m, n) && !seen[left_r][left_c]) {
                    seen[left_r][left_c] = true;
                    ans++;
                }
                if (is_valid_location(right_r, right_c, m, n) && !seen[right_r][right_c]) {
                    seen[right_r][right_c] = true;
                    ans++;
                }
            }
        }
    }
    std::cout << "Answer: " << ans << std::endl;
}
// Part 2:
std::pair<int, int> left_change(const std::pair<int, int>& lhs, const std::pair<int, int>& rhs) {
    int dr = lhs.first - rhs.first;
    int dc = lhs.second - rhs.second;
    return { dr, dc };
}

std::pair<int, int> right_change(const std::pair<int, int>& lhs, const std::pair<int, int>& rhs) {
    int dr = rhs.first - lhs.first;
    int dc = rhs.second - lhs.second;
    return { dr, dc };
}

void evaluate2(std::vector<std::string>& board) {
    int ans = 0;
    int m = board.size(), n = board[0].size();
    std::vector<std::vector<bool>> seen(m, std::vector<bool>(n, false));
    auto frequencies = build_map(board);
    for (auto [key, node_locations] : frequencies) {
        int nodes_s = node_locations.size();
        for (int i = 0; i < nodes_s-1; i++) {
            for (int j = i+1; j < nodes_s; j++) {
                auto [left_dr, left_dc] = left_change(node_locations[i], node_locations[j]);
                auto [right_dr, right_dc] = right_change(node_locations[i], node_locations[j]);
                auto [left_x, left_y] = node_locations[i];
                do {
                    ans += !seen[left_x][left_y] ? 1 : 0;
                    seen[left_x][left_y] = true;
                    left_x += left_dr;
                    left_y += left_dc;
                } while (is_valid_location(left_x, left_y, m, n));

                auto [right_x, right_y] = node_locations[j];
                do {
                    ans += !seen[right_x][right_y] ? 1 : 0;
                    seen[right_x][right_y] = true;
                    right_x += right_dr;
                    right_y += right_dc;
                } while (is_valid_location(right_x, right_y, m, n));

            }
        }
    }
    std::cout << "Answer: " << ans << std::endl;
}

int main() {
    std::vector<std::string> grid;
    read_file(grid);
    evaluate1(grid);
    evaluate2(grid);
    return 0;
}


