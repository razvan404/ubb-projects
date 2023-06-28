import numpy as np

from DataSet import DataSet

import matplotlib.pyplot as plt
import matplotlib as mpl

mpl.use('TkAgg')


class Plotter:
    @staticmethod
    def plot_outputs_histogram(dataset: DataSet):
        plt.title('Histogram of outputs')
        plt.hist(dataset.output_data, bins=len(dataset.output_columns), rwidth=0.8)
        plt.xticks(np.arange(len(dataset.output_columns)), dataset.output_columns)
        plt.show()

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

    @staticmethod
    def plot_confusion_matrix(dataset: DataSet, conf_matrix, title: str = None):
        import itertools

        classes = dataset.output_columns
        plt.figure()
        plt.imshow(conf_matrix, interpolation='nearest', cmap='Blues')
        plt.title(f'Confusion Matrix {title}')
        plt.colorbar()
        tick_marks = np.arange(len(classes))
        plt.xticks(tick_marks, classes, rotation=45)
        plt.yticks(tick_marks, classes)

        fmt = '.2f'
        thresh = conf_matrix.max() / 2.
        for row, column in itertools.product(range(conf_matrix.shape[0]), range(conf_matrix.shape[1])):
            plt.text(column, row, format(conf_matrix[row, column], fmt),
                     horizontalalignment="center",
                     color="white" if conf_matrix[row, column] > thresh else "black")
        plt.xlabel('true label')
        plt.ylabel('predicted label')
        plt.tight_layout()

        plt.show()

