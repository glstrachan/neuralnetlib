#include "trainingdata.hh"
#include <iostream>

int main() {
    trainingData t;

    char* name = "./tests/testdata/data.csv";
    std::cout << t.load(name); // This will test properly if a data.csv file exists

    return 0;
}