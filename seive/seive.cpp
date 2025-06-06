#include <iostream>
#include <vector>
#include <cmath>

std::vector<int> sieve(int n)
{
    std::vector<bool> isPrime(n, true);

    isPrime[0] = false;
    isPrime[1] = false;

    // sqrt to optimize
    for(auto p = 2; p < floor(sqrt(n)); ++p) 
    {
        if(isPrime[p]) 
        {
            for(auto step = p*p; step < n; step += p) 
            {
                isPrime[step] = false;
            }
        }
    }

    std::vector<int> primes;
    for(auto i = 2; i < n; ++i) 
    {
        if(isPrime[i]) 
        {
            primes.push_back(i);
        }
    }
    return primes;
}
int main() 
{   
    std::vector<int> myPrimes = sieve(100);

    for(auto prime : myPrimes) {
        std::cout << prime << " ";
    }
    std::cout << std::endl;

    return 0;
}