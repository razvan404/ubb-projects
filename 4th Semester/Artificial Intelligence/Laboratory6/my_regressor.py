class MyLinearRegression:
    def __init__(self):
        self.intercept_ = 0.0
        self.coef_ = None
        self.computed_1D = False

    def fit(self, x: list, y: list):
        pass

    def predict(self, x: list):
        if isinstance(x[0], list):
            return [self.intercept_ + sum([self.coef_[i] * val[i] for i in range(len(self.coef_))]) for val in x]
        else:
            return [self.intercept_ + self.coef_[0] * val for val in x]


class MyLinearRegression1D(MyLinearRegression):
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


class MyLinearRegression2D(MyLinearRegression):
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

        if MyLinearRegression2D.__proportional_lists(x1, x2):
            regressor = MyLinearRegression1D()
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

        det_xtx = xtx[0][0] * MyLinearRegression2D.__get_minor_signed_determinant_3d_matrix(xtx, [0, 0]) + \
            xtx[0][1] * MyLinearRegression2D.__get_minor_signed_determinant_3d_matrix(xtx, [0, 1]) + \
            xtx[0][2] * MyLinearRegression2D.__get_minor_signed_determinant_3d_matrix(xtx, [0, 2])

        inv_det_xtx = 1 / det_xtx

        xtx_inv = [[MyLinearRegression2D.__get_minor_signed_determinant_3d_matrix(xtx, [j, i]) * inv_det_xtx
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
