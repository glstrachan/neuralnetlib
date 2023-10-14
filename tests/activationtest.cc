#include "activation.hh"
#include <iostream>

int main() {
    double a = 0.01;

    std::cout << "Testing: sigmoid\n";
    for(double z = -1; z <= 1; z += 0.1) {
        printf("f(%4.1f) = %6.3f\n", z, sigmoid(z, a));
    }

    std::cout << "\nTesting: tanh\n";
    for(double z = -1; z <= 1; z += 0.1) {
        printf("f(%4.1f) = %6.3f\n", z, tanh(z, a));
    }

    std::cout << "\nTesting: ReLU\n";
    for(double z = -1; z <= 1; z += 0.1) {
        printf("f(%4.1f) = %6.3f\n", z, ReLU(z, a));
    }

    std::cout << "\nTesting: Leaky ReLU\n";
    for(double z = -1; z <= 1; z += 0.1) {
        printf("f(%4.1f) = %6.3f\n", z, leakyReLU(z, a));
    }

    return 0;
}