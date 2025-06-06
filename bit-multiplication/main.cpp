#include <iostream>
using namespace std;

int multiply(int a, int b) {
    int product = 0; // Initialize the product
    int i = 0;       // Keeps track of the bit position in b

    while (b > 0) {
        if (b & 1) { // If the current bit of b is 1
            product += (a << i); // Add a shifted by i to the product
        }
        b >>= 1; // Shift b to the right (process the next bit)
        i++;     // Move to the next bit position
    }

    return product;
}

int main() {
    int a = 3, b = 5;
    cout << "Product: " << multiply(a, b) << endl; // Output: 15
    return 0;
}