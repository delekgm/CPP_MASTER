#include "Checking_Account.h"

Checking_Account::Checking_Account(std::string name, double balance) 
: Account{name, balance}{
    std::cout << "Checking Account constructor called" << std::endl;
}

bool Checking_Account::withdraw(double amount){
    std::cout << "Checking Account withdraw called" << std::endl;
    double withdrawal_fee = 1.50;
    amount += withdrawal_fee;
    return Account::withdraw(amount);
}

std::ostream &operator<<(std::ostream &os, const Checking_Account &account) {
    os << "[Savings_Account: " << account.name << ": " << account.balance << "]";
    return os;
}