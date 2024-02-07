#pragma once

#include "model.hh"

/* Chooses between model per weight */
model* uniformCrossover(uint32_t seed, model* a, model* b);

/* Chooses between model per layer */
model* singlePointCrossover(uint32_t seed, model* a, model* b);

/* Blends between models per weight randomly */
model* arithmeticCrossover(uint32_t seed, model* a, model* b);