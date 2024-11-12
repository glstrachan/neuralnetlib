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

    srand(12345);

    // We will train using the function w(x,y,z) = 3x^3 - 2y^2 + z;
    uint32_t trainingSize = 10000;
    vector* inputs = (vector*)malloc(trainingSize * sizeof(vector));
    vector* outputs = (vector*)malloc(trainingSize * sizeof(vector));

    for(int i = 0; i < trainingSize; i++) {
        double x = ((double)(rand() % 1001) / 1000.0) * 2.0 - 1.0;
        double y = ((double)(rand() % 1001) / 1000.0) * 2.0 - 1.0;
        double z = ((double)(rand() % 1001) / 1000.0) * 2.0 - 1.0;

        double w = (3 * x * x * x) - (2 * y * y) + z;

        double* inputData = (double*)malloc(3 * sizeof(double));
        double* outputData = (double*)malloc(1 * sizeof(double));

        inputData[0] = x; inputData[1] = y; inputData[2] = z;
        outputData[0] = w;

        inputs[i].size = inputSize;
        inputs[i].data = inputData;

        outputs[i].size = outputSize;
        outputs[i].data = outputData;
    }

    trainingData data(trainingSize, inputs, outputs);

    // Making validation data

    uint32_t validationSize = 10000;
    vector* vInputs = (vector*)malloc(validationSize * sizeof(vector));
    vector* vOutputs = (vector*)malloc(validationSize * sizeof(vector));

    for(int i = 0; i < trainingSize; i++) {
        double x = ((double)(rand() % 1001) / 1000.0) * 2.0 - 1.0;
        double y = ((double)(rand() % 1001) / 1000.0) * 2.0 - 1.0;
        double z = ((double)(rand() % 1001) / 1000.0) * 2.0 - 1.0;

        double w = (3 * x * x * x) - (2 * y * y) + z;

        double* inputData = (double*)malloc(3 * sizeof(double));
        double* outputData = (double*)malloc(1 * sizeof(double));

        inputData[0] = x; inputData[1] = y; inputData[2] = z;
        outputData[0] = w;

        vInputs[i].size = inputSize;
        vInputs[i].data = inputData;

        vOutputs[i].size = outputSize;
        vOutputs[i].data = outputData;
    }

    trainingData vData(validationSize, vInputs, vOutputs);

    // Defining out model shape
    uint32_t numLayers = 4;
    uint32_t* layersizes = (uint32_t*)malloc(numLayers * sizeof(uint32_t));

    layersizes[0] = 3; layersizes[1] = 16; layersizes[2] = 16; layersizes[3] = 1;

    model m(numLayers, layersizes);

    m.initWeights(HeInit, 834939);

    // Do training
    //train(&m, &data, &vData, leakyReLU, quadraticCost, trainingSize / 70, 5000, 0.05, 9699);

    char* name = "save.csv";
    m.load(name);

    // Find out model cost
    double avgcost = 0.0;

    for(int i = 0; i < 100; i++) {
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

        std::cout << "Expected: " << (3 * x * x * x) - (2 * y * y) + z << " Actual: " << testOutput -> data[0] << std::endl;

        avgcost += quadraticCost((3 * x * x * x) - (2 * y * y) + z, testOutput -> data[0], false) / 1000;
    }

    std::cout << avgcost << std::endl;

    for (int i = 0; i < trainingSize; i++) {
        free(inputs[i].data);  
        free(outputs[i].data);
    }

    free(inputs);
    free(outputs);

    for (int i = 0; i < validationSize; i++) {
        free(vInputs[i].data);  
        free(vOutputs[i].data);
    }

    free(vInputs);
    free(vOutputs);
    free(layersizes);

    // m.save(name);
    
    return 0;
}