#include "train.hh"
#include "trainingdata.hh"
#include "activation.hh"
#include "cost.hh"

#include <stdlib.h>

#include "stdio.h"
#include <iostream>

int main() {
    uint32_t inputSize = 3;
    uint32_t outputSize = 1;

    // We will train using the function w(x,y,z) = 3x^3 - 2y^2 + z;
    uint32_t trainingSize = 10000;
    vector* inputs = (vector*)malloc(trainingSize * sizeof(vector));
    vector* outputs = (vector*)malloc(trainingSize * sizeof(vector));

    srand(12345);

    for(int i = 0; i < trainingSize; i++) {
        double x = ((double)(rand() % 1001) / 1000.0) * 2.0 - 1.0;
        double y = ((double)(rand() % 1001) / 1000.0) * 2.0 - 1.0;
        double z = ((double)(rand() % 1001) / 1000.0) * 2.0 - 1.0;

        double w = (3 * x * x * x) - (2 * y * y) + z;

        // std::cout << x << " " << y << " " << z << " = " << w << std::endl;

        double* inputData = (double*)malloc(3 * sizeof(double));
        double* outputData = (double*)malloc(1 * sizeof(double));

        inputData[0] = x; inputData[1] = y; inputData[2] = z;
        outputData[0] = w;

        inputs[i].size = 3;
        inputs[i].data = inputData;

        outputs[i].size = 1;
        outputs[i].data = outputData;
    }

    trainingData data(trainingSize, inputs, outputs);

    uint32_t numLayers = 4;
    uint32_t* layersizes = (uint32_t*)malloc(numLayers * sizeof(uint32_t));

    layersizes[0] = 3; layersizes[1] = 4; layersizes[2] = 4; layersizes[3] = 1;

    model m(numLayers, layersizes);

    m.initWeights(HeInit, 83439);

    //std::cout << "\n\nWeights Before\n" << m;

    train(&m, &data, leakyReLU, quadraticCost, trainingSize / 100, 400, 0.5, 999);

    //std::cout << "\n\nWeights After\n" << m;

    double avgcost = 0.0;

    for(int i = 0; i < 1000; i++) {
        double x = ((double)(rand() % 1001) / 1000.0) * 2.0 - 1.0;
        double y = ((double)(rand() % 1001) / 1000.0) * 2.0 - 1.0;
        double z = ((double)(rand() % 1001) / 1000.0) * 2.0 - 1.0;

        double* testData = (double*)malloc(inputSize * sizeof(double));
        testData[0] = x; 
        testData[1] = y; 
        testData[2] = z;

        vector testVector(inputSize, testData);

        m.setInput(&testVector);
        m.evaluate(leakyReLU);

        vector* testOutput = (vector*)malloc(sizeof(vector));
        m.getOutput(testOutput);

        //std::cout << "Expected: " << (3 * x * x * x) - (2 * y * y) + z << " Actual: " << testOutput -> data[0] << std::endl;

        avgcost += quadraticCost((3 * x * x * x) - (2 * y * y) + z, testOutput -> data[0], false) / 1000;
    }

    std::cout << avgcost << std::endl;
    
    return 0;
}