import os.path

from matplotlib import pyplot as plt
from sklearn.metrics import ConfusionMatrixDisplay
from typing import List

from core.config import CONFIG


class PlotVisualizer:
    @classmethod
    def plot_history(cls, history: List[float], title: str):
        plt.plot(history)
        plt.title(title)

    @classmethod
    def plot_many(cls, dims: (int, int), *args, filename: str = None):
        assert dims[0] * dims[1] == len(args)
        for idx, arg in enumerate(args, start=1):
            plt.subplot(*dims, idx)
            arg()
        if filename is None:
            plt.show()
        else:
            plt.savefig(os.path.join(CONFIG.save_plots_location(), filename))

    @classmethod
    def plot_confusion_matrix(
        cls, confusion_matrix: List[List[int]], labels: List[str], filename: str = None
    ):
        ConfusionMatrixDisplay(confusion_matrix, display_labels=labels).plot()
        if filename is None:
            plt.show()
        else:
            plt.savefig(os.path.join(CONFIG.save_plots_location(), filename))
