#include "train.hh"

bool train(model* m, trainingData* data, activationType* a, uint32_t batchSize, uint32_t epochs, double rate, u_int32_t seed) {
    if(batchSize > data -> size || rate <= 0.0) return false;

    for(int i = 0; i < epochs; i++) {
        std::vector<int> indices;

        for(int j = 0; j < data -> size; i++) {
            indices.push_back(j);
        }

        std::vector<std::vector<int>> miniBatches;

        for(int j = 0; j < ceil((data -> size) / batchSize) * batchSize; j++) {

        }
    }
    // Divide up our indices into groups of size batchSize

    // for every mini batch
    // Pass on group of indices to a new function that will 
    // evaluate every input and compare it to every output
    // from this gradients will be computed for every weight and bias
    // the (gradient / batchSize) is added to a model that represents the gradient from the minibatch
    // Every weight and bias is adjusted by the gradient * learning rate (or some combination of this)
}

void processBatch();