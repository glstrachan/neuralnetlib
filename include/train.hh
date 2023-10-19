#pragma once

#include "trainingdata.hh"
#include "model.hh"

#include <vector>
#include <stdlib.h> 
#include <cmath>

bool train(model* m, trainingData* data, double (*activation)(double z, double a, double prime), double (*cost)(double expected, double actual, bool prime), uint32_t batchSize, uint32_t epochs, double rate, uint32_t seed); // bool indicates success