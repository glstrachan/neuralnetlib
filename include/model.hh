#pragma once

#include "vectormatrix.hh"
#include "initializer.hh"
#include "activation.hh"

struct model {
    uint32_t numlayers;
    vector* layers;
    matrix* weights;

    model(uint32_t numlayers, u_int32_t* layersizes);
    void initWeights(void (*init)(matrix* m, uint32_t seed), u_int32_t seed);
    void evaluate(double (*activation)(double z, double a)); // a is an optional paramater
    bool setInput(vector* input);
    void getOutput(vector*& output);
};