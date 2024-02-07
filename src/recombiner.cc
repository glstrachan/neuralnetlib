#include "recombiner.hh"

model* uniformCrossover(uint32_t seed, model* a, model* b) {
    model* offspring = new model(a);

    std::mt19937 rng(seed);
    std::uniform_real_distribution<float> dist(0.0, 1.0);

    for (uint32_t i = 0; i < offspring->numLayers - 1; i++) {
        for (uint32_t x = 0; x < offspring->weights[i].sizex; x++) {
            for (uint32_t y = 0; y < offspring->weights[i].sizey; y++) {
                if (dist(rng) < 0.5) {
                    offspring->weights[i].data[x][y] = b->weights[i].data[x][y];
                }
            }
        }
    }

    return offspring;
}

model* singlePointCrossover(uint32_t seed, model* a, model* b) {
    model* offspring = new model(a);

    std::mt19937 rng(seed);
    std::uniform_int_distribution<int> dist(0, offspring->numLayers - 2);

    int crossoverPoint = dist(rng);

    for (int i = 0; i <= crossoverPoint; i++) {
        for (uint32_t x = 0; x < offspring->weights[i].sizex; x++) {
            for (uint32_t y = 0; y < offspring->weights[i].sizey; y++) {
                offspring->weights[i].data[x][y] = b->weights[i].data[x][y];
            }
        }
    }

    return offspring;
}

model* arithmeticCrossover(uint32_t seed, model* a, model* b) {
    model* offspring = new model(a);

    std::mt19937 rng(seed);
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    for (uint32_t i = 0; i < offspring->numLayers - 1; i++) {
        for (uint32_t x = 0; x < offspring->weights[i].sizex; x++) {
            for (uint32_t y = 0; y < offspring->weights[i].sizey; y++) {
                double alpha = dist(rng);
                offspring->weights[i].data[x][y] = alpha * a->weights[i].data[x][y] + (1 - alpha) * b->weights[i].data[x][y];
            }
        }
    }

    return offspring;
}