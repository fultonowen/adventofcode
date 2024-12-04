#include <iostream>
#include <fstream>
#include <vector>

template <typename T>
void print_vec(std::vector<T>& xs) {
    std::cout << "{ ";
    for (T val : xs) {
        std::cout << val << ", ";
    }
    std::cout << "}" << std::endl;
}
// Read input:
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

// Accessor for input within bounds
char get_char(std::vector<std::string>& in, int r, int c) {
    if (r >=0 && c >=0 && r < in.size() && c < in[0].size()) return in[r][c];
    return ' ';
}

// Part 1:
int scan_any_position(std::vector<std::string>& input, int row_start, int col_start, int dx, int dy) {
    int m = input.size(), n = input[0].length(), search_ptr = 0;
    std::string xmas = "XMAS";
    if (input[row_start][col_start] != 'X') return 0;
    while (row_start >=0 && col_start >=0 && row_start < m && col_start < n) {
        if (get_char(input, row_start, col_start) == xmas[search_ptr]) search_ptr++;
        else break;
        if (search_ptr == 4) return 1;
        row_start += dx;
        col_start += dy;

    }
    return 0;
}

int scan_all(std::vector<std::string>& input) {
    int res = 0, m = input.size(), n = input[0].length();
    std::vector<std::pair<int, int>> directions {
            {0, -1}, {0, 1},
            {1, 0}, {-1, 0},
            {1, -1}, {1, 1},
            {-1, -1}, {-1, 1}
    };
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            for (auto [dx, dy] : directions) res += scan_any_position(input, i, j, dx, dy);
        }
    }
    return res;
}

void evaluate1(std::vector<std::string>& input) {
    int ans = scan_all(input);

    std::cout << "Answer: " << ans << std::endl;
}

// Part 2:
int is_x_mas(std::vector<std::string>& input, int r, int c) {
    if (input[r][c] != 'A') return 0;
    char topleft = get_char(input, r-1, c-1), bottomright = get_char(input, r+1, c+1);
    char bottomleft = get_char(input, r+1, c-1), topright = get_char(input, r-1, c+1);
    std::string first_cross{topleft, bottomright}, second_cross{bottomleft, topright};
    return ((first_cross == "MS" || first_cross == "SM") && (second_cross == "MS" || second_cross == "SM")) ? 1 : 0;

}

void evaluate2(std::vector<std::string>& input) {
    int ans = 0, m = input.size(), n = input[0].length();
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            ans += is_x_mas(input, i, j);
        }
    }
    std::cout << "Answer: " << ans << std::endl;
}
int main() {
    std::vector<std::string> in;
    read_file(in);
    evaluate1(in);
    evaluate2(in);
    return 0;
}
