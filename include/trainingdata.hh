#pragma once

#include "model.hh"

// Training data will assume u have a series of vectors corresponding to inputs and outputs

struct trainingData {
    vector* inputs;
    vector* outputs;

    trainingData(vector* inputs, vector* outputs);

    // TODO
    bool load(char* name); // bool indicates success
};