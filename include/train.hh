#pragma once

#include "trainingdata.hh"
#include "model.hh"
#include "cost.hh"

#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>

bool train(model* m, trainingData* data, trainingData* validation, double (*activation)(double z, double a, bool prime), double (*cost)(double expected, double actual, bool prime), uint32_t batchSize, uint32_t epochs, double rate, uint32_t seed); // bool indicates success