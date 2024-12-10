#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <vector>

void read_file(std::vector<std::vector<int>>& xs) {
    std::ifstream ifs;
    ifs.open("input.txt");
    std::string line;
    if (ifs.is_open()) {
        while (getline(ifs, line)) {
            std::vector<int> _xs;
            for (char& c : line) {
                int height = c - '0';
                _xs.push_back(height);
            }
            xs.push_back(_xs);
        }
        ifs.close();
    } else std::cout << "Unable to open file" << std::endl;
}

// helpers:
bool is_valid_move(int x, int y, int m, int n) {
    return x >=0 && x < m && y < n && y >=0;
}

// Part 1:
int count_full_paths(std::vector<std::vector<int>>& board, int start_r, int start_c) {
    int m = board.size(), n = board[0].size(), count = 0;
    const int dirs[5] = {-1, 0, 1, 0, -1};
    std::queue<std::pair<int, int>> bfs_queue;
    std::vector<std::vector<bool>> seen(m, std::vector<bool>(n, false));
    seen[start_r][start_c]=true;
    bfs_queue.emplace(start_r, start_c);
    while (!bfs_queue.empty()) {
        auto [r, c] = bfs_queue.front();
        bfs_queue.pop();
        if (board[r][c] == 9) {
            count++;
        }
        for (int i = 0; i < 4; i++) {
            int dx = r + dirs[i], dy = c + dirs[i+1];
            if (is_valid_move(dx, dy, m, n) && !seen[dx][dy] && board[r][c] + 1 == board[dx][dy]) {
                bfs_queue.emplace(dx, dy);
                seen[dx][dy] = true;
            }
        }
    }
    return count;
}

void evaluate1(std::vector<std::vector<int>>& board) {
    int ans = 0;
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[0].size(); j++) {
            if (board[i][j] != 0) continue;
            ans += count_full_paths(board, i, j);
        }
    }
    std::cout << "Answer: " << ans << std::endl;
}


//Part2:
int count_full_paths2(std::vector<std::vector<int>>& board, int start_r, int start_c) {
    int m = board.size(), n = board[0].size(), count = 0;
    const int dirs[5] = {-1, 0, 1, 0, -1};
    std::queue<std::pair<int, int>> bfs_queue;
    bfs_queue.emplace(start_r, start_c);
    while (!bfs_queue.empty()) {
        auto [r, c] = bfs_queue.front();
        bfs_queue.pop();
        if (board[r][c] == 9) {
            count++;
            continue;
        }
        for (int i = 0; i < 4; i++) {
            int dx = r + dirs[i], dy = c + dirs[i+1];
            if (is_valid_move(dx, dy, m, n) && board[r][c] + 1 == board[dx][dy]) {
                bfs_queue.emplace(dx, dy);
            }
        }
    }
    return count;
}
void evaluate2(std::vector<std::vector<int>>& board) {
    int ans = 0;
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[0].size(); j++) {
            if (board[i][j] != 0) continue;
            ans += count_full_paths2(board, i, j);
        }
    }
    std::cout << "Answer: " << ans << std::endl;
}

int main() {
    std::vector<std::vector<int>> input;
    read_file(input);
    evaluate1(input);
    evaluate2(input);
    return 0;
}


