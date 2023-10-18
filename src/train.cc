#include "train.hh"

bool train(model* m, trainingData* data, activationType* a, uint32_t batchSize, uint32_t epochs, double rate, u_int32_t seed) {
    if(batchSize > data -> size || rate <= 0.0) return false;

    srand(seed);

    for(int i = 0; i < epochs; i++) {
        std::vector<int> indices;

        for(int j = 0; j < data -> size; i++) {
            indices.push_back(j);
        }

        std::vector<std::vector<int>> miniBatches;

        // Extra training data will be appended to other minibatches
        uint32_t batches = (u_int32_t)std::floor((double)(data -> size) / (double)batchSize);
        u_int32_t newBatchSize = (u_int32_t)std::floor((double)(data -> size) / (double)batches);

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

        // Done making minibatches -> Start gradient descent

        gradient grad(m); // Using a model to represent the gradient for a batch
        gradient subGrad = m; // a gradient for a single training instance

        // Calculate all sub gradients for a minibatch
        // Append them scaled to grad
        // Add the gradient to the model
        // Repeat

        for(int j = 0; j < batches; j++) {
            // Reset the gradient and subgradient to have all weights and biases 0
            grad.reset();

            for(int k = 0; k < miniBatches[j].size(); k++) {
                // Fill in the subGrad here

                // Scale subgrad
                // Add the subgradient onto the gradient
            }
            
            // Adjust the model based on the gradient and the learning rate
            // Show the cost of the current model to the user
        }
    }

    return true;
}