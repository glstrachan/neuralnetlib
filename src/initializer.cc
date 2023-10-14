#include "initializer.hh"

void randomInit(matrix* m, uint32_t seed) {
    std::mt19937 rng(seed);
    std::uniform_real_distribution<double> dist(-1.0, 1.0);

    for(int x = 0; x < m -> sizex; x++) {
        for(int y = 0; y < m -> sizey; y++) {
            m -> data[x][y] = dist(rng);
        }
    }
}

void XGInit(matrix* m, uint32_t seed) {
    std::mt19937 rng(seed);
    std::normal_distribution<double> dist(0, std::sqrt(1.0 / m -> sizex));

    for(int x = 0; x < m -> sizex; x++) {
        for(int y = 0; y < m -> sizey; y++) {
             m -> data[x][y] = dist(rng);
        }
    }
}

void HeInit(matrix* m, uint32_t seed) {
    std::mt19937 rng(seed);
    std::normal_distribution<double> dist(0, std::sqrt(2.0 / m -> sizex));

    for(int x = 0; x < m -> sizex; x++) {
        for(int y = 0; y < m -> sizey; y++) {
            m -> data[x][y] = dist(rng);
        }
    }
}