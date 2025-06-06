#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <set>

std::pair<std::vector<std::vector<std::string>>, std::vector<std::vector<std::string>>> parse_input(const std::string path) {
    // Open the input file
    std::ifstream file(path);
    std::vector<std::vector<std::string>> locks;
    std::vector<std::vector<std::string>> keys;

    if(!file.is_open()) {
        throw std::runtime_error("Unable to open input.txt");
    }

    std::vector<std::string> currentGrid;
    std::string line;

    // Process the file line by line
    while (std::getline(file, line)) {
        if (line.empty()) {
            // End of grid, classify it
            if(!currentGrid.empty()) {
                if(currentGrid[0][0] == '#') {
                    locks.push_back(std::vector<std::string>(currentGrid.begin() + 1, currentGrid.end()));
                } else if (currentGrid.back()[0] == '#') {
                    keys.push_back(std::vector<std::string>(currentGrid.begin(), currentGrid.end() - 1));
                }
                currentGrid.clear();
            }
        } else {
            // Accumlate lines into the current grid
            currentGrid.push_back(line);
        }
    }

    // Handle the last grid (if any)
    if (!currentGrid.empty()) {
        if(currentGrid[0][0] == '#') {
            locks.push_back(std::vector<std::string>(currentGrid.begin() + 1, currentGrid.end()));
        } else if (currentGrid.back()[0] == '#') {
            keys.push_back(std::vector<std::string>(currentGrid.begin(), currentGrid.end() - 1));
        }
        currentGrid.clear();
    }

    file.close();
    return {locks, keys};
}

std::vector<std::vector<int>> get_counts(const std::vector<std::vector<std::string>>& pieces) {
    std::vector<std::vector<int>> piece_counts;

    for(auto piece : pieces) {
        std::vector<int> piece_count;

        for(size_t c = 0; c < piece[0].size(); ++c) {
            int count = 0;
            for(size_t r = 0; r < piece.size(); ++r) {
                if(piece[r][c] == '#') count++;
            }
            piece_count.push_back(count);
        }
        piece_counts.push_back(piece_count);
    }
    return piece_counts;
}

int main() {
    try {
        const std::string path = "./input.txt";
        auto [locks, keys] = parse_input(path);

        // Print locks and keys for verification
        // std::cout << "Locks:\n";
        // for(const auto& lock : locks) {
        //     for(const auto& row : lock) {
        //         std::cout << row << '\n';
        //     }
        //     std::cout << '\n';
        // }

        // std::cout << "Keys:\n";
        // for(const auto& key : keys) {
        //     for(const auto& row : key) {
        //         std::cout << row << '\n';
        //     }
        //     std::cout << '\n';
        // }

        std::vector<std::vector<int>> lock_counts = get_counts(locks);
        std::vector<std::vector<int>> key_counts = get_counts(keys);

        //Print locks and keys for verification
        // std::cout << "Locks:\n";
        // for(const auto& lock_count : lock_counts) {
        //     for(const auto& row : lock_count) {
        //         std::cout << row << '\n';
        //     }
        //     std::cout << '\n';
        // }

        // std::cout << "Keys:\n";
        // for(const auto& key_count : key_counts) {
        //     for(const auto& row : key_count) {
        //         std::cout << row << '\n';
        //     }
        //     std::cout << '\n';
        // }

        std::set<std::pair<std::vector<int>, std::vector<int>>> combos;

        for(const auto& key_count : key_counts) {
            for(const auto& lock_count : lock_counts) {
                bool fits = true;
                for(size_t i = 0; i < 5; ++i) {
                    if(key_count[i] + lock_count[i] > 5) {
                        fits = false;
                        break;
                    }
                }
                if (fits) {
                    combos.insert({key_count, lock_count});
                }
            }
        }

        std::cout << combos.size() << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}