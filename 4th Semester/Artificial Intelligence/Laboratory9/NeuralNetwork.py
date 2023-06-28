import numpy as np

from keras.models import Sequential
from keras.layers import Dense, Conv2D, MaxPool2D, Flatten, Dropout
import tensorflow as tf

from SepiaFilter import IMAGE_SIZE


class NeuralNetwork:
    def __init__(self, hidden_layer_size: int = 12, max_iter: int = 5000, learning_rate: float = 0.001):
        self.__hidden_layer_size = hidden_layer_size
        self.__max_iter = max_iter
        self.__learning_rate = learning_rate
        self.__weights = []

    @staticmethod
    def __softmax(x: list):
        exp_vector = np.exp(x)
        return exp_vector / exp_vector.sum(axis=1, keepdims=True)

    @staticmethod
    def __sigmoid(x: float):
        return 1 / (1 + np.exp(-x))

    @staticmethod
    def __sigmoid_derivative(sigmoid_x: float):
        return sigmoid_x * (1 - sigmoid_x)

    def fit(self, x: list, y: list):
        no_features = len(x[0])
        no_outputs = len(set(y))
        x = np.array(x)
        new_y = np.zeros((len(y), no_outputs))
        for i in range(len(y)):
            new_y[i][y[i]] = 1
        y = new_y
        inp_hid_weights = np.random.rand(no_features, self.__hidden_layer_size)
        inp_hid_bias = np.random.randn(self.__hidden_layer_size)
        hid_out_weights = np.random.rand(self.__hidden_layer_size, no_outputs)
        hid_out_bias = np.random.randn(no_outputs)
        for _ in range(self.__max_iter):
            # forward propagation
            hid_layer_y = np.dot(x, inp_hid_weights) + inp_hid_bias
            hid_layer_y = self.__sigmoid(hid_layer_y)

            out_layer_y = np.dot(hid_layer_y, hid_out_weights) + hid_out_bias
            out_layer_y = self.__softmax(out_layer_y)

            # backpropagation
            err = out_layer_y - y
            out_err_gradient = err
            hid_err_gradient = np.dot(out_err_gradient, hid_out_weights.T) * self.__sigmoid_derivative(hid_layer_y)

            inp_hid_weights -= self.__learning_rate * np.dot(x.T, hid_err_gradient)
            inp_hid_bias -= self.__learning_rate * np.sum(hid_err_gradient, axis=0)

            hid_out_weights -= self.__learning_rate * np.dot(hid_layer_y.T, out_err_gradient)
            hid_out_bias -= self.__learning_rate * np.sum(out_err_gradient, axis=0)

        self.__weights = [inp_hid_weights, inp_hid_bias, hid_out_weights, hid_out_bias]

    def predict(self, x: list):
        inp_hid_y = np.dot(x, self.__weights[0]) + self.__weights[1]
        hid_y = self.__sigmoid(inp_hid_y)
        hid_out_y = np.dot(hid_y, self.__weights[2]) + self.__weights[3]
        out_y = self.__softmax(hid_out_y)
        out_computed = [list(output).index(max(output)) for output in out_y]
        return out_computed


def get_cnn_classifier():
    model = Sequential()
    model.add(Conv2D(32, (3, 3), padding='same', activation='relu', input_shape=(IMAGE_SIZE, IMAGE_SIZE, 3)))
    model.add(MaxPool2D())
    model.add(Conv2D(64, (3, 3), padding='same', activation='relu'))
    model.add(MaxPool2D())
    model.add(Dropout(0.4))
    model.add(Flatten())
    model.add(Dense(2, activation='softmax'))
    model.compile(optimizer=tf.keras.optimizers.Adam(learning_rate=0.001), loss=tf.keras.losses.
                  SparseCategoricalCrossentropy(from_logits=True), metrics=['accuracy'])
    return model
