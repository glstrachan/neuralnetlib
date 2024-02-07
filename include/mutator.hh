#pragma once

#include "vectormatrix.hh"
#include "model.hh"
#include <algorithm>

/* Basically randomly replaces weights in the model */
void randomResetting(model* m, uint32_t seed);

/* Adds a random value to the weights */
void gaussianMutation(model* m, uint32_t seed);

/* Replaces the weights with a random value */
void polynomialMutation(model* m, uint32_t seed);

/* Shuffles the weights */
void weightShuffling(model* m, uint32_t seed);
