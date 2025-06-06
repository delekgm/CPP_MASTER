#include <iostream>
#include <fstream>
#include <string>

std::string toLowerCase(const std::string &str);
bool find_substring(const std::string &word_to_find, const std::string target);

int main(){
    std::string search_word{};
    std::string curr_word{};
    int word_count{0};
    std::ifstream in_file;

    in_file.open("romeoandjuliet.txt");
    if(!in_file){
        std::cerr << "Problem opening file" << std::endl;
        return 1;
    }

    std::cout << "Enter a word to search: ";
    std::cin >> search_word;
    std::cout << std::endl;

    search_word = toLowerCase(search_word);

    std::cout << "You are searching " << search_word << std::endl;

    while(in_file >> curr_word){
        curr_word = toLowerCase(curr_word);
        if(find_substring(search_word, curr_word)){
            ++word_count;
            std::cout << curr_word << std::endl;
        }
    }

    std::cout << "The word " << search_word << " was found " << word_count << " times" << std::endl;

    in_file.close();
    return 0;
}

std::string toLowerCase(const std::string &str) {
    std::string result;
    for (char c : str) {
        result += std::tolower(c);
    }
    return result;
}

bool find_substring(const std::string &word_to_find, const std::string target){
    std::size_t found = target.find(word_to_find);
    if(found == std::string::npos){
        return false;
    } else {
        return true;
    }
}
