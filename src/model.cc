#include "model.hh"

model::model(uint32_t numLayers, u_int32_t* layersizes) : numLayers(numLayers) {
    layers = (vector*)malloc(numLayers * sizeof(vector));
    weights = (matrix*)malloc((numLayers - 1) * sizeof(matrix));
    biases = (vector*)malloc((numLayers - 1) * sizeof(vector));

    for(int i = 0; i < numLayers; i++) {
        layers[i].size = layersizes[i];
        layers[i].data = (double*)calloc(layersizes[i], sizeof(double));
    }

    for(int i = 0; i < numLayers - 1; i++) {
        uint32_t sizex = layersizes[i];
        uint32_t sizey = layersizes[i + 1];

        weights[i].sizex = sizex;
        weights[i].sizey = sizey;

        weights[i].data = (double**)malloc(sizex * sizeof(double*));

        for(int x = 0; x < sizex; x++) {
            weights[i].data[x] = (double*)calloc(sizey, sizeof(double));
        }
    }

    for(int i = 0; i < numLayers - 1; i++) {
        biases[i].size = layersizes[i + 1];
        biases[i].data = (double*)calloc(layersizes[i + 1], sizeof(double));
    }
}

void model::initWeights(void (*init)(matrix* m, uint32_t seed), u_int32_t seed) {
    for(int i = 0; i < numLayers - 1; i++) {
        init(&weights[i], seed + i);
    }
}

void model::initBiases() {}

void model::evaluate(double (*activation)(double z, double a)) {
    for(int i = 1; i < numLayers; i++) {
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
    output = &layers[numLayers - 1];
}

bool model::save(char* name) {
    FILE* file = fopen(name, "w");

    if (file == NULL) {
        return false;
    }

    if(fprintf(file, "%d\n\n", numLayers) < 0) {
        return false;
    }

    for(int i = 0; i < numLayers; i++) {
        if(fprintf(file, "%d, ", layers[i].size) < 0) {
            return false;
        }
    }

    if(fprintf(file, "\n\n") < 0) {
        return false;
    }

    for(int i = 0; i < numLayers - 1; i++) {
        for(int j = 0; j < weights[i].sizex; j++) {
            for(int k = 0; k < weights[i].sizey; k++) {
                if(fprintf(file, "%lf, ", weights[i].data[j][k]) < 0) {
                    return false;
                }
            }

            if(fprintf(file, "\n") < 0) {
                return false;
            }
        }

        if(fprintf(file, "\n") < 0) {
            return false;
        }
    }

    for(int i = 0; i < numLayers - 1; i++) {
        for(int j = 0; j < biases[i].size; j++) {
            if(fprintf(file, "%lf, ", biases[i].data[j]) < 0) {
                return false;
            }
        }

        if(fprintf(file, "\n\n") < 0) {
            return false;
        }
    }

    if(fclose(file) != 0) {
        return false;
    }

    return true;
}

bool model::load(char* name) {
    FILE* file = fopen(name, "r");

    if (file == NULL) {
        return false;
    }

    u_int32_t newNumLayers;

    if(fscanf(file, "%d", &newNumLayers) == EOF) {
        return false;
    }

    uint32_t* layerSizes = (uint32_t*)malloc(newNumLayers * sizeof(u_int32_t));

    for(int i = 0; i < newNumLayers; i++) {
        if(fscanf(file, "%d,", &layerSizes[i]) == EOF) {
            return false;
        }
    }

    matrix* newWeights = (matrix*)malloc((newNumLayers - 1) * sizeof(matrix));

    for(int i = 0; i < newNumLayers - 1; i++) {
        double** data = (double**)malloc(layerSizes[i] * sizeof(double*));

        for(int j = 0; j < layerSizes[i]; j++) {
            data[j] = (double*)malloc(layerSizes[i + 1] * sizeof(double));

            for(int k = 0; k < layerSizes[i + 1]; k++) {
                if(fscanf(file, "%lf,", &data[j][k]) == EOF) {
                    return false;
                }
            }
        }

        newWeights[i].data = data;
        newWeights[i].sizex = layerSizes[i];
        newWeights[i].sizey = layerSizes[i + 1];
    }

    vector* newBiases = (vector*)malloc((newNumLayers - 1) * sizeof(vector));

    for(int i = 1; i < newNumLayers; i++) {
        double* data = (double*)malloc(layerSizes[i] * sizeof(double));

        for(int j = 0; j < layerSizes[i]; j++) {
            if(fscanf(file, "%lf,", &data[j]) == EOF) {
                return false;
            }
        }

        newBiases[i - 1].data = data;
        newBiases[i - 1].size = layerSizes[i];
    }

    numLayers = newNumLayers;
    weights = newWeights;
    biases = newBiases;

    if(fclose(file) != 0) {
        return false;
    }

    return true;
}