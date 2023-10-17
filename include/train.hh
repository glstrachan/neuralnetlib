#pragma once

#include "trainingdata.hh"
#include "model.hh"

#include <vector>
#include <stdlib.h> 
#include <cmath>

bool train(model* m, trainingData* data, activationType* a, uint32_t batchSize, uint32_t epochs, double rate, u_int32_t seed); // bool indicates success