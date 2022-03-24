# Inspired from https://towardsdatascience.com/how-to-build-your-own-neural-network-from-scratch-in-python-68998a08e4f6

import numpy as np
import pandas as pd
from datetime import datetime


def sigmoid(t):
    return 1/(1+np.exp(-t))


def sigmoid_deriviate(p):
    return p * (1 - p)


class NeuralNetwork:
    def __init__(self, x, y):
        self.input = x
        # self.input.shape[1] is the number of columns
        self.weights1 = np.random.rand(self.input.shape[1], 4)
        self.weights2 = np.random.rand(4, 1)
        self.y = y
        self.output = np.zeros(self.y.shape)

    def feedforward(self):
        self.layer1 = sigmoid(np.dot(self.input, self.weights1))
        self.output = sigmoid(np.dot(self.layer1, self.weights2))

    def backpropagate(self):
        error_value = 2*(self.y - self.output)
        sigmoid_d_output = sigmoid_deriviate(self.output)
        sigmoid_d_layer1 = sigmoid_deriviate(self.layer1)
        error_value_mult_sigmoid_d_output = error_value * sigmoid_d_output

        d_weights2 = np.dot(
            self.layer1.T, error_value_mult_sigmoid_d_output)
        d_weights1 = np.dot(
            self.input.T,
            (np.dot(error_value_mult_sigmoid_d_output, self.weights2.T) * sigmoid_d_layer1))

        # Updating the weights with the deriviate (slope) of the loss function
        self.weights1 += d_weights1
        self.weights2 += d_weights2


X = np.array([
    [0, 0, 1],
    [0, 1, 1],
    [1, 0, 1],
    [1, 1, 1]])
Y = np.array([[0], [1], [1], [0]])

neural_network = NeuralNetwork(X, Y)
delta1 = datetime.now()
for i in range(1500000):
    neural_network.feedforward()
    neural_network.backpropagate()
delta2 = datetime.now()
print(delta2-delta1)
print(neural_network.output)
