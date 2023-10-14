#include "activation.hh"

double sigmoid(double z, double a) {
    return 1 / (1 + std::exp(-z));
}

double tanh(double z, double a) {
    return (std::exp(z) - std::exp(-z)) / (std::exp(z) + std::exp(-z));
}

double ReLU(double z, double a) {
    return z > 0 ? z : 0;
}

double leakyReLU(double z, double a) {
    return z > 0 ? z : a * z;
}