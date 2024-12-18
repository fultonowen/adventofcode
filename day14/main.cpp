#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <thread>
#include <queue>

static int SECONDS = 100, MAX_SECONDS = 1000000;
static int ROWS = 103, COLS = 101;

template <typename T>
void print_iterable(T& xs) {
    std::cout << "[";
    for (int i = 0; i < xs.size(); i++) {
        std::cout << xs[i];
    }
    std::cout << "]" << std::endl;
}

template <typename T>
void print_vec(T& xs) {
    std::for_each(xs.begin(), xs.end(), print_iterable<typename T::value_type>);
}

void read_file(std::vector<std::vector<int>>& xs) {
    std::ifstream ifs;
    ifs.open("input.txt");
    std::string line;
    if (ifs.is_open()) {
        while (getline(ifs, line)) {
            std::stringstream iss(line);
            iss.ignore(2);
            int start_c, start_r, v_c, v_r;
            iss >> start_c;
            iss.ignore(1);
            iss >> start_r;
            iss.ignore(3);
            iss >> v_c;
            iss.ignore(1);
            iss >> v_r;
            std::vector<int> row{start_r, start_c, v_r, v_c};
            xs.push_back(row);
        }
        ifs.close();
    } else std::cout << "Unable to open file" << std::endl;
}

int find_quad_at_100_seconds(std::vector<int>& bot) {
    // start row, start col, v_r, v_c
    int final_row = (ROWS + ((bot[0] + bot[2] * SECONDS) % ROWS)) % ROWS;
    int final_col = (COLS + ((bot[1] + bot[3] * SECONDS) % COLS)) % COLS;
    int half_rows = ROWS / 2;
    int half_cols = COLS / 2;
    if (final_row < half_rows && final_col < half_cols) return 0;
    else if (final_row < half_rows && final_col > half_cols) return 1;
    else if (final_row > half_rows && final_col < half_cols) return 2;
    else if (final_row > half_rows && final_col > half_cols) return 3;
    else return 4;
}

// Part 1:
void evaluate1(std::vector<std::vector<int>>& bots) {
    int quadrant[5] = {0, 0, 0, 0, 0};
    for (auto& bot : bots) {
        quadrant[find_quad_at_100_seconds(bot)]++;
    }
    uint64_t ans = quadrant[0] * quadrant[1] * quadrant[2] * quadrant[3];
    std::cout << "Answer: " << ans << std::endl;
}


//Part2:
std::pair<int, int> move(std::vector<int>& bot, int s) {
    // start row, start col, v_r, v_c
    int curr_row = (ROWS + ((bot[0] + bot[2] * s) % ROWS)) % ROWS;
    int curr_col = (COLS + ((bot[1] + bot[3] * s) % COLS)) % COLS;
    return {curr_row, curr_col};
}

bool is_valid(int x, int y) {
    return x >= 0 && x < ROWS && y < COLS && y >=0;
}

int find_area(std::vector<std::vector<char>>& input, std::vector<std::vector<bool>>& seen, int r, int c) {
    int dir[5] = {-1, 0, 1, 0, -1};
    int area = 0;
    std::queue<std::pair<int, int>> bfs_q;
    seen[r][c] = true;
    bfs_q.emplace(r, c);
    while (!bfs_q.empty()) {
        auto [row, col] = bfs_q.front();
        bfs_q.pop();
        area++;
        for (int i = 0; i < 4; i++) {
            int change_r = row + dir[i], change_c = col + dir[i+1];
            if (is_valid(change_r, change_c) && input[row][col] == input[change_r][change_c]) {
                if (!seen[change_r][change_c]) {
                    bfs_q.emplace(change_r, change_c);
                    seen[change_r][change_c] = true;
                }
            }
        }
    }
    return area;
}

int find_max_area(std::vector<std::vector<char>>& grid) {
    int max_area = 0;
    std::vector<std::vector<bool>> seen(ROWS, std::vector<bool>(COLS, false));
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (grid[i][j] == '.') continue;
            max_area = std::max(max_area, find_area(grid, seen, i, j));
        }
    }
    return max_area;
}

void paint(std::vector<std::vector<int>>& bots) {
    std::vector<std::vector<char>> grid(ROWS, std::vector<char>(COLS, '.'));

    for (int sec = 0; sec < MAX_SECONDS; sec++) {
        for (auto &bot: bots) {
            auto [active_row, active_col] = move(bot, sec);
            grid[active_row][active_col] = '#';
        }

        if (find_max_area(grid) >= 50) {
            std::cout << "Second value: " << sec << std::endl;
            print_vec(grid);
            std::this_thread::sleep_for(std::chrono::seconds(5));
        }

        for (auto &bot_item: bots) {
            auto [curr_row, curr_col] = move(bot_item, sec);
            grid[curr_row][curr_col] = '.';
        }
    }
}

void evaluate2(std::vector<std::vector<int>>& bots) {
    uint64_t ans = 0;
    paint(bots);
    std::cout << "Answer: " << ans << std::endl;
}

int main() {
    std::vector<std::vector<int>> input;
    read_file(input);
    evaluate1(input);
    evaluate2(input);
    return 0;
}


