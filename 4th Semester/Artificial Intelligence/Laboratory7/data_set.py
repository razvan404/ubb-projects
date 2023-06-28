import csv
import matplotlib.pyplot as plt
import matplotlib as mpl
import numpy as np
from sklearn.preprocessing import StandardScaler


def normalise(train_data, validate_data):
    scaler = StandardScaler()
    if not isinstance(train_data[0], list):
        train_data = [[i] for i in train_data]
        validate_data = [[i] for i in validate_data]

        scaler.fit(train_data)
        normalised_train_data = scaler.transform(train_data)
        normalised_validate_data = scaler.transform(validate_data)

        normalised_train_data = [i[0] for i in normalised_train_data]
        normalised_validate_data = [i[0] for i in normalised_validate_data]
    else:
        scaler.fit(train_data)
        normalised_train_data = scaler.transform(train_data)
        normalised_validate_data = scaler.transform(validate_data)

    return normalised_train_data, normalised_validate_data


class DataSet1Input:
    def __init__(self, input_column: str, output_column: str,
                 file_name: str = None,
                 input_data: list = None, output_data: list = None):
        self.__input_column = input_column
        self.__output_column = output_column

        if file_name is not None:
            data = []
            data_names = []
            with open(file_name) as csv_file:
                csv_reader = csv.reader(csv_file, delimiter=',')
                for row in csv_reader:
                    if not data_names:
                        data_names = row
                    else:
                        data.append(row)
            selected_variable = data_names.index(input_column)
            self.__input_data = [float(data[i][selected_variable]) if data[i][selected_variable] != ''
                                 else 0 for i in range(len(data))]
            selected_output = data_names.index(output_column)
            self.__output_data = [float(data[i][selected_output]) if data[i][selected_output] != ''
                                  else 0 for i in range(len(data))]
        else:
            self.__input_data = input_data
            self.__output_data = output_data

        self.__training_set = None
        self.__validation_set = None

    @property
    def input_data(self):
        return self.__input_data

    @property
    def output_data(self):
        return self.__output_data

    @staticmethod
    def plot_data_histogram(data: list, column_name: str):
        plt.hist(data, 10)
        plt.title(f'Histogram of {column_name}')
        plt.show()

    def plot_histograms(self):
        DataSet1Input.plot_data_histogram(self.__input_data, self.__input_column)
        DataSet1Input.plot_data_histogram(self.__output_data, self.__output_column)

    def plot_data_linearity(self, symbol: str | None = None, given_label: str | None = None,
                            title: str | None = None, show_plot: bool = True):
        if symbol is None:
            symbol = 'ro'

        if given_label is None:
            given_label = self.__output_column

        if title is None:
            title = f'{self.__input_column} vs {self.__output_column}'

        plt.plot(self.__input_data, self.__output_data, symbol, label=given_label)
        plt.xlabel(self.__input_column)
        plt.ylabel(self.__output_column)
        plt.title(title)
        plt.legend()

        if show_plot:
            plt.show()

    def split_into_training_and_validation(self, plot: bool = False,
                                           title: str = 'training data vs validation data'):
        if self.__training_set is None or self.__validation_set is None:
            indexes = [i for i in range(len(self.__input_data))]
            training_sample = np.random.choice(indexes, int(0.8 * len(self.__input_data)), replace=False)
            validation_sample = [i for i in indexes if i not in training_sample]

            training_inputs = [self.__input_data[i] for i in training_sample]
            training_outputs = [self.__output_data[i] for i in training_sample]

            validation_inputs = [self.__input_data[i] for i in validation_sample]
            validation_outputs = [self.__output_data[i] for i in validation_sample]

            self.__training_set = DataSet1Input(self.__input_column, self.__output_column,
                                                input_data=training_inputs, output_data=training_outputs)
            self.__validation_set = DataSet1Input(self.__input_column, self.__output_column,
                                                  input_data=validation_inputs, output_data=validation_outputs)

        if plot:
            self.__training_set.plot_data_linearity(given_label='training data', show_plot=False)
            self.__validation_set.plot_data_linearity(symbol='g^', given_label='validation data',
                                                      title=title)

        return self.__training_set, self.__validation_set

    def apply_normalisation(self):
        self.split_into_training_and_validation()

        train_inputs, validate_inputs = normalise(self.__training_set.input_data, self.__validation_set.input_data)
        train_outputs, validate_outputs = normalise(self.__training_set.output_data, self.__validation_set.output_data)

        self.__training_set = DataSet1Input(self.__input_column, self.__output_column,
                                            input_data=train_inputs, output_data=train_outputs)
        self.__validation_set = DataSet1Input(self.__input_column, self.__output_column,
                                              input_data=validate_inputs, output_data=validate_outputs)

    def clear_training_and_validation_cache(self):
        self.__training_set = None
        self.__validation_set = None


