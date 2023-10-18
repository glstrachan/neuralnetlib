#pragma once

#include "model.hh"
#include "vectormatrix.hh"

struct gradient {
    u_int32_t numLayers;
    matrix* weights;
    vector* biases;

    gradient(model* m); // Takes a model to be based off of

    void reset();
    bool addGrad(gradient* g, double scale);
};

bool addModelGradient(model* m, gradient* g, double rate);