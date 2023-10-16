#include "activation.hh"

activationType::activationType(double a, double (*activation)(double z, double a), double (*activationPrime)(double z, double a)) : 
a(a), activation(activation), activationPrime(activationPrime) {}

double sigmoid(double z, double a) {
    return 1.0 / (1.0 + std::exp(-z));
}

double tanh(double z, double a) {
    return (std::exp(z) - std::exp(-z)) / (std::exp(z) + std::exp(-z));
}

double ReLU(double z, double a) {
    return z > 0.0 ? z : 0.0;
}

double leakyReLU(double z, double a) {
    return z > 0.0 ? z : a * z;
}

double sigmoidPrime(double z, double a) {
    return std::exp(z) / std::pow(std::exp(z) + 1.0, 2.0);
}

double tanhPrime(double z, double a) {
    return (4.0 * std::exp(2.0 * z)) / std::pow(std::exp(2.0 * z) + 1.0, 2.0);
}

double ReLUPrime(double z, double a) {
    return z > 0.0 ? 1.0 : 0.0;
}

double leakyReLUPrime(double z, double a) {
    return z > 0.0 ? a : 0.0;
}