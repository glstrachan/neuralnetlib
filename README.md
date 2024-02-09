
# NeuralNetLib

`NeuralNetLib` is a lightweight C++ library designed for performing both reinforcement learning and genetic algorithm tasks.

## Introduction

Neural networks are almost always obscured for beginners because of the terminology used and lack of simplistic explanations.

This library aims to make a neural network library that is very easy to use natively in C++ and requires little to no understanding of the underlying mechanics of a neural network.

## Key Features

- **Ease of Use**: Tailored for simplicity, enabling users to leverage neural network functionalities natively in C++ with ease.
- **Modularity**: Designed with customization and modularity in mind, allowing users to easily extend and adapt the library to fit their specific needs.

## Customization

The library is built to be highly customizable. Users can add their own functions for various tasks such as cost calculation, activation, initialization, recombination, or mutation by simply developing a function that adheres to a straightforward API. The library currently includes a variety of standard functions for these tasks, serving as excellent references for implementing custom functions.

### Supported Functions

- **Activation Functions**:
  - Sigmoid
  - Tanh
  - ReLU
  - Leaky ReLU

- **Cost Function**:
  - Quadratic cost

- **Initialization Methods**:
  - Uniform random initialization
  - Xavier Glorot initialization
  - He initialization

- **Mutation Strategies**:
  - Random resetting
  - Gaussian mutation
  - Polynomial mutation
  - Weight shuffling

- **Recombination Methods**:
  - Uniform crossover
  - Single point crossover
  - Arithmetic crossover


## Detailed Example Breakdown

This section breaks down the process of setting up, training, and evaluating a neural network model using `NeuralNetLib`. Each step is explained to provide clarity on how the library functions.

### Step 1: Include Necessary Headers

First, include the necessary header files that provide functionalities for training, data handling, activation functions, and cost calculations.

```cpp
#include "train.hh"
#include "trainingdata.hh"
#include "activation.hh"
#include "cost.hh"
#include <stdlib.h>
#include <iostream>
```

### Step 2: Initialize the Environment

Set up the main environment, define input and output sizes, and initialize the random seed for reproducibility.

```cpp
int main() {
    uint32_t inputSize = 3;
    uint32_t outputSize = 1;
    srand(12345); // Seed for random number generator
}
```

### Step 3: Create Training and Validation Data

Generate training and validation data based on the function `w(x,y,z) = 3x^3 - 2y^2 + z`. Allocate memory for input and output vectors and populate them with values.

```cpp
// Training data
uint32_t trainingSize = 10000;
vector* inputs = (vector*)malloc(trainingSize * sizeof(vector));
vector* outputs = (vector*)malloc(trainingSize * sizeof(vector));
// Populate training data...
// Validation data
uint32_t validationSize = 10000;
vector* vInputs = (vector*)malloc(validationSize * sizeof(vector));
vector* vOutputs = (vector*)malloc(validationSize * sizeof(vector));
// Populate validation data...
```

### Step 4: Define the Model

Specify the structure of the neural network model, including the number of layers and the size of each layer. Initialize weights using a chosen method.

```cpp
uint32_t numLayers = 4;
uint32_t* layersizes = (uint32_t*)malloc(numLayers * sizeof(uint32_t));
layersizes[0] = 3; // Input layer
layersizes[1] = 16; // Hidden layer 1
layersizes[2] = 16; // Hidden layer 2
layersizes[3] = 1; // Output layer
model m(numLayers, layersizes);
m.initWeights(HeInit, 834939); // Initialize weights
```

### Step 5: Train the Model

Use the training function to train the model on the provided training and validation datasets with specified parameters such as activation function, cost function, batch size, number of epochs, learning rate, and seed for weight initialization.

```cpp
train(&m, &data, &vData, leakyReLU, quadraticCost, trainingSize / 70, 5000, 0.05, 9699);
```

### Step 6: Evaluate the Model

Evaluate the model's performance by testing it on new data and comparing the predicted output with the expected output. Calculate and display the average cost to assess the model's accuracy.

```cpp
double avgcost = 0.0;
// Loop to evaluate model on new data points and compute average cost
```

### Step 7: Cleanup

Free up allocated memory to prevent memory leaks.

```cpp
// Free allocated memory for inputs, outputs, and other dynamically allocated resources
```

### Step 8: Conclude the Program

End the `main` function and return an exit status.

```cpp
return 0;
}
```

This breakdown provides a step-by-step guide to understanding and implementing a neural network model using `NeuralNetLib`. Each step is crucial for setting up the environment, preparing data, defining the model, training, and evaluating its performance.

### Step 9: Save the Model

Once the model is trained and evaluated, you can save its state to a file for later use. This is particularly useful for deploying the model in applications or continuing training at a later time.

```cpp
// Assuming `m` is your trained model instance
char* modelFileName = "trained_model.nn";
m.save(modelFileName);
```

This code snippet demonstrates how to save the model to a file named "trained_model.nn". You can choose any file name or extension that suits your project's conventions.

### Step 10: Load the Model

To use the previously saved model, you can load it from the file. This is essential for making predictions or further refining the model without having to retrain from scratch.

```cpp
// Assuming `m` is an instance of your model structure
char* modelFileName = "trained_model.nn";
m.load(modelFileName);
```

This code snippet demonstrates how to load the model from the "trained_model.nn" file. Ensure that the model structure (`m`) is compatible with the saved model state.
