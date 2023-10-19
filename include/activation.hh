#pragma once

#include <cmath>

double sigmoid(double z, double a, bool prime);
double tanh(double z, double a, bool prime);
double ReLU(double z, double a, bool prime);
double leakyReLU(double z, double a, bool prime);