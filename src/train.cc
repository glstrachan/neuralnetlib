#include "train.hh"

bool train(model* m, trainingData* data, activationType* a, uint32_t batchSize, uint32_t epochs, double rate, u_int32_t seed) {
    if(batchSize > data -> size || rate <= 0.0) return false;

    for(int i = 0; i < epochs; i++) {
        std::vector<int> indices;

        for(int j = 0; j < data -> size; i++) {
            indices.push_back(j);
        }

        std::vector<std::vector<int>> miniBatches;

        // Extra training data will be appended to other minibatches
        uint32_t batches = (u_int32_t)std::floor((double)(data -> size) / (double)batchSize);
        u_int32_t newBatchSize = (u_int32_t)std::floor((double)(data -> size) / (double)batches);

        srand(seed);

        for(int j = 0; j < batches; j++) {
            std::vector<int> batchIndices;

            if(j == batches - 1) { // Last miniBatch may have more
                newBatchSize += (data -> size % newBatchSize); 
            }

            for(int k = 0; k < newBatchSize; k++) {
                uint32_t r = rand() %  indices.size();
                batchIndices.push_back(indices[r]);
                indices.erase(indices.begin() + r);
            }

            miniBatches.push_back(batchIndices);
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