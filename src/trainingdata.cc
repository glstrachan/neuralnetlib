#include "trainingdata.hh"

trainingData::trainingData(uint32_t size, vector* inputs, vector* outputs) : size(size), inputs(inputs), outputs(outputs) {}

bool trainingData::load(char* name) {
    FILE* file = fopen(name, "r");

    if (file == NULL) {
        return false;
    }

    uint32_t inputSize, outputSize;

    if(fscanf(file, "%d%d%d", &size, &inputSize, &outputSize) == EOF) {
        return false;
    }

    inputs = (vector*)malloc(size * sizeof(vector));
    outputs = (vector*)malloc(size * sizeof(vector));

    vector input(inputSize, nullptr);

    for(int i = 0; i < size; i++) {
        double* data = (double*)malloc(inputSize * sizeof(double));

        for(int j = 0; j < inputSize; j++) {
            if(fscanf(file, "%lf", &data[j]) == EOF) {
                return false;
            }
        }

        input.data = data;
        inputs[i] = input;
    }

    vector output(outputSize, nullptr);

    for(int i = 0; i < size; i++) {
        double* data = (double*)malloc(outputSize * sizeof(double));

        for(int j = 0; j < outputSize; j++) {
            if(fscanf(file, "%lf", &data[j]) == EOF) {
                return false;
            }
        }

        output.data = data;
        outputs[i] = output;
    }

    if(fclose(file) != 0) {
        return false;
    }

    return true;
}