#include <iostream>
#include <cstdlib>

int gaussianSum(int n) {
    return (n * (n + 1)) / 2;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <num1> \n";
        return 1;
    }

    int num = atoi(argv[1]);

    std::cout << "Sum: " << gaussianSum(num) << "\n";
    return 0;
}