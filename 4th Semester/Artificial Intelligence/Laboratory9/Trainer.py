import numpy as np

from DataSet import DataSet


class Trainer:
    def __init__(self, dataset: DataSet, classifier):
        self.__classifier = classifier
        self.__dataset = dataset
        self.__training_set, self.__validation_set = dataset.split_into_training_and_validation()

    def train(self, is_cnn: bool = False) -> None:
        if not is_cnn:
            self.__classifier.fit(self.__training_set.input_data, self.__training_set.output_data)
        else:
            self.__classifier.fit(self.__training_set.input_data, self.__training_set.output_data, epochs=10,
                                  batch_size=32)

    def classification(self) -> list:
        return self.__classifier.predict(self.__validation_set.input_data)

    def eval_model(self, computed_outputs: list = None, is_cnn: bool = False) -> (int, dict, dict, np.ndarray):
        from sklearn.metrics import confusion_matrix

        labels = self.__dataset.output_columns
        if computed_outputs is None:
            computed_outputs = self.classification()
        if is_cnn:
            computed_outputs = [np.argmax(i) for i in computed_outputs]
        conf_matrix = confusion_matrix(self.__validation_set.output_data, computed_outputs)
        acc = sum([conf_matrix[i][i] for i in range(len(labels))]) / len(computed_outputs)
        precision = {}
        recall = {}

        for i in range(len(labels)):
            try:
                precision[labels[i]] = conf_matrix[i][i] / sum([conf_matrix[j][i] for j in range(len(labels))])
            except any:
                precision[labels[i]] = 0
            try:
                recall[labels[i]] = conf_matrix[i][i] / sum([conf_matrix[i][j] for j in range(len(labels))])
            except any:
                recall[labels[i]] = 0

        return acc, precision, recall, conf_matrix
