#include <iostream>

double daily_rate(double hourly_rate){
    return hourly_rate * 8;
}

double apply_discount(double price, double discount_percent){
    return price - (price * (discount_percent / 100));
}

double monthly_rate(double hourly_rate, double discount_percent){
    double price = (hourly_rate * 8 * 22);
    double discount = price * (discount_percent / 100);
    return ceil(price - discount);
}

double days_in_budget(double budget, double hourly_rate, double discount_percent){
    double daily = hourly_rate * 8;
    double daily_with_discount = daily - (daily * discount_percent / 100);
    return floor(budget / daily_with_discount);
}

int main(){
    auto d_r = daily_rate(60);
    std::cout << "Daily rate: " << d_r << std::endl;

    auto a_d = apply_discount(150, 10);
    std::cout << "Price with discount: " << a_d << std::endl;

    auto m_r = monthly_rate(77, 10.5);
    std::cout << "Monthly rate: " << m_r << std::endl;

    auto d_i_b = days_in_budget(20'000, 80, 11.0);
    std::cout << "Days in budget: " << d_i_b << std::endl;
    
    return 0;
}