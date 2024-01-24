import torch
import numpy as np

from sklearn.metrics import confusion_matrix as sk_confusion_matrix


def confusion_matrix(y_real: np.ndarray, y_pred: np.ndarray):
    if y_real is None or y_pred is None:
        raise ValueError(
            "Both the real outputs and the predicted outputs should be given as parameters!"
        )
    return sk_confusion_matrix(y_real.flatten(), y_pred.flatten())


def mean_pixels_accuracy(
    y_real: np.ndarray = None,
    y_pred: np.ndarray = None,
    conf_matrix: np.ndarray = None,
):
    if conf_matrix is None:
        conf_matrix = confusion_matrix(y_real, y_pred)
    right_pixels = np.sum(np.diag(conf_matrix))
    total_pixels = np.sum(conf_matrix)
    return right_pixels / total_pixels


def intersection_over_union(
    y_real: np.ndarray = None, y_pred: np.ndarray = None, conf_matrix: np.ndarray = None
):
    if conf_matrix is None:
        conf_matrix = confusion_matrix(y_real, y_pred)
    diag = np.diag(conf_matrix)
    return np.mean(
        diag / (np.sum(conf_matrix, axis=0) - diag + np.sum(conf_matrix, axis=1))
    )


def frequency_weighted_intersection_over_union(
    y_real: np.ndarray = None, y_pred: np.ndarray = None, conf_matrix: np.ndarray = None
):
    if conf_matrix is None:
        conf_matrix = confusion_matrix(y_real, y_pred)
    diag = np.diag(conf_matrix)
    classes_counts = np.sum(conf_matrix, axis=0)
    return np.sum(
        classes_counts * diag / (classes_counts - diag + np.sum(conf_matrix, axis=1))
    ) / np.sum(classes_counts)


def test_metrics():
    img_size = 100
    num_classes = 5
    y_real = torch.randint(num_classes, (img_size, img_size)).numpy()
    y_pred = torch.randint(num_classes, (img_size, img_size)).numpy()
    conf_matrix = confusion_matrix(y_real, y_pred)

    print("Confusion matrix:", conf_matrix, sep="\n")
    print("Mean pixels accuracy:", mean_pixels_accuracy(conf_matrix=conf_matrix))
    print("Intersection over union:", intersection_over_union(conf_matrix=conf_matrix))
    print(
        "Frequency weighted intersection over union",
        frequency_weighted_intersection_over_union(conf_matrix=conf_matrix),
    )


if __name__ == "__main__":
    test_metrics()
