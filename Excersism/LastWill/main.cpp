#include <iostream>
#include "families.h"

int main(){
    auto account_number = estate_executor::assemble_account_number(2);
    auto code = estate_executor::assemble_code();
    std::cout << "The account num is: " << account_number << " and the code is: " << code << std::endl; 
    return 0;
}