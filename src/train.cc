#include "train.hh"

bool train(model* m, trainingData* data, trainingData* validation, double (*activation)(double z, double a, bool prime), double (*cost)(double expected, double actual, bool prime), uint32_t batchSize, uint32_t epochs, double rate, uint32_t seed) {
    if(batchSize > data -> size || rate <= 0.0) return false;

    srand(seed);

    for(int i = 0; i < epochs; i++) {
        printf("\n\nEpoch %d:\n", i + 1);

        std::vector<int> indices;

        for(int j = 0; j < data -> size; j++) {
            indices.push_back(j);
        }

        std::vector<std::vector<int>> miniBatches;

        // Extra training data will be appended to other minibatches
        uint32_t batches = (uint32_t)std::floor((double)(data -> size) / (double)batchSize);
        uint32_t newBatchSize = (uint32_t)std::floor((double)(data -> size) / (double)batches);
        
        for(int j = 0; j < batches; j++) {
            std::vector<int> batchIndices;

            if(j == batches - 1) { // Last miniBatch may have more
                newBatchSize += (data -> size % newBatchSize); 
            }

            for(int k = 0; k < newBatchSize; k++) {
                uint32_t r = rand() % indices.size();
                batchIndices.push_back(indices[r]);
                indices.erase(indices.begin() + r);
            }

            miniBatches.push_back(batchIndices);
        }

        // Done making minibatches -> Start (stochastic) gradient descent

        // TODO: Optimize all this stuff so it isn't in a model
        model grad(m);           // Gradient = Model
        model subGrad(m);        // Single instance gradient
        model weightedInputs(m); // (Z), weighted inputs before activation
        model errors(m);         // Errors for all layers

        for(int j = 0; j < batches; j++) {
            grad.zero(); // Reset the gradient to have all weights and biases 0

            double miniBatchError = 0.0;

            for(int k = 0; k < miniBatches[j].size(); k++) {
                // Fill in the subGrad here
                m -> setInput(&(data -> inputs[miniBatches[j][k]])); 

                // Feed forward and also get the weighted inputs
                for(int l = 1; l < m -> numLayers; l++) { // Modified evaluation
                    multiply(&(m -> weights[l - 1]), &(m -> layers[l - 1]), &(weightedInputs.layers[l])); 

                    for(int n = 0; n < m -> layers[l].size; n++) {
                        m -> layers[l].data[n] = activation(weightedInputs.layers[l].data[n] + m -> biases[l - 1].data[n], 0.01, false);
                    }
                }

                // Compute Output Layer error
                double avgError = 0.0;

                for(int l = 0; l < m -> layers[m -> numLayers - 1].size; l++) {
                    errors.layers[m -> numLayers - 1].data[l] = cost(data -> outputs[miniBatches[j][k]].data[l], m -> layers[m -> numLayers - 1].data[l], true) * 
                    activation(weightedInputs.layers[m -> numLayers - 1].data[l], 0.01, true);

                    avgError += (errors.layers[m -> numLayers - 1].data[l]) / (m -> layers[m -> numLayers - 1].size);
                }

                miniBatchError += avgError / miniBatches[j].size();

                // Compute hidden Layer error
                for(int l = m -> numLayers - 2; l >= 0; l--) {
                    vector* reverse = (vector*)malloc(sizeof(vector));

                    multiplyT(&(m -> weights[l]), &errors.layers[l + 1], reverse);

                    for(int n = 0; n < errors.layers[l].size; n++) {
                        errors.layers[l].data[n] = (reverse -> data[n]) * activation(weightedInputs.layers[l].data[n], 0.01, true);
                    }
                }

                // Set bias gradient (same as error at same index but next layer)
                for(int l = 0; l < m -> numLayers - 1; l++) {
                    for(int n = 0; n < m -> biases[l].size; n++) {
                        subGrad.biases[l].data[n] = errors.layers[l + 1].data[n];
                    }
                }

                // Set weight gradient
                for(int l = 0; l < m -> numLayers - 1; l++) {
                    for(int n = 0; n < m -> weights[l].sizex; n++) {
                        for(int o = 0; o < m -> weights[l].sizey; o++) {
                            subGrad.weights[l].data[n][o] = (m -> layers[l].data[n]) * errors.layers[l + 1].data[o];
                        }
                    }
                }

                grad.addModel(&subGrad, 1.0 / (double)miniBatches[j].size()); // Add the scaled subgradient onto the gradient
            }

            printf("\rMini-batch %d/%d - Loss: %5.2lf", j + 1, batches, miniBatchError);
            
            m -> addModel(&grad, -rate); // Model = gradient * rate
        }

        // TODO: Show the cost of the current model to the user (on a validation set)
        double avgError = 0.0;
        double avgCost = 0.0;

        for(int j = 0; j < validation -> size; j++) {
            m -> setInput(&(validation -> inputs[j]));
            m -> evaluate(activation);

            double instanceError = 0.0;
            double instanceCost = 0.0;

            for(int k = 0; k < m -> layers[m -> numLayers - 1].size; k++) {
                instanceError += (cost(validation -> outputs[j].data[k], m -> layers[m -> numLayers - 1].data[k], true) / m -> layers[m -> numLayers - 1].size);
                instanceCost += (cost(validation -> outputs[j].data[k], m -> layers[m -> numLayers - 1].data[k], false) / m -> layers[m -> numLayers - 1].size);
            }

            avgError += (instanceError / (validation -> size));
            avgCost += (instanceCost / (validation -> size));
        }

        printf("\nValidation Loss: %5.2lf\nValidation Cost: %5.2lf\n", avgError, avgCost);
    }

    return true;
}