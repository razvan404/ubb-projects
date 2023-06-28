import random
import warnings

import numpy as np
from DataSet import DataSet
from Plotter import Plotter

warnings.filterwarnings("ignore")


class Trainer:
    def __init__(self, dataset: DataSet, classifier):
        self.__classifier = classifier
        self.__dataset = dataset
        self.__training_set, self.__validation_set = dataset.split_into_training_and_validation()

    def train_unsupervised(self):
        self.__classifier.fit(self.__training_set.input_data)

    def train_supervised(self, is_cnn: bool = True, epochs: int = 20):
        if is_cnn:
            self.__classifier.fit(self.__training_set.input_data, self.__training_set.output_data,
                                  epochs=epochs, batch_size=32, verbose=0)
        else:
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
        return [np.argmax(i) for i in self.__classifier.predict(self.__validation_set.input_data)]

    def classification_fer(self, threshold: float = None) -> list:
        if threshold is None:
            computed = []
            for index, inp in enumerate(self.__validation_set.input_data):
                emotion, score = self.__classifier.top_emotion(inp)
                print(f'Image {index}: {emotion} - {score}')
                Plotter.plot_image(inp, title=emotion)
                if emotion:
                    computed.append(self.__validation_set.output_labels.index(emotion))
                else:
                    computed.append(random.randint(0, len(self.__validation_set.output_labels) - 1))
            return computed
        else:
            for index, inp in enumerate(self.__validation_set.input_data):
                emotions = self.__classifier.detect_emotions(inp)[0]['emotions']
                selected_emotions = [(emotion, emotions[emotion]) for emotion in emotions
                                     if emotions[emotion] > threshold]
                print(f'Image {index}: {selected_emotions}')
                Plotter.plot_image(inp, title=str(selected_emotions))
                if index % 7 == 0 and index > 0:
                    input('Press enter to continue . . . ')

    def eval_model(self, computed_outputs: list = None) -> (int, dict, dict, np.ndarray):
        from sklearn.metrics import confusion_matrix

        labels = self.__dataset.output_labels
        output_data = self.__validation_set.output_data
        if computed_outputs is None:
            computed_outputs = self.classification()
        print(f'Computed outputs: {computed_outputs}')
        print(f'Expected outputs: {output_data}')

        conf_matrix = confusion_matrix(y_true=output_data, y_pred=computed_outputs)
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
