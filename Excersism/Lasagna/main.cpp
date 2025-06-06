#include <iostream>
#include <array>

int ovenTime();
int remainingOvenTime(const int actualMinutesInOven);
int prepTime(const int numLayers);
std::array<int, 4> letter_grades(int highest_score);

int main(){
    auto time = ovenTime();
    std::cout << time << std::endl;

    auto remainingTime = remainingOvenTime(30);
    std::cout << remainingTime << std::endl;

    auto prep = prepTime(2);
    std::cout << prep << std::endl;

    std::array<int, 4> grades = letter_grades(97);

    std::cout << grades[0] << std::endl;
    std::cout << grades[1] << std::endl;
    std::cout << grades[2] << std::endl;
    std::cout << grades[3] << std::endl;

    return 0;
}

int prepTime(const int numLayers){
    return numLayers * 2;
}
int remainingOvenTime(const int actualMinutesInOven){
    return ovenTime() - actualMinutesInOven;
}

int ovenTime(){
    return 40;
}

std::array<int, 4> letter_grades(int highest_score) {
    std::array<int, 4> grade_thresholds;
    int total_score_range = highest_score - 40;
    int score_range = total_score_range / 4;
    int offset = 3;
    int score_off = 0;
    if(highest_score % 2 == 0) score_off = 1;
    for(int i = 3; i >= 0; --i){
        int grade_threshold = highest_score - ((i + 1) * score_range) + score_off;
        // std::cout << grade_threshold << std::endl;
        grade_thresholds[i - offset] = grade_threshold;
        offset -= 2;
    }
    return grade_thresholds;
}