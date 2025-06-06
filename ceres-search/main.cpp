#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

int ceres_search_part_one(const std::vector<std::string> &grid) {
    long count {0};
    for(size_t r = 0; r < grid.size(); ++r) {
        for(size_t c = 0; c < grid[0].size(); ++c) {
            if(grid[r][c] != 'X') {
                continue;
            }

            int arr[8][2] = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};
            for(size_t i = 0; i < 8; ++i) {
                int *dirs = arr[i];
                int *dr = dirs;
                int *dc = dirs + 1;

                if(!(0 <= r + 3 * (*dr) < grid.size() && 0 <= c + 3 * (*dc) < grid[0].size())) {
                    continue;
                }

                if(grid[r + (*dr)][c + (*dc)] == 'M' && grid[r + 2 * (*dr)][c + 2 * (*dc)] == 'A' && grid[r + 3 * (*dr)][c + 3 * (*dc)] == 'S') ++count;
            }

        }
    }
    return count;
}

int ceres_search_part_two(const std::vector<std::string> &grid) {
    long count {0};
    for(size_t r = 1; r < grid.size() - 1; ++r) {
        for(size_t c = 1; c < grid[0].size() - 1; ++c) {
            if(grid[r][c] != 'A') {
                continue;
            }

            std::vector<char> corners = { grid[r - 1][ c - 1], grid[r - 1][c + 1], grid[r + 1][c + 1], grid[r + 1][c - 1] };
            // std::cout << corners[1];
            if (corners[0] == 'M' && corners[2] == 'S' && corners[1] == 'M' && corners[3] == 'S') {
                count++;
                continue;
            }


            if (corners[0] == 'S' && corners[2] == 'M' && corners[1] == 'S' && corners[3] == 'M') {
                count++;
                continue;
            }

            if (corners[0] == 'S' && corners[2] == 'M' && corners[1] == 'M' && corners[3] == 'S') {
                count++;
                continue;
            }

            if (corners[0] == 'M' && corners[2] == 'S' && corners[1] == 'S' && corners[3] == 'M') {
                count++;
                continue;
            }
        }
    }
    return count;
}

int main() {
    std::fstream input;
    input.open("input.txt");
    if(!input) {
        std::cerr << "Problem opening file" << std::endl;
        return 1;
    }

    std::string line;
    std::vector<std::string> all_lines;

    while(std::getline(input, line)) {
        all_lines.push_back(line);
    }

    // for (const auto& vec : all_lines) {
    //     std::cout << vec << "\n";
    // }

    input.close();

    std::cout << ceres_search_part_one(all_lines) << std::endl;
    std::cout << ceres_search_part_two(all_lines) << std::endl;
    return 0;
}

/*
def parse_input():
    with open('./input.txt', 'r') as file:
        return file.read().splitlines()

def cere_search_part_two(grid):
    count = 0
    for r in range(1, len(grid) - 1):
        for c in range(1, len(grid[0]) - 1):
            if grid[r][c] != "A":
                continue
            corners = [grid[r - 1][ c - 1], grid[r - 1][c + 1], grid[r + 1][c + 1], grid[r + 1][c - 1]]
            if corners[0] == 'M' and corners[2] == 'S' and corners[1] == 'M' and corners[3] == 'S':
                count += 1
                continue
            if corners[0] == 'S' and corners[2] == 'M' and corners[1] == 'S' and corners[3] == 'M':
                count += 1
                continue
            if corners[0] == 'S' and corners[2] == 'M' and corners[1] == 'M' and corners[3] == 'S':
                count += 1
                continue
            if corners[0] == 'M' and corners[2] == 'S' and corners[1] == 'S' and corners[3] == 'M':
                count += 1
                continue
    return count

def driver():
    grid = parse_input()
    print(cere_search_part_one(grid))
    print(cere_search_part_two(grid))

if __name__ == "__main__":
    driver()

# python3 -m venv venv
# Activate venv -> source venv/bin/activate
# Deactivate venv -> deactivate
*/