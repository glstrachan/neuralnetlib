#pragma once

#include "vectormatrix.hh"
#include <stdio.h>

struct trainingData {
    uint32_t size;
    vector* inputs;
    vector* outputs;

    trainingData(uint32_t size, vector* inputs, vector* outputs);
    trainingData();

    // Data Scheme: 
    // First int: the number of sets of data
    // Second and Third ints: the size of inputs and outputs
    // Next floats: the inputs followed by the outputs

    bool load(char* name); // bool indicates success
};