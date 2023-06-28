from cmath import log, exp
from typing import List


def multiclass_classification(real_data: List[str], computed_data: List[str], labels: List[str]):
    total_accuracy = sum([1 if real == comp else 0 for real, comp in zip(real_data, computed_data)]) \
                     / len(real_data[0])

    true_positive = {label: sum([1 if real == label and comp == label else 0
                                 for real, comp in zip(real_data, computed_data)]) for label in labels}
    false_positive = {label: sum([1 if real != label and comp == label else 0
                                  for real, comp in zip(real_data, computed_data)]) for label in labels}
    false_negative = {label: sum([1 if real == label and comp != label else 0
                                  for real, comp in zip(real_data, computed_data)]) for label in labels}
    true_negative = {label: sum([1 if real != label and comp != label else 0
                                 for real, comp in zip(real_data, computed_data)]) for label in labels}

    accuracy = {label: (true_positive[label] + true_negative[label]) / (true_positive[label] + true_negative[label] +
                                                                        false_positive[label] + false_negative[label])
                for label in labels}
    precisions = {label: true_positive[label] / (true_positive[label] + false_positive[label])
                  for label in labels}
    recalls = {label: true_positive[label] / (true_positive[label] + false_negative[label])
               for label in labels}
    return total_accuracy, accuracy, precisions, recalls


def binary_loss(real_data: List[str], computed_data: List[list], positive_label: str):
    # cross-entropy loss function, a good approximation for the true distribution
    classes = list(set(real_data))
    actual = [[1, 0] if label == positive_label else [0, 1] for label in real_data]
    dataset_classification = 0.0
    for i in range(len(real_data)):
        sample_classification = abs(sum([actual[i][j] * log(computed_data[i][j]) + (1 - actual[i][j])
                                         * (1 - log(computed_data[i][j])) for j in range(len(classes))]))
        dataset_classification += sample_classification
    return dataset_classification / len(real_data)


def loss_multiclass_classification(real_data, computed_data) -> float:
    # categorical cross-entropy
    classes_count = len(real_data)
    return -sum([real_data[i] * log(computed_data[i]) for i in range(classes_count)])


def loss_multilabel_classification(real_data, computed_data) -> float:
    labels_count = len(real_data)
    probs = [1 / (1 + exp(-value)) for value in computed_data]
    return -sum([real_data[i] * log(probs[i]) for i in range(labels_count)])