class DataSet2Inputs:
    def __init__(self, input_column1: str, input_column2: str, output_column: str, file_name: str | None = None,
                 input_data1: list = None, input_data2: list = None, output_data: list = None):
        self.__input_column1 = input_column1
        self.__input_column2 = input_column2
        self.__output_column = output_column

        if file_name is not None:
            data = []
            data_names = []
            with open(file_name) as csv_file:
                csv_reader = csv.reader(csv_file, delimiter=',')
                for row in csv_reader:
                    if not data_names:
                        data_names = row
                    else:
                        data.append(row)
            selected_variable1 = data_names.index(input_column1)
            self.__input_data1 = [float(data[i][selected_variable1] if data[i][selected_variable1] != '' else 0)
                                  for i in range(len(data))]

            selected_variable2 = data_names.index(input_column2)
            self.__input_data2 = [float(data[i][selected_variable2] if data[i][selected_variable2] != '' else 0)
                                  for i in range(len(data))]

            selected_output = data_names.index(output_column)
            self.__output_data = [float(data[i][selected_output] if data[i][selected_output != ''] else 0)
                                  for i in range(len(data))]

        else:
            self.__input_data1 = input_data1
            self.__input_data2 = input_data2
            self.__output_data = output_data

        self.__training_set = None
        self.__validation_set = None

    @property
    def input_data1(self):
        return self.__input_data1

    @property
    def input_data2(self):
        return self.__input_data2

    @property
    def output_data(self):
        return self.__output_data

    def plot_histograms(self):
        DataSet1Input.plot_data_histogram(self.__input_data1, self.__input_column1)
        DataSet1Input.plot_data_histogram(self.__input_data2, self.__input_column2)
        DataSet1Input.plot_data_histogram(self.__output_data, self.__output_column)

    def plot_data_linearity(self, symbol: str | None = None, given_label: str | None = None,
                            title: str | None = None, show_plot: bool = True, ax=None, surface_label=None):
        if symbol is None:
            symbol = 'ro'

        if given_label is None:
            given_label = self.__output_column

        if title is None:
            title = f'{self.__input_column1}, {self.__input_column2} vs {self.__output_column}'

        if ax is None:
            ax = plt.axes(projection='3d')

        ax.set_xlabel(self.__input_column1)
        ax.set_ylabel(self.__input_column2)
        ax.set_zlabel(self.__output_column)

        ax.plot3D(self.__input_data1, self.__input_data2, self.__output_data, symbol, label=given_label)
        if surface_label is not None:
            fake2Dline = mpl.lines.Line2D([0], [0], linestyle="none", c='b', marker='o')
            ax.legend([fake2Dline], [surface_label], numpoints=1)
        else:
            ax.legend()
        ax.set_title(title)

        if show_plot:
            plt.show()

        return ax

    def split_into_training_and_validation(self, plot: bool = False,
                                           title: str = 'training data vs validation data'):
        if self.__training_set is None or self.__validation_set is None:
            indexes = [i for i in range(len(self.__input_data1))]
            training_sample = np.random.choice(indexes, int(0.8 * len(self.__input_data1)), replace=False)
            validation_sample = [i for i in indexes if i not in training_sample]

            training_inputs1 = [self.__input_data1[i] for i in training_sample]
            training_inputs2 = [self.__input_data2[i] for i in training_sample]
            training_outputs = [self.__output_data[i] for i in training_sample]

            validation_inputs1 = [self.__input_data1[i] for i in validation_sample]
            validation_inputs2 = [self.__input_data2[i] for i in validation_sample]
            validation_outputs = [self.__output_data[i] for i in validation_sample]

            self.__training_set = DataSet2Inputs(self.__input_column1, self.__input_column2, self.__output_column,
                                                 input_data1=training_inputs1, input_data2=training_inputs2,
                                                 output_data=training_outputs)

            self.__validation_set = DataSet2Inputs(self.__input_column1, self.__input_column2, self.__output_column,
                                                   input_data1=validation_inputs1, input_data2=validation_inputs2,
                                                   output_data=validation_outputs)

        if plot:
            ax = self.__training_set.plot_data_linearity(given_label='training data', show_plot=False)
            self.__validation_set.plot_data_linearity(symbol='g^', given_label='validation data',
                                                      title=title, ax=ax)

        return self.__training_set, self.__validation_set

    def apply_normalisation(self):
        self.split_into_training_and_validation()
        train_inputs = [[self.__training_set.input_data1[i], self.__training_set.input_data2[i]]
                        for i in range(len(self.__training_set.input_data1))]
        validation_inputs = [[self.__validation_set.input_data1[i], self.__validation_set.input_data2[i]]
                             for i in range(len(self.__validation_set.input_data1))]
        train_inputs, validation_inputs = normalise(train_inputs, validation_inputs)
        train_outputs, validation_outputs = normalise(self.__training_set.output_data,
                                                      self.__validation_set.output_data)

        self.__training_set = DataSet2Inputs(self.__input_column1, self.__input_column2, self.__output_column,
                                             input_data1=train_inputs[:, 0], input_data2=train_inputs[:, 1],
                                             output_data=train_outputs)

        self.__validation_set = DataSet2Inputs(self.__input_column1, self.__input_column2, self.__output_column,
                                               input_data1=validation_inputs[:, 0], input_data2=validation_inputs[:, 1],
                                               output_data=validation_outputs)

    def clear_training_and_validation_cache(self):
        self.__training_set = None
        self.__validation_set = None


