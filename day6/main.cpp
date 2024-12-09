#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>

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

std::pair<int, int> find_start_pos(std::vector<std::string>& board) {
    int m = board.size(), n = board[0].length();
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] == '^') return {i, j};
        }
    }
    return {-1, -1};
}

const std::vector<std::pair<int, int>> directions{
        {-1, 0}, {0, 1}, {1, 0}, {0, -1}
};

bool is_valid_move(int to_row, int to_col, int m, int n) {
    return to_row >=0 && to_row < m && to_col >=0 && to_col < n;
}

// Part 1:
bool update(std::vector<std::string>& board, int& r, int& c, int& d) {
    int to_r = r + directions[d%4].first;
    int to_c = c + directions[d%4].second;
    if (is_valid_move(to_r, to_c, board.size(), board[0].size())) {
        if (board[to_r][to_c] != '#') {
            r = to_r;
            c = to_c;
        } else d++;
        return true;
    }
    return false;
}

void move_all(std::vector<std::string>& board, std::set<std::pair<int, int>>& found, int curr_row, int curr_col) {
    board[curr_row][curr_col] = '.';
    int direction = 0;
    int to_row = curr_row, to_col = curr_col;
    found.emplace(curr_row, curr_col);
    while (update(board, to_row, to_col, direction)) {
        found.emplace(to_row, to_col);
    }
    board[curr_row][curr_col] = '^';

}

void evaluate1(std::vector<std::string>& board, std::set<std::pair<int, int>>& seen) {
    auto [s_row, s_col] = find_start_pos(board);
    move_all(board, seen, s_row, s_col);
    std::cout << "Answer: " << seen.size() << std::endl;
}

//Part2:
int move_all2(std::vector<std::string>& board, std::set<std::pair<int, int>>& seen) {
    int m = board.size(), n = board[0].size(), g = 4;
    auto [s_row, s_col] = find_start_pos(board);
    int obstructions = 0;
    seen.erase({s_row, s_col});
    for (auto& obs : seen) {
        int start_r = s_row, start_c = s_col, direction = 0;
        board[obs.first][obs.second] = '#';
        std::vector<std::vector<std::vector<bool>>> path_state(m,
                                                               std::vector<std::vector<bool>>(n, std::vector<bool>(g, false)));
        while (update(board, start_r, start_c, direction)) {
            if (path_state[start_r][start_c][direction % 4]) {
                obstructions++;
                break;
            }
            path_state[start_r][start_c][direction % 4] = true;

        }
        board[obs.first][obs.second] = '.';

    }
    return obstructions;
}

void evaluate2(std::vector<std::string>& board, std::set<std::pair<int, int>>& seen) {
    int ans = move_all2(board, seen);
    std::cout << "Answer: " << ans << std::endl;
}

int main() {
    std::vector<std::string> grid;
    std::set<std::pair<int, int>> seen;
    read_file(grid);
    evaluate1(grid, seen);
    evaluate2(grid, seen);
    return 0;
}


