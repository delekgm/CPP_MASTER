#include <iostream>
#include <vector>
#include "sieve.h"

using namespace std;

int ovenTime();

int main()
{
    cout << "Hello, world" << endl;
    // ovenTime();
    auto primes = sieve::primes(100);
    for(auto p : primes ){
        cout << p << endl;
    }
    return 0;
}

int ovenTime(){
    int n {10};
    int n1 {20};

    n += n1;

    return n;
}