#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

bool safe(const std::vector<int> &level_set) {

    std::vector<int> diffs;

    // Calculate the differences
    for (size_t i = 0; i < level_set.size() - 1; ++i) {
        diffs.push_back(level_set[i] - level_set[i + 1]);
    }

    // Check if all differences are between 1 and 3
    bool condition1 = true;
    for (int x : diffs) {
        if (x < 1 || x > 3) {
            condition1 = false;
            break;
        }
    }

    // Check if all differences are between -1 and -3
    bool condition2 = true;
    for (int x : diffs) {
        if (x > -1 || x < -3) {
            condition2 = false;
            break;
        }
    }

    return condition1 || condition2;
}

int red_nosed_one(std::vector<std::vector<int>> &reports) {
    long count {0};
    for(const auto &level_set : reports) {
        if(safe(level_set)) {
            count++;
        }
    }
    return count;
}

int red_nosed_two(const std::vector<std::vector<int>> &reports) {
    long count {0};

    for(const auto &level_set : reports) {
        bool found = false;

        for(size_t i = 0; i < level_set.size(); ++i) {
            std::vector<int> modified_level_set;
            modified_level_set.reserve(level_set.size() - 1);

            for(size_t j = 0; j < level_set.size(); ++j) {
                if(j != i) {
                    modified_level_set.push_back(level_set[j]);
                }
            }

            if(safe(modified_level_set)) {
                found = true;
                break;
            }
        }
        
        if(found) {
            ++count;
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
    std::vector<std::vector<int>> all_lines;

    while(std::getline(input, line)) {
        std::istringstream iss(line);
        std::vector<int> numbers;
        int num;

        while(iss >> num) {
            numbers.push_back(num);
        }

        all_lines.push_back(numbers);
    }

    // Print the vectors to verify
    for (const auto& vec : all_lines) {
        for (int n : vec) {
            std::cout << n << " ";
        }
        std::cout << "\n";
    }

    input.close();

    long part_one = red_nosed_one(all_lines);
    long part_two = red_nosed_two(all_lines);


    std::cout << part_one << std::endl;
    std::cout << part_two << std::endl;
    return 0;
}

/*
def parse_input():
    with open('./input.txt', 'r') as file:
        reports = file.readlines()
        reports = [list(map(int, report.split())) for report in reports]
        return reports

def safe(level_set):
    # zip pattern to get pairs of values
    diffs = [x - y for x, y in zip(level_set, level_set[1:])]
    return all(1 <= x <= 3 for x in diffs) or all(-1 >= x >= -3 for x in diffs)

def red_nosed_reports_one(reports):
    count = 0
    for level_set in reports:
        if safe(level_set):
            count += 1
    return count

def red_nosed_reports_two(reports):
    count = 0
    for level_set in reports:
        # Out of bounds results in empty list
        # At i = 0 the first element is removed
        # At i = length - 1 the last element is removed
        # A check on the full level set isn't needed because a safe list without the first or last element is still safe
        if any(safe(level_set[:i] + level_set[i + 1:]) for i in range(len(level_set))):
            count += 1
    return count

def driver():
    reports = parse_input()
    print(red_nosed_reports_one(reports))
    print(red_nosed_reports_two(reports))

if __name__ == "__main__":
    driver()

# python3 -m venv venv
# Activate venv -> source venv/bin/activate
# Deactivate venv -> deactivate*/