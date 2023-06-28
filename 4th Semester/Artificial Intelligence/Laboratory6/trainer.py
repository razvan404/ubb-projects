import numpy as np
from matplotlib import pyplot as plt

from data_set import DataSet, DataSet2D


class LinearTrainer:
    def __init__(self, data_set: DataSet, regressor):
        self.__training_data, self.__validation_data = data_set.split_into_training_and_validation()
        self.__regressor = regressor

    def get_learnt_model(self):
        elements = [[el] for el in self.__training_data.input_data]
        self.__regressor.fit(elements, self.__training_data.output_data)
        return self.__regressor.intercept_, self.__regressor.coef_[0]

    def plot_results(self):
        w0 = self.__regressor.intercept_
        w1 = self.__regressor.coef_[0]

        no_points = 1000
        val = min(self.__training_data.input_data)
        step = (max(self.__training_data.input_data) - val) / no_points

        xref = [val + step * i for i in range(no_points)]
        yref = [w0 + w1 * el for el in xref]

        plt.plot(xref, yref, 'b-', label='learnt model')
        self.__training_data.plot_data_linearity(given_label='training data', title='training data vs learnt model')

    def plot_predicted_results(self):
        computed_validation_outputs = self.__regressor.predict([[x] for x in self.__validation_data.input_data])

        plt.plot(self.__validation_data.input_data, computed_validation_outputs, 'yo', label='computed test data')
        self.__validation_data.plot_data_linearity(symbol='g^', given_label='real test data',
                                                   title='computed validation and real validation data')

    def compute_error(self) -> float:
        computed_validation_outputs = self.__regressor.predict([[x] for x in self.__validation_data.input_data])

        error = 0.0
        for t1, t2 in zip(computed_validation_outputs, self.__validation_data.output_data):
            error += (t1 - t2) ** 2
        error /= len(self.__validation_data.output_data)
        return error


class LinearTrainer2D:
    def __init__(self, regressor, data_set: DataSet2D = None, training_set: DataSet2D = None,
                 validation_set: DataSet2D = None):
        if data_set is not None:
            self.__training_data, self.__validation_data = data_set.split_into_training_and_validation()
        else:
            self.__training_data, self.__validation_data = training_set, validation_set
        self.__regressor = regressor

    def get_learnt_model(self):
        elements = [[el1, el2] for el1, el2 in zip(self.__training_data.input_data1, self.__training_data.input_data2)]
        self.__regressor.fit(elements, self.__training_data.output_data)
        return self.__regressor.intercept_, self.__regressor.coef_[0], self.__regressor.coef_[1]

    def plot_results(self):
        w0 = self.__regressor.intercept_
        w1 = self.__regressor.coef_[0]
        w2 = self.__regressor.coef_[1]

        min1 = min(self.__training_data.input_data1)
        max1 = max(self.__training_data.input_data1)

        min2 = min(self.__training_data.input_data2)
        max2 = max(self.__training_data.input_data2)

        ax = plt.axes(projection='3d')
        xref1, xref2 = np.meshgrid(np.arange(min1, max1 + 0.1, max1 - min1),
                                   np.arange(min2, max2 + 0.1, max2 - min2))
        yref = xref2 * w2 + xref1 * w1 + w0
        ax.plot_surface(xref1, xref2, yref, alpha=0.5, label='learnt model')
        self.__training_data.plot_data_linearity(given_label='training data',
                                                 title='training data vs learnt model', ax=ax,
                                                 surface_label='learnt model')
        plt.show()

    def plot_predicted_results(self):
        computed_validation_outputs = self.__regressor.predict([[x1, x2] for x1, x2 in
                                                                zip(self.__validation_data.input_data1,
                                                                    self.__validation_data.input_data2)])
        ax = plt.axes(projection='3d')

        ax.plot3D(self.__validation_data.input_data1, self.__validation_data.input_data2, computed_validation_outputs,
                  'yo', label='computed test data')

        self.__validation_data.plot_data_linearity(symbol='g^', given_label='real test data',
                                                   title='computed validation and real validation data', ax=ax)

    def compute_error(self) -> float:
        computed_validation_outputs = self.__regressor.predict([[x1, x2] for x1, x2 in
                                                                zip(self.__validation_data.input_data1,
                                                                    self.__validation_data.input_data2)])
        error = 0.0
        for t1, t2 in zip(computed_validation_outputs, self.__validation_data.output_data):
            error += (t1 - t2) ** 2
        error /= len(self.__validation_data.output_data)
        return error
