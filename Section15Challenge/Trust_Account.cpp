#include "Trust_Account.h"

Trust_Account::Trust_Account(std::string name, double balance, double int_rate, int withdrawals) 
: Savings_Account{name, balance, int_rate}, withrawals{withdrawals}{
}

bool Trust_Account::deposit(double amount) {
    if(amount >= 5000.0)
        amount += 50.0;
    return Savings_Account::deposit(amount);
}

bool Trust_Account::withdraw(double amount){
    if(this->withrawals > 3 || amount > this->balance * 0.2)
        return false;
    if(Account::withdraw(amount)){
        this->withrawals++;
        return true;
    }
    else {
        return false;
    }
}

std::ostream &operator<<(std::ostream &os, const Trust_Account &account) {
    os << "[Trust_Account: " << account.name << ": " << account.balance << ", " << account.int_rate << "%]";
    return os;
}