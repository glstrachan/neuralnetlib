#include "model.hh"
#include <iostream>

int main() {
    uint32_t datasize = 2;
    double* data = (double*)malloc(datasize * sizeof(double));

    data[0] = 0.1;
    data[1] = 0.2;

    vector v(datasize, data);

    std::cout << "\nInput Layer\n";
    for(int i = 0; i < v.size; i++) {
        printf("%5.2f ", v.data[i]);
    }

    uint32_t numlayers = 4;
    u_int32_t* layersizes = (u_int32_t*)malloc(4 * sizeof(uint32_t));

    layersizes[0] = 2;
    layersizes[1] = 3;
    layersizes[2] = 4;
    layersizes[3] = 1;

    model m(numlayers, layersizes);

    m.initWeights(HeInit, 0);

    std::cout << "\n\nWeights\n";
    for(int i = 0; i < m.numlayers - 1; i ++) {
        for(int x = 0; x < m.weights[i].sizex; x++) {
            for(int y = 0; y < m.weights[i].sizey; y++) {
               printf("%5.2f ", m.weights[i].data[x][y]);
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    m.setInput(&v);

    m.evaluate(sigmoid);

    vector* r = (vector*)malloc(sizeof(vector));

    m.getOutput(r);

    std::cout << "Output Layer\n";
    for(int i = 0; i < r -> size; i++) {
        printf("%5.2f ", r -> data[i]);
    }

    std::cout << std::endl;

    return 0;
}