class DataSetMultiOutput:
    def __init__(self, input_columns: list[str], output_columns: list[str], input_data: list[list[float]] | None = None,
                 output_data: list[list[float]] | None = None, file_name: str | None = None):
        self.__input_columns = input_columns
        self.__output_columns = output_columns

        if file_name is not None:
            data = []
            data_names = []

            if file_name is not None:
                with open(file_name) as file:
                    csv_reader = csv.reader(file)
                    for row in csv_reader:
                        if not data_names:
                            data_names = row
                        else:
                            data.append(row)

            self.__input_data = [[float(data[i][data_names.index(input_columns[j])]
                                        if data[i][data_names.index(input_columns[j])] != '' else 0)
                                  for j in range(len(input_columns))]
                                 for i in range(len(data))]

            self.__output_data = [[float(data[i][data_names.index(output_columns[j])]
                                         if data[i][data_names.index(output_columns[j])] != '' else 0)
                                   for j in range(len(output_columns))]
                                  for i in range(len(data))]

        else:
            self.__input_data = input_data
            self.__output_data = output_data

        self.__training_set = None
        self.__validation_set = None

    @property
    def input_data(self):
        return self.__input_data

    @property
    def output_data(self):
        return self.__output_data

    def split_into_training_and_validation(self):
        if self.__training_set is None or self.__validation_set is None:
            indexes = [i for i in range(len(self.__input_data))]
            training_sample = np.random.choice(indexes, int(0.8 * len(self.__input_data)), replace=False)
            validation_sample = [i for i in indexes if i not in training_sample]

            training_inputs = [self.__input_data[i] for i in training_sample]
            training_outputs = [self.__output_data[i] for i in training_sample]

            validation_inputs = [self.__input_data[i] for i in validation_sample]
            validation_outputs = [self.__output_data[i] for i in validation_sample]

            self.__training_set = DataSetMultiOutput(self.__input_columns, self.__output_columns,
                                                     input_data=training_inputs, output_data=training_outputs)

            self.__validation_set = DataSetMultiOutput(self.__input_columns, self.__output_columns,
                                                       input_data=validation_inputs, output_data=validation_outputs)

        return self.__training_set, self.__validation_set

    def apply_normalisation(self):
        self.split_into_training_and_validation()
        train_inputs, validation_inputs = normalise(self.__training_set.input_data, self.__validation_set.input_data)
        train_outputs, validation_outputs = normalise(self.__training_set.output_data, self.__validation_set.output_data)

        self.__training_set = DataSetMultiOutput(self.__input_columns, self.__output_columns,
                                                 input_data=train_inputs, output_data=train_outputs)

        self.__validation_set = DataSetMultiOutput(self.__input_columns, self.__output_columns,
                                                   input_data=validation_inputs, output_data=validation_outputs)

    def clear_training_and_validation_cache(self):
        self.__training_set = None
        self.__validation_set = None