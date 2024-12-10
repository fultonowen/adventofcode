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



bool is_valid_move(int to_row, int to_col, int m, int n) {
    return to_row >=0 && to_row < m && to_col >=0 && to_col < n;
}

// Part 1:
void evaluate1(std::vector<std::string>& board) {
    int ans = 0;
    std::cout << "Answer: " << ans << std::endl;
}

//Part2:
void evaluate2(std::vector<std::string>& board) {
    int ans =0;
    std::cout << "Answer: " << ans << std::endl;
}

int main() {
    std::vector<std::string> grid;
    read_file(grid);
    evaluate1(grid,);
    evaluate2(grid, seen);
    return 0;
}


