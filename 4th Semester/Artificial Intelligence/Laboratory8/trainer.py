import numpy as np

from data_set import DataSet


class Trainer:
    def __init__(self, dataset: DataSet, classifier):
        self.__classifier = classifier
        self.__dataset = dataset
        self.__training_set, self.__validation_set = dataset.split_into_training_and_validation()

    def get_model(self):
        self.__classifier.fit(self.__training_set.input_data, self.__training_set.output_data)
        w = [[self.__classifier.intercept_[i]] + list(self.__classifier.coef_[i])
             for i in range(len(self.__classifier.coef_))]
        return w

    def predict_outputs(self):
        return self.__classifier.predict(self.__validation_set.input_data)

    def compute_error(self, computed_outputs: list = None):
        if computed_outputs is None:
            computed_outputs = self.predict_outputs()
        error = 0.0
        for t1, t2 in zip(computed_outputs, self.__validation_set.output_data):
            if t1 != t2:
                error += 1.0
        error /= len(self.__validation_set.output_data)
        return error

    def cross_validation(self, sets_count: int):
        indexes = [i for i in range(len(self.__training_set.input_data))]
        index_sets = [[] for _ in range(sets_count)]

        index_sets[0] = list(np.random.choice(indexes, int(1.0 / sets_count * len(self.__training_set.input_data)),
                                              replace=False))
        used = list(index_sets[0])
        for j in range(1, sets_count):
            index_sets[j] = list(np.random.choice([i for i in indexes if i not in used],
                                                  int(1.0 / sets_count * len(self.__training_set.input_data)),
                                                  replace=False))
            used += list(index_sets[j])

        errors = []
        for index_set in index_sets:
            self.__training_set, self.__validation_set = self.__dataset \
                .split_into_training_and_validation(validation_indexes=index_set)
            self.get_model()
            errors.append(self.compute_error())
        return errors
