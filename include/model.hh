#pragma once

#include "vectormatrix.hh"
#include "initializer.hh"
#include "activation.hh"

struct model {
    uint32_t numLayers;
    vector* layers;
    matrix* weights;
    vector* biases;

    model(uint32_t numLayers, uint32_t* layersizes);
    model(model* m); // Copy constructor for gradients

    void initWeights(void (*init)(matrix* m, uint32_t seed), uint32_t seed);
    void initBiases(double d); // Sets all biases to a value

    void evaluate(double (*activation)(double z, double a, double prime)); // a is an optional paramater

    bool setInput(vector* input); // bool indicates success
    void getOutput(vector*& output);

    void zero(); // Zeroing for gradients
    bool addModel(model* m, double scale); // Mainly for gradients

    // Data Scheme
    // First int (N) is number of layers
    // We dont save the layers (they aren't part of the model)
    // Next inputs are the weights
    // Next inputs are the biases

    bool save(char* name); 
    bool load(char* name); // bool indicates success
};