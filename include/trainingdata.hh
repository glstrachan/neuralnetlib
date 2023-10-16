#pragma once

#include "vectormatrix.hh"

// Training data will assume u have a series of vectors corresponding to inputs and outputs

struct trainingData {
    u_int32_t size;
    vector* inputs;
    vector* outputs;

    trainingData(uint32_t size, vector* inputs, vector* outputs);

    // TODO
    bool load(char* name); // bool indicates success
};