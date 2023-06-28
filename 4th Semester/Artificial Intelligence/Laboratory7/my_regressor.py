import random
from statistics import mean


class MyRegression:
    def __init__(self):
        self.intercept_ = 0.0
        self.coef_ = None

    def fit(self, x: list, y: list):
        pass

    def predict(self, x: list):
        pass


class MyLinearRegression1Input(MyRegression):
    def fit(self, x: list, y: list):
        sums = {
            '1': len(x),
            'x': sum(e[0] for e in x),
            'y': sum(y),
            'x^2': sum(e[0] ** 2 for e in x),
            'xy': sum(e[0] * l for e, l in zip(x, y))
        }
        self.coef_ = [(sums['1'] * sums['xy'] - sums['x'] * sums['y'])
                      / (sums['1'] * sums['x^2'] - sums['x'] * sums['x'])]
        self.intercept_ = (sums['y'] - self.coef_[0] * sums['x']) / sums['1']

    def predict(self, x: list):
        return [self.intercept_ + self.coef_[0] * e[0] for e in x]


class MyLinearRegression2Input(MyRegression):
    def __init__(self):
        super().__init__()
        self.computed_1D = False

    @staticmethod
    def __get_minor_signed_determinant_3d_matrix(matrix: list, nodes: [int, int]):
        return matrix[(nodes[0] + 1) % 3][(nodes[1] + 1) % 3] * matrix[(nodes[0] + 2) % 3][(nodes[1] + 2) % 3] - \
                     matrix[(nodes[0] + 1) % 3][(nodes[1] + 2) % 3] * matrix[(nodes[0] + 2) % 3][(nodes[1] + 1) % 3]

    @staticmethod
    def __proportional_lists(x1: list, x2: list):
        q = x1[0] / x2[0]
        for i in range(1, len(x1)):
            if not (abs(x1[i] - q * x2[i]) < 0.0001):
                return False
        return True

    def fit(self, x: list, y: list):
        x1 = [e[0] for e in x]
        x2 = [e[1] for e in x]

        if MyLinearRegression2Input.__proportional_lists(x1, x2):
            regressor = MyLinearRegression1Input()
            regressor.fit([[e] for e in x1], y)
            self.intercept_ = regressor.intercept_
            self.coef_ = regressor.coef_ + [0.0]
            self.computed_1D = True
            return

        sums = {
            '1': len(x),
            'x1': sum(x1),
            'x2': sum(x2),
            'x1^2': sum([e ** 2 for e in x1]),
            'x2^2': sum([e ** 2 for e in x2]),
            'x1x2': sum([e[0] * e[1] for e in x])
        }

        xtx = [[sums['1'], sums['x1'], sums['x2']],
               [sums['x1'], sums['x1^2'], sums['x1x2']],
               [sums['x2'], sums['x1x2'], sums['x2^2']]]

        det_xtx = xtx[0][0] * MyLinearRegression2Input.__get_minor_signed_determinant_3d_matrix(xtx, [0, 0]) + \
                  xtx[0][1] * MyLinearRegression2Input.__get_minor_signed_determinant_3d_matrix(xtx, [0, 1]) + \
                  xtx[0][2] * MyLinearRegression2Input.__get_minor_signed_determinant_3d_matrix(xtx, [0, 2])

        inv_det_xtx = 1 / det_xtx

        xtx_inv = [[MyLinearRegression2Input.__get_minor_signed_determinant_3d_matrix(xtx, [j, i]) * inv_det_xtx
                    for i in range(3)] for j in range(3)]

        before_y = [[0] * len(x) for _ in range(3)]

        for j in range(len(x)):
            for i in range(3):
                before_y[i][j] = xtx_inv[i][0] + xtx_inv[i][1] * x[j][0] + xtx_inv[i][2] * x[j][1]

        final = [0] * 3
        for i in range(3):
            for j in range(len(x)):
                final[i] += y[j] * before_y[i][j]

        self.intercept_ = final[0]
        self.coef_ = final[1:]

    def predict(self, x: list):
        if self.computed_1D:
            return [self.intercept_ + self.coef_[0] * e[0] for e in x]
        return [self.intercept_ + self.coef_[0] * e[0] + self.coef_[1] * e[1] for e in x]


class MySGDRegression(MyRegression):
    def __init__(self, learning_rate: float = 0.001, no_epochs: int = 1000):
        super().__init__()
        self.learning_rate = learning_rate
        self.no_epochs = no_epochs

    def fit(self, x: list, y: list):
        self.coef_ = [random.random() for _ in range(len(x[0]) + 1)]  # +1 for the bias
        # self.coef_ = [random.random() for _ in range(len(x[0]) + 1)]    #beta or w coefficients
        for _ in range(self.no_epochs):
            # TBA: shuffle the trainind examples in order to prevent cycles
            for i in range(len(x)): # for each sample from the training data
                y_pred = self.eval(x[i])        # estimate the output
                error = y_pred - y[i]           # compute the error for the current sample
                for j in range(0, len(x[0])):   # update the coefficients
                    self.coef_[j] = self.coef_[j] - self.learning_rate * error * x[i][j]
                self.coef_[len(x[0])] = self.coef_[len(x[0])] - self.learning_rate * error

        self.intercept_ = self.coef_[-1]
        self.coef_ = self.coef_[:-1]

    def eval(self, xi):
        yi = self.coef_[-1]
        for j in range(len(xi)):
            yi += self.coef_[j] * xi[j]
        return yi

    def predict(self, x: list):
        return [self.intercept_ + sum([self.coef_[i] * e[i] for i in range(len(e))]) for e in x]


class MyBatchGDRegression(MyRegression):
    def __init__(self, learning_rate: float = 0.001, no_epochs: int = 1000):
        super().__init__()
        self.learning_rate = learning_rate
        self.no_epochs = no_epochs

    def fit(self, x: list, y: list):
        self.coef_ = [random.random() for _ in range(len(x[0]) + 1)]
        for _ in range(self.no_epochs):
            errors = []
            for i in range(len(x)):
                y_computed = self.eval(x[i])
                errors.append(y_computed - y[i])
            error = mean(errors)
            for i in range(len(x)):
                for j in range(0, len(x[0])):
                    self.coef_[j] = self.coef_[j] - self.learning_rate * error * x[i][j]
                self.coef_[len(x[0])] = self.coef_[len(x[0])] - self.learning_rate * error * 1

        self.intercept_ = self.coef_[-1]
        self.coef_ = self.coef_[:-1]

    def eval(self, xi):
        yi = self.coef_[-1]
        for j in range(len(xi)):
            yi += self.coef_[j] * xi[j]
        return yi

    def predict(self, x: list):
        return [self.intercept_ + sum([self.coef_[i] * e[i] for i in range(len(e))]) for e in x]
