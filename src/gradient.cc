#include "gradient.hh"

gradient::gradient(model* m) {
    numLayers = m -> numLayers;

    weights = (matrix*)malloc((numLayers - 1) * sizeof(matrix));
    biases = (vector*)malloc((numLayers - 1) * sizeof(vector));

    for(int i = 0; i < numLayers - 1; i++) {
        u_int32_t sizex = m -> weights[i].sizex;
        u_int32_t sizey = m -> weights[i].sizey;

        double** data = (double**)malloc(sizex * sizeof(double*));

        for(int j = 0; j < sizex; j++) {
            data[j] = (double*)calloc(sizey, sizeof(double));
        }

        weights[i].sizex = sizex;
        weights[i].sizey = sizey;
        weights[i].data = data;
    }

    for(int i = 0; i < numLayers - 1; i++) {
        u_int32_t size = m -> biases[i].size;

        double* data = (double*)calloc(size, sizeof(double));

        biases[i].size = size;
        biases[i].data = data;
    }
}

void gradient::reset() {
    for(int i = 0; i < numLayers - 1; i++) {
        for(int j = 0; j < weights[i].sizex; j++) {
            for(int k = 0; k < weights[i].sizey; k++) {
                weights[i].data[j][k] = 0.0;
            }
        } 
    }

    for(int i = 0; i < numLayers; i++) {
        for(int j = 0; j < biases[i].size; j++) {
            biases[i].data[j] = 0.0;
        }
    }
}

bool gradient::addGrad(gradient* g, double scale) {
    if(numLayers != g -> numLayers) {
        return false;
    }

    for(int i = 0; i < numLayers - 1; i++) {
        int sizex = weights[i].sizex;
        int sizey = weights[i].sizey;

        if(sizex != g -> weights[i].sizex || sizey != g -> weights[i].sizey) {
            return false;
        }

        for(int j = 0; j < sizex; j++) {
            for(int k = 0; k < sizey; k++) {
                weights[i].data[j][k] += (g -> weights[i].data[j][k] * scale);
            }
        }
    }

    for(int i = 0; i < numLayers - 1; i++) {
        int size = biases[i].size;

        if(size != g -> biases[i].size) {
            return false;
        }

        for(int j = 0; j < size; j++) {
            biases[i].data[j] += (g -> biases[i].data[j] * scale);
        }
    }

    return true;
}