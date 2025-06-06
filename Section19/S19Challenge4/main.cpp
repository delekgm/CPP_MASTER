#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

bool isBlank(const std::string &line) {
    for (char c : line) {
        if (!std::isspace(c)) {
            return false;
        }
    }
    return true;
}

int main(){
    std::ifstream in_file;
    std::ofstream out_file;

    in_file.open("romeoandjuliet.txt");
    out_file.open("romeoandjuliet_out.txt");

    if(!in_file){
        std::cerr << "Problem opening in file" << std::endl;
        return 1;
    }

    if(!out_file){
        std::cerr << "Problem opening out file" << std::endl;
        return 1;
    }

    std::string line{};
    int line_number{0};

    while(getline(in_file, line)){
        std::cout << line << std::endl;
        if(isBlank(line)){
            out_file << std::endl;
            std::cout << "Ajjjjj" << std::endl;
        } else {
            ++line_number;
            out_file << std::setw(7) << std::left << line_number << line << std::endl;
        }
    }

    std::cout << "Copy Complete" << std::endl;

    in_file.close();
    out_file.close();
    return 0;
}
