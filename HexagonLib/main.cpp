#include <iostream>
#include "hex.h"

int main(){
    Hex h {1, 2};
    std::cout << h.q << std::endl;
    std::cout << h.r << std::endl;
    std::cout << h.s << std::endl;
    return 0;
}