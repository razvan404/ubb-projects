import numpy as np

from DataSet import DataSet

import matplotlib.pyplot as plt
import matplotlib as mpl

mpl.use('TkAgg')


class Plotter:
    @staticmethod
    def plot_confusion_matrix(dataset: DataSet, conf_matrix, title: str = None):
        import itertools

        classes = dataset.output_labels
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
