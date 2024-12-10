#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void read_file(std::string& xs) {
    std::ifstream ifs;
    ifs.open("input.txt");
    std::string line;
    if (ifs.is_open()) {
        while (getline(ifs, line)) {
            xs = line;
        }
        ifs.close();
    } else std::cout << "Unable to open file" << std::endl;
}

struct Block {
    int file_id;
    Block(int fid) : file_id(fid) {};
    int get_id() const { return file_id; }
};

struct Space {
    int idx;
    int size;
    Space(int _idx, int _size) : idx(_idx), size(_size) {};
};

std::vector<Block> to_blocks(std::string& input) {
    std::vector<Block> res;
    int f_id = 0;
    for (int i = 0; i < input.length(); i++) {
        if (i % 2 == 0) {
            int size = input[i] - '0';
            for (int j = 0; j < size; j++) {
                res.emplace_back(f_id);
            }
            f_id++;
        } else {
            int size = input[i] - '0';

            for (int j = 0; j < size; j++) res.emplace_back(-1);
        }
    }
    return res;
}

std::vector<Space> to_spaces(std::string& input) {
    std::vector<Space> res;
    int idx = 0;
    for (int i = 0; i < input.length(); i++) {
        int size = input[i] - '0';
        if (i % 2 == 1) {
            res.emplace_back(idx, size);
        }
        idx += size;
    }
    return res;
}

uint64_t checksum(std::vector<Block>& board) {
    uint64_t res = 0;
    for (int i = 0; i < board.size(); i++) {
        std::cout << board[i].get_id() << std::endl;
        if (board[i].get_id() == -1) continue;
        res += i * board[i].get_id();
    }
    return res;
}
/*
 * The digits alternate between indicating the length of a file and the length of free space.
 */

// Part 1:
void evaluate1(std::vector<Block> board) {
    int free_block = 0, right = board.size() -1;
    while (board[right].get_id() == -1) {
        right--;
    }
    while (free_block < right) {
        if (board[free_block].get_id() != -1) {
            free_block++;
        } else if (board[right].get_id() == -1) {
            right--;
        } else {
            std::swap(board[free_block++], board[right--]);
        }
    }
    uint64_t ans = checksum(board);
    std::cout << "Answer: " << ans << std::endl;
}


int scan_space_fit(std::vector<Space>& spaces, int k, int right_ptr) {
    for (int i = 0; i < spaces.size(); i++ ){
        if (spaces[i].size >= k && spaces[i].idx < right_ptr) {
            spaces[i].size -= k;
            int temp = spaces[i].idx;
            spaces[i].idx += k;
            return temp;
        }
    }
    return -1;
}

int find_file_size(std::vector<Block>& xs, int& right_ptr) {
    int prev_id = xs[right_ptr].get_id();
    int size = 0;
    while (prev_id == xs[right_ptr].get_id()) {
        prev_id = xs[right_ptr--].get_id();
        size++;
    }
    return size;
}

void swap_blocks(std::vector<Block>& xs, int left_ptr, int right_ptr, int size) {
    for (int i = 0; i < size; i++) {
        std::swap(xs[left_ptr++], xs[right_ptr++]);
    }
}


//Part2:
void evaluate2(std::vector<Block> board, std::vector<Space>& spaces) {
    int free_block = 0, right = board.size() -1;
    while (board[right].get_id() == -1) {
        right--;
    }
    while (0 <= right) {
        if (board[right].get_id() == -1) {
            right--;
        } else {
            int right_size = find_file_size(board, right);
            int left_swap_idx = scan_space_fit(spaces, right_size, right);
            std::cout << "File size: " << right_size << "left_swap_idx: " << left_swap_idx << std::endl;
            if (left_swap_idx != -1)
                swap_blocks(board, left_swap_idx, right+1, right_size);
        }
    }
    uint64_t ans = checksum(board);
    std::cout << "Answer: " << ans << std::endl;
}

int main() {
    std::string input;
    read_file(input);
    std::vector<Block> files = to_blocks(input);
    std::vector<Space> spaces = to_spaces(input);

    evaluate1(files);
    evaluate2(files, spaces);
    return 0;
}


