#include "model.hh"

model::model(uint32_t numlayers, u_int32_t* layersizes) : numlayers(numlayers) {
    layers = (vector*)malloc(numlayers * sizeof(vector));
    weights = (matrix*)malloc((numlayers - 1) * sizeof(matrix));
    biases = (vector*)malloc((numlayers - 1) * sizeof(vector));

    for(int i = 0; i < numlayers; i++) {
        layers[i].size = layersizes[i];
        layers[i].data = (double*)calloc(layersizes[i], sizeof(double));
    }

    for(int i = 0; i < numlayers - 1; i++) {
        uint32_t sizex = layersizes[i];
        uint32_t sizey = layersizes[i + 1];

        weights[i].sizex = sizex;
        weights[i].sizey = sizey;

        weights[i].data = (double**)malloc(sizex * sizeof(double*));

        for(int x = 0; x < sizex; x++) {
            weights[i].data[x] = (double*)calloc(sizey, sizeof(double));
        }
    }

    for(int i = 0; i < numlayers - 1; i++) {
        biases[i].size = layersizes[i + 1];
        biases[i].data = (double*)calloc(layersizes[i + 1], sizeof(double));
    }
}

void model::initWeights(void (*init)(matrix* m, uint32_t seed), u_int32_t seed) {
    for(int i = 0; i < numlayers - 1; i++) {
        init(&weights[i], seed + i);
    }
}

void model::initBiases() {}

void model::evaluate(double (*activation)(double z, double a)) {
    for(int i = 1; i < numlayers; i++) {
         multiply(&weights[i - 1], &layers[i - 1], &layers[i]);

         for(int j = 0; j < layers[i].size; j++) {
            layers[i].data[j] = activation(layers[i].data[j] + biases[i - 1].data[j], 0.01);
         }
    }
}

bool model::setInput(vector* input) {
    if(input -> size == layers[0].size) {
        layers[0] = *input;
        return true;
    }

    return false;
}

void model::getOutput(vector*& output) {
    output = &layers[numlayers - 1];
}