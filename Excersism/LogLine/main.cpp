#include <iostream>
#include <string>


namespace log_line {
    std::string message(std::string line) {
        size_t colonPos = line.find(':');
        if(colonPos != std::string::npos){
            std::string message = line.substr(colonPos + 2);
            return message;
        } else {
            std::string errorMessage {"Could not find message"};
            return errorMessage;
        }
    }

    std::string log_level(std::string line) {
        size_t openBracketPos = line.find('[');
        size_t closeBracketPos = line.find(']');

        if(openBracketPos != std::string::npos && closeBracketPos != std::string::npos){
            std::string level = line.substr(openBracketPos + 1, closeBracketPos - 1);
            return level;
        } else {
            std::string errorMessage {"No valid log level"};
            return errorMessage;
        }
    }

    std::string reformat(std::string line) {
        size_t openBracketPos = line.find('[');
        size_t closeBracketPos = line.find(']');
        size_t colonPos = line.find(':');

        if(openBracketPos != std::string::npos && closeBracketPos != std::string::npos && colonPos != std::string::npos){
            std::string level = line.substr(openBracketPos, closeBracketPos + 1);
            std::string message = line.substr(colonPos + 2);
            std::string reformatLevel = message + ": " + level;
            return reformatLevel;
        } else {
            std::string errorMessage {"No valid log level"};
            return errorMessage;
        }
    }
}

int main(){
    auto message = log_line::message("[ERROR]: Invalid operation");
    std::cout << message << std::endl;

    auto level = log_line::log_level("[ERROR]: Invalid operation");
    std::cout << level << std::endl;

    auto reformat = log_line::reformat("[ERROR]: Invalid operation");
    std::cout << reformat << std::endl;

    return 0;
}