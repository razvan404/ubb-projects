from data_set import DataSet

import matplotlib.pyplot as plt
import matplotlib as mpl

mpl.use('TkAgg')


class Plotter:
    @staticmethod
    def plot_data_histogram(dataset: DataSet, column_name: str):
        plt.title(f'Histogram of {column_name}')
        if column_name in dataset.input_columns:
            plt.hist(dataset.get_input_data(column_name), bins=10)
        else:
            plt.hist(dataset.output_data, bins=10)
        plt.show()

    @staticmethod
    def plot_histograms(dataset: DataSet):
        for column_name in dataset.input_columns:
            Plotter.plot_data_histogram(dataset, column_name)
        Plotter.plot_data_histogram(dataset, 'target variable')

    @staticmethod
    def plot_data_scatter_2_features(dataset: DataSet, title: str = None, show: bool = True):
        labels = sorted(set(dataset.output_data))
        no_data = len(dataset.input_data)
        for idx, crt_label in enumerate(labels):
            x = [dataset.input_data[i][0] for i in range(no_data) if dataset.output_data[i] == crt_label]
            y = [dataset.input_data[i][1] for i in range(no_data) if dataset.output_data[i] == crt_label]
            plt.scatter(x, y, label=dataset.output_columns[idx])
        plt.xlabel(dataset.input_columns[0])
        plt.ylabel(dataset.input_columns[1])
        if title is not None:
            plt.title(title)
        plt.legend()
        if show:
            plt.show()

    @staticmethod
    def plot_trainer_predictions(dataset: DataSet, predicted_outputs, title: str = None):
        labels = sorted(set(dataset.output_data))
        no_data = len(dataset.input_data)
        for idx, crt_label in enumerate(labels):
            x = [dataset.input_data[i][0] for i in range(no_data) if dataset.output_data[i] == crt_label
                 and predicted_outputs[i] == crt_label]
            y = [dataset.input_data[i][1] for i in range(no_data) if dataset.output_data[i] == crt_label
                 and predicted_outputs[i] == crt_label]
            plt.scatter(x, y, label=dataset.output_columns[idx] + ' correct')
        for idx, crt_label in enumerate(labels):
            x = [dataset.input_data[i][0] for i in range(no_data) if dataset.output_data[i] == crt_label
                 and predicted_outputs[i] != crt_label]
            y = [dataset.input_data[i][1] for i in range(no_data) if dataset.output_data[i] == crt_label
                 and predicted_outputs[i] != crt_label]
            plt.scatter(x, y, label=dataset.output_columns[idx] + ' wrong')
        plt.xlabel(dataset.input_columns[0])
        plt.ylabel(dataset.input_columns[1])
        if title is not None:
            plt.title(title)
        plt.legend()
        plt.show()
