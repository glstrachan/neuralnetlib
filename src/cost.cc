#include "cost.hh"

float quadraticCost(double expected, double actual, bool prime) {
    return prime ? actual - expected : 0.5 * std::pow(expected - actual, 2.0);
}