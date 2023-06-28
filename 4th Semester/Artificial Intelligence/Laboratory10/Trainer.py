import copy

import numpy as np

from DataSet import DataSet


class Trainer:
    def __init__(self, dataset: DataSet, classifier):
        self.__classifier = classifier
        self.__dataset = dataset
        self.__training_set, self.__validation_set = dataset.split_into_training_and_validation()

    def train_unsupervised(self):
        self.__classifier.fit(self.__training_set.input_data)

    def train_supervised(self):
        self.__classifier.fit(self.__training_set.input_data, self.__training_set.output_data)

    def train_hybrid(self, unsupervised_classifier, percent: float = 0.5):
        data_size = len(self.__training_set.input_data)
        classified_data = self.__training_set.input_data[:int(data_size * percent)]
        classified_output = self.__training_set.output_data[:int(data_size * percent)]
        unclassified_data = self.__training_set.input_data[int(data_size * percent):]

        self.__classifier.fit(classified_data, classified_output)
        unsupervised_classifier.fit(unclassified_data)
        unclassified_output = unsupervised_classifier.predict(unclassified_data)
        self.__classifier.partial_fit(unclassified_data, unclassified_output)

    def classification(self) -> list:
        return self.__classifier.predict(self.__validation_set.input_data)

    def eval_model(self, computed_outputs: list = None) -> (int, dict, dict, np.ndarray):
        from sklearn.metrics import confusion_matrix

        labels = self.__dataset.output_labels

        output_data = self.__validation_set.output_data
        if isinstance(self.__validation_set.output_data[0], np.int32) or \
                isinstance(self.__validation_set.output_data[0], int):
            output_data = [labels[el] for el in output_data]

        if computed_outputs is None:
            computed_outputs = self.classification()

        if isinstance(computed_outputs[0], np.int32) or isinstance(computed_outputs[0], np.int64):
            # we associate a label to the most frequent output
            feat_label = {}
            for label in labels:
                counts = []
                for j in range(max(computed_outputs) + 1):
                    count_same = 0
                    for real, comp in zip(output_data, computed_outputs):
                        if real == label and comp == j:
                            count_same += 1
                    counts += [(j, count_same)]
                counts = sorted(counts, key=lambda x: x[1], reverse=True)
                while len(counts) > 0 and counts[0][0] in feat_label:
                    counts.pop(0)
                if len(counts) > 0:
                    feat_label[counts[0][0]] = label
            computed_outputs_labels = [feat_label[el] for el in computed_outputs]
        else:
            computed_outputs_labels = computed_outputs

        print(f'Computed outputs: {computed_outputs_labels}')
        print(f'Expected outputs: {output_data}')

        conf_matrix = confusion_matrix(y_true=output_data, y_pred=computed_outputs_labels)
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
    