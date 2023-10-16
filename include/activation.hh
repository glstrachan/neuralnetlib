#pragma once

#include <cmath>

double sigmoid(double z, double a);
double tanh(double z, double a);
double ReLU(double z, double a);
double leakyReLU(double z, double a);

// For the derivatives of our activation functions
double sigmoidPrime(double z, double a);
double tanhPrime(double z, double a);
double ReLUPrime(double z, double a);
double leakyReLUPrime(double z, double a);