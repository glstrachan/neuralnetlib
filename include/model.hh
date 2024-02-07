#pragma once

#include "vectormatrix.hh"
#include "initializer.hh"
#include "activation.hh"

#include <iostream>

struct model {
    uint32_t numLayers;
    vector* layers;
    matrix* weights;
    vector* biases;

    model(uint32_t numLayers, uint32_t* layersizes);
    model(model* m); // Copy constructor for gradients
    model(model* (*recombiner)(uint32_t seed, model* a, model* b), uint32_t seed, model* a, model* b); // Recombiner for genetic algorithms

    void initWeights(void (*init)(matrix* m, uint32_t seed), uint32_t seed);
    void initBiases(double d); // Sets all biases to a value

    void evaluate(double (*activation)(double z, double a, bool prime)); // a is an optional paramater

    bool setInput(vector* input); // bool indicates success
    void getOutput(vector*& output);

    void zero(); // Zeroing for gradients
    bool addModel(model* m, double scale); // Mainly for gradients

    void mutate(void (*mutator)(model* m, uint32_t seed), uint32_t seed); // Mutates the model

    // Data Scheme
    // First int (N) is number of layers
    // We dont save the layers (they aren't part of the model)
    // Next inputs are the weights
    // Next inputs are the biases

    bool save(char* name); 
    bool load(char* name); // bool indicates success
};