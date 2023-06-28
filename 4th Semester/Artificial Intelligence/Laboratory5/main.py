from matplotlib import pyplot as plt

from classification import multiclass_classification, binary_loss, \
    loss_multiclass_classification, loss_multilabel_classification
from regression import mean_absolute_error, root_mean_absolute_error, regression_loss


def read_csv(filename: str, key=lambda x: int(x)):
    with open(filename) as f:
        features = f.readline().split(',')
        features[-1] = features[-1][:-1]
        result = {}
        for feature in features:
            result[feature] = []

        for line in f.readlines():
            attributes = line.split(',')
            for i in range(len(features) - 1):
                result[features[i]].append(key(attributes[i]))
            result[features[-1]].append(key(attributes[-1][:-1]))
        return result


def plot_predictions(real_data: list, computed_data: list, title: str):
    indexes = [i for i in range(len(real_data))]
    real, = plt.plot(indexes, real_data, 'ro', label='real')
    computed, = plt.plot(indexes, computed_data, 'bo', label='computed')
    plt.legend([real, (real, computed)], ["Real", "Computed"])
    plt.title(title)
    plt.show()


def demo1():
    print('Demo 1')
    sports = read_csv('data/sports.csv')
    print(' Mean absolute error: ', mean_absolute_error([sports['Weight'], sports['Waist'], sports['Pulse']],
                                                        [sports['PredictedWeight'], sports['PredictedWaist'],
                                                        sports['PredictedPulse']]))
    print(' Root mean absolute error: ', root_mean_absolute_error([sports['Weight'], sports['Waist'], sports['Pulse']],
                                                                  [sports['PredictedWeight'], sports['PredictedWaist'],
                                                                  sports['PredictedPulse']]))
    for label in ['Weight', 'Waist', 'Pulse']:
        plot_predictions(sports[label], sports[f'Predicted{label}'], f'Sports - {label} predictions ')


def demo2():
    print('Demo 2')
    flowers = read_csv('data/flowers.csv', key=lambda x: x)
    labels = list(set(flowers['Type']))
    total_accuracy, accuracy, precisions, recalls = multiclass_classification(flowers['Type'], flowers['PredictedType'], labels)
    print(f' Total accuracy: {total_accuracy}')
    for label in labels:
        print(f'  {label}:\n   Accuracy: {accuracy[label]} \n   Precision {precisions[label]}'
              f'\n   Recall {recalls[label]}')


def bonus1():
    print('Bonus 1')
    sports = read_csv('data/sports.csv')
    labels = ['Weight', 'Waist', 'Pulse']
    print(' Regression loss:', regression_loss(labels, {label: sports[label] for label in labels},
                                               {label: sports[f'Predicted{label}'] for label in labels}))


def bonus2():
    print('Bonus 2')
    real_values = ['spam', 'spam', 'ham', 'ham', 'spam', 'ham']
    computed_outputs = [[0.7, 0.3], [0.2, 0.8], [0.4, 0.6], [0.9, 0.1], [0.7, 0.3], [0.4, 0.6]]
    print(' Binary loss:', binary_loss(real_values, computed_outputs, 'spam'))


def bonus3():
    print('Bonus 3')
    real_data = [1, 0, 1, 0, 0]
    computed_data = [0.8, 0.2, 1.1, 0.7, 0.2]
    print(' Multi-class classification:', loss_multiclass_classification(real_data, computed_data))


def bonus4():
    print('Bonus 4')
    real_data = [1, 0, 1, 0, 0]
    computed_data = [0.8, 0.2, 1.1, 0.7, 0.2]
    print(' Multi-label classification:', loss_multilabel_classification(real_data, computed_data))


if __name__ == '__main__':
    demo1()
    demo2()
    bonus1()
    bonus2()
    bonus3()
    bonus4()
