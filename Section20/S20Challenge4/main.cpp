// Section 20
// Challenge 4
// Identifying palindrome strings using a deque
#include <cctype>
#include <queue>
#include <stack>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

bool is_palindrome(const std::string &s)
{   
    std::queue<char> q;
    std::stack<char> stk;
    for(char c : s){
        // is alpha tells you if a char is in the alphabet
        if(std::isalpha(c)) {
            q.push(std::toupper(c));
            stk.push(std::toupper(c));
        }
    }

    char c1 {};
    char c2 {};

    while(q.size() > 1 && stk.size() > 1){
        c1 = q.front();
        c2 = stk.top();
        q.pop();
        stk.pop();
        if(c1 != c2) return false;
    }

    return true;
}

int main()
{
    std::vector<std::string> test_strings{ "a", "aa", "aba", "abba", "abbcbba", "ab", "abc", "radar", "bob", "ana",
        "avid diva", "Amore, Roma", "A Toyota's a toyota", "A Santa at NASA", "C++",
        "A man, a plan, a cat, a ham, a yak, a yam, a hat, a canal-Panama!", "This is a palindrome", "palindrome" };
   
    std::cout << std::boolalpha;
    std::cout << std::setw(8) << std::left << "Result" << "String" << std::endl;
    for(const auto& s : test_strings) {
        std::cout << std::setw(8) << std::left << is_palindrome(s) << " " << s << std::endl;
    }
    std::cout << std::endl;
    return 0;
}