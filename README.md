# neuralnetlib
neuralnetlib is a lightweight C++ library designed for performing both reinforcement learning and genetic algorithm tasks.

Neural networks are almost always obscured for beginners because of the terminology used and lack of simplistic explanations.

This library aims to make a neural network library that is very easy to use natively in C++ and requires little to no understanding of the underlying mechanics of a neural network.

# modular
I have designed the library to be as customizeable and modular as possible. If you want to add your own function for cost, activation, initialization, recombination or mutation all that is required is for you to develop one function that follows a very standard API.

Right now I support a number of different standard functions for each of these tasks.

For activation I support
sigmoid, tanh, ReLU and leakyReLU

For cost I support
quadratic cost

For initialization I support
a
