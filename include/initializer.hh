#pragma once

#include "vectormatrix.hh"
#include <random>

void randomInit(matrix* m, uint32_t seed);

/* Xavier Glorot Initialization */
void XGInit(matrix* m, uint32_t seed);

/* Kaiming He Initialization */
void HeInit(matrix* m, uint32_t seed);