#include "mutator.hh"

void randomResetting(model* m, uint32_t seed) {
    double mutationRate = 0.1;

    std::mt19937 rng(seed);

    std::uniform_real_distribution<float> dist(0.0, 1.0);

    for(int i = 0; i < m -> numLayers - 1; i++) {
        for(int x = 0; x < m -> weights[i].sizex; x++) {
            for(int y = 0; y < m -> weights[i].sizey; y++) {
                if(dist(rng) < mutationRate) {
                    m -> weights[i].data[x][y] = dist(rng) * 2.0 - 1.0;
                }
            }
        }
    }
}

void gaussianMutation(model* m, uint32_t seed) {
    double mutationRate = 0.1;

    std::mt19937 rng(seed);

    std::normal_distribution<float> dist(0.0, 1.0);

    for(int i = 0; i < m -> numLayers - 1; i++) {
        for(int x = 0; x < m -> weights[i].sizex; x++) {
            for(int y = 0; y < m -> weights[i].sizey; y++) {
                if(dist(rng) < mutationRate) {
                    m -> weights[i].data[x][y] += dist(rng) * 0.1 - 0.05;
                }
            }
        }
    }
}

void polynomialMutation(model* m, uint32_t seed) {
    double mutationRate = 0.1;
    double eta = 20.0;

    std::mt19937 rng(seed);
    std::uniform_real_distribution<float> dist(0.0, 1.0);

    for(int i = 0; i < m->numLayers - 1; i++) {
        for(int x = 0; x < m->weights[i].sizex; x++) {
            for(int y = 0; y < m->weights[i].sizey; y++) {
                if(dist(rng) < mutationRate) {
                    double u = dist(rng);
                    double delta;
                    if (u < 0.5) {
                        delta = std::pow(2.0 * u, 1.0 / (eta + 1.0)) - 1.0;
                    } else {
                        delta = 1.0 - std::pow(2.0 * (1.0 - u), 1.0 / (eta + 1.0));
                    }
                    m->weights[i].data[x][y] += delta;
                }
            }
        }
    }
}

void weightShuffling(model* m, uint32_t seed) {
    std::mt19937 rng(seed);

    for (uint32_t i = 0; i < m->numLayers - 1; i++) {
        std::vector<double> flattenedWeights;
        for (uint32_t x = 0; x < m->weights[i].sizex; x++) {
            for (uint32_t y = 0; y < m->weights[i].sizey; y++) {
                flattenedWeights.push_back(m->weights[i].data[x][y]);
            }
        }

        std::shuffle(flattenedWeights.begin(), flattenedWeights.end(), rng);

        uint32_t index = 0;
        for (uint32_t x = 0; x < m->weights[i].sizex; x++) {
            for (uint32_t y = 0; y < m->weights[i].sizey; y++) {
                m->weights[i].data[x][y] = flattenedWeights[index++];
            }
        }
    }
}