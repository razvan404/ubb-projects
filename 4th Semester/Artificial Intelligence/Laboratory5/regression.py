from math import sqrt
from typing import List


def mean_absolute_error(real_data: List[list], computed_data: List[list]):
    error = 0
    for real, comp in zip(real_data, computed_data):
        for real_value, comp_value in zip(real, comp):
            error += abs(real_value - comp_value)
    return error / len(real_data[0])


def root_mean_absolute_error(real_data: List[list], computed_data: List[list]):
    error = 0
    for real, comp in zip(real_data, computed_data):
        for real_value, comp_value in zip(real, comp):
            error += (real_value - comp_value) ** 2
    return sqrt(error / len(real_data[0]))


def regression_loss(labels: List[str], real_data: dict, computed_data: dict):
    errors = {label: 0 for label in labels}
    for label in labels:
        for real_value, comp_value in zip(real_data[label], computed_data[label]):
            errors[label] += abs(real_value - comp_value) / len(real_data[label])
    return errors
