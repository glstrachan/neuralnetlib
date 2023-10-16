#pragma once

#include "vectormatrix.hh"
#include "initializer.hh"
#include "activation.hh"

struct model {
    uint32_t numlayers;
    vector* layers;
    matrix* weights;
    vector* biases;

    model(uint32_t numlayers, u_int32_t* layersizes);

    void initWeights(void (*init)(matrix* m, uint32_t seed), u_int32_t seed);
    void initBiases(); // Currently we set all to 0 initially, so empty

    void evaluate(double (*activation)(double z, double a)); // a is an optional paramater

    bool setInput(vector* input); // bool indicates success
    void getOutput(vector*& output);

    // TODO: Implement these bad boys
    void save(char* name); 
    bool load(char* name); // bool indicates success
};