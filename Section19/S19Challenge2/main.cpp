#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>

int main(){
    std::ifstream in_file;
    in_file.open("responses.txt");
    if(!in_file){
        std::cerr << "Problem opening file" << std::endl;
        return 1;
    }
    std::string key{};
    in_file >> key;

    std::vector<std::string> name_answer_pairs;
    std::string text{};

    while(in_file >> text){
        name_answer_pairs.push_back(text);
    }

    //ruler
    std::cout << "\n1234567890123456789012345678901234567890123456789012345678901234567890\n" << std::endl;

    int running_sum{0};
    for(size_t i = 0; i < name_answer_pairs.size() - 1; i += 2){
        std::string name = name_answer_pairs.at(i);
        std::string answer = name_answer_pairs.at(i + 1);

        
        int score {0};

        for(size_t j = 0; j < key.size(); ++j){
            if(key[j] == answer[j]){
                ++score;
            }
        }

        running_sum += score;

        std::cout << std::setw(10) << std::left  << name << std::setw(10) << std::left << score << std::endl;
    }

    double average_score{0.0};
    if(name_answer_pairs.size() > 0)
        average_score = static_cast<double>(running_sum)/(name_answer_pairs.size()/2);
        std::cout << std::setw(10) << std::left  << "Average" << std::setw(10) << std::left << average_score << std::endl;

    in_file.close();


    return 0;
}