import csv

import numpy as np
from sklearn.preprocessing import StandardScaler


class DataSet:
    def __init__(self, input_columns: list[str], output_columns: list[str], input_data: list[list[float]] | None = None,
                 output_data: list[list[float]] | None = None, file_name: str | None = None):
        self.__input_columns = input_columns
        self.__output_columns = output_columns

        if file_name is not None:
            data = []
            data_names = []

            if file_name is not None:
                with open(file_name) as file:
                    csv_reader = csv.reader(file)
                    for row in csv_reader:
                        if not data_names:
                            data_names = row
                        else:
                            data.append(row)

            self.__input_data = [[float(data[i][data_names.index(input_columns[j])]
                                        if data[i][data_names.index(input_columns[j])] != '' else 0)
                                  for j in range(len(input_columns))]
                                 for i in range(len(data))]

            self.__output_data = [[float(data[i][data_names.index(output_columns[j])]
                                         if data[i][data_names.index(output_columns[j])] != '' else 0)
                                   for j in range(len(output_columns))]
                                  for i in range(len(data))]

        else:
            self.__input_data = input_data
            self.__output_data = output_data

        self.__training_set = None
        self.__validation_set = None

    @property
    def input_columns(self):
        return self.__input_columns

    @property
    def input_data(self):
        return self.__input_data

    def get_input_data(self, column_name: str):
        if column_name not in self.__input_columns:
            return None
        if not isinstance(self.__input_data[0], list):
            return self.__input_data
        return [el[self.__input_columns.index(column_name)] for el in self.__input_data]

    @property
    def output_columns(self):
        return self.__output_columns

    @property
    def output_data(self):
        return self.__output_data

    def get_output_data(self, column_name: str):
        if column_name not in self.__output_columns:
            return None
        if not isinstance(self.__output_data[0], list):
            return self.__output_data
        return [el[self.__output_columns.index(column_name)] for el in self.__output_data]

    def split_into_training_and_validation(self, validation_indexes: list[int] | None = None):
        if validation_indexes is not None:
            training_indexes = [i for i in range(len(self.__input_data)) if i not in validation_indexes]
            training_inputs = [self.__input_data[i] for i in training_indexes]
            training_outputs = [self.__output_data[i] for i in training_indexes]

            validation_inputs = [self.__input_data[i] for i in validation_indexes]
            validation_outputs = [self.__output_data[i] for i in validation_indexes]

            self.__training_set = DataSet(self.__input_columns, self.__output_columns,
                                          input_data=training_inputs, output_data=training_outputs)

            self.__validation_set = DataSet(self.__input_columns, self.__output_columns,
                                            input_data=validation_inputs, output_data=validation_outputs)
        elif self.__training_set is None or self.__validation_set is None:
            indexes = [i for i in range(len(self.__input_data))]
            training_sample = np.random.choice(indexes, int(0.8 * len(self.__input_data)), replace=False)
            validation_sample = [i for i in indexes if i not in training_sample]

            training_inputs = [self.__input_data[i] for i in training_sample]
            training_outputs = [self.__output_data[i] for i in training_sample]

            validation_inputs = [self.__input_data[i] for i in validation_sample]
            validation_outputs = [self.__output_data[i] for i in validation_sample]

            self.__training_set = DataSet(self.__input_columns, self.__output_columns,
                                          input_data=training_inputs, output_data=training_outputs)

            self.__validation_set = DataSet(self.__input_columns, self.__output_columns,
                                            input_data=validation_inputs, output_data=validation_outputs)

        return self.__training_set, self.__validation_set

    @staticmethod
    def normalise(training_data, validation_data):
        scaler = StandardScaler()
        if not isinstance(training_data, list):
            train_data = [[i] for i in training_data]
            validate_data = [[i] for i in validation_data]

            scaler.fit(train_data)
            normalised_train_data = scaler.transform(train_data)
            normalised_validate_data = scaler.transform(validate_data)

            normalised_train_data = [i[0] for i in normalised_train_data]
            normalised_validate_data = [i[0] for i in normalised_validate_data]
        else:
            scaler.fit(training_data)
            normalised_train_data = scaler.transform(training_data)
            normalised_validate_data = scaler.transform(validation_data)

        return normalised_train_data, normalised_validate_data

    def apply_normalisation(self):
        self.split_into_training_and_validation()
        train_inputs, validation_inputs = self.normalise(self.__training_set.input_data,
                                                         self.__validation_set.input_data)

        self.__training_set = DataSet(self.__input_columns, self.__output_columns,
                                      input_data=train_inputs, output_data=self.__training_set.output_data)

        self.__validation_set = DataSet(self.__input_columns, self.__output_columns,
                                        input_data=validation_inputs, output_data=self.__validation_set.output_data)

        return self.__training_set, self.__validation_set

    def clear_training_and_validation_cache(self):
        self.__training_set = None
        self.__validation_set = None
