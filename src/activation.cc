#include "activation.hh"

double sigmoid(double z, double a, bool prime) {
    return prime ? std::exp(z) / std::pow(std::exp(z) + 1.0, 2.0) : 
    1.0 / (1.0 + std::exp(-z));
}

double tanh(double z, double a, bool prime) {
    return prime ? (4.0 * std::exp(2.0 * z)) / std::pow(std::exp(2.0 * z) + 1.0, 2.0) : 
    (std::exp(z) - std::exp(-z)) / (std::exp(z) + std::exp(-z));
}

double ReLU(double z, double a, bool prime) {
    return prime ? z > 0.0 ? 1.0 : 0.0 : z > 0.0 ? z : 0.0;
}

double leakyReLU(double z, double a, bool prime) {
    return prime ? z > 0.0 ? a : 0.0 : z > 0.0 ? z : a * z;
}