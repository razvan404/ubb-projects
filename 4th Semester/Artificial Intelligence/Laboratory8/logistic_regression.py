import random
from math import exp

from numpy.linalg import inv
import numpy as np


def sigmoid(x):
    return 1 / (1 + exp(-x))


class MyStochasticLogisticRegression:
    def __init__(self):
        self.intercept_ = 0.0
        self.coef_ = []

    # use the gradient descent method
    # simple stochastic GD
    def fit(self, x: list, y: list, learning_rate: float = 0.001, no_epochs: int = 1000):
        self.coef_ = [random.random() for _ in range(len(x[0]) + 1)]
        for _ in range(no_epochs):
            for i in range(len(x)):
                y_computed = sigmoid(self.eval(x[i], self.coef_))
                crt_error = y_computed - y[i]
                for j in range(1, len(self.coef_)):
                    self.coef_[j] = self.coef_[j] - learning_rate * crt_error * x[i][j - 1]
                self.coef_[0] = self.coef_[0] - learning_rate * crt_error * 1

        self.intercept_ = self.coef_[0]
        self.coef_ = self.coef_[1:]

    def eval(self, xi: list, coef: list):
        yi = coef[0]
        for j in range(len(xi)):
            yi += coef[j + 1] * xi[j]
        return yi

    def predict_one_sample(self, sample_features: list):
        threshold = 0.5
        coefficients = [self.intercept_] + [c for c in self.coef_]
        computed_float_value = self.eval(sample_features, coefficients)
        computed01_value = sigmoid(computed_float_value)
        computed_label = 0 if computed01_value < threshold else 1
        return computed_label

    def predict(self, in_test):
        computed_labels = [self.predict_one_sample(sample) for sample in in_test]
        return computed_labels


class MyLogisticRegressionMultiLabel:
    def __init__(self, learning_rate: float = 0.001, no_epochs: int = 1000, gd_type: str = 'stochastic'):
        self.intercept_ = []
        self.coef_ = []
        self.__learning_rate = learning_rate
        self.__no_epochs = no_epochs
        if gd_type == 'stochastic':
            self.fit = self.fit_stochastic
        elif gd_type == 'batch':
            self.fit = self.fit_batch
        else:
            raise ValueError('Unknown GD type')

    def fit_stochastic(self, x, y):
        self.coef_ = []
        self.intercept_ = []
        labels = list(sorted(set(y)))
        for label in labels:
            coef = [random.random() for _ in range(len(x[0]) + 1)]
            for _ in range(self.__no_epochs):
                for i in range(len(x)):
                    y_computed = sigmoid(self.eval(x[i], coef))
                    crt_error = y_computed - 1 if y[i] == label else y_computed
                    for j in range(1, len(coef)):
                        coef[j] -= self.__learning_rate * crt_error * x[i][j - 1]
                    coef[0] -= self.__learning_rate * crt_error * 1
            self.intercept_.append(coef[0])
            self.coef_.append(coef[1:])

    def fit_batch(self, x, y):
        self.coef_ = []
        self.intercept_ = []
        labels = list(sorted(set(y)))
        for label in labels:
            coef = [random.random() for _ in range(len(x[0]) + 1)]
            for _ in range(self.__no_epochs):
                errors = [0] * len(coef)
                for i in range(len(x)):
                    y_computed = sigmoid(self.eval(x[i], coef))
                    crt_error = y_computed - 1 if y[i] == label else y_computed
                    for j in range(1, len(coef)):
                        errors[j] += crt_error * x[i][j - 1]
                    errors[0] += crt_error
                for i in range(len(coef)):
                    coef[i] -= self.__learning_rate * errors[i]
            self.intercept_.append(coef[0])
            self.coef_.append(coef[1:])

    def eval(self, xi: list, coef: list):
        yi = coef[0]
        for j in range(len(xi)):
            yi += coef[j + 1] * xi[j]
        return yi

    def predict_one_sample(self, sample_features: list):
        predictions = []
        for intercept, coefficient in zip(self.intercept_, self.coef_):
            computed_value = self.eval(sample_features, [intercept] + coefficient)
            predictions.append(sigmoid(computed_value))
        return predictions.index(max(predictions))

    def predict(self, in_test: list):
        computed_labels = [self.predict_one_sample(sample) for sample in in_test]
        return computed_labels
