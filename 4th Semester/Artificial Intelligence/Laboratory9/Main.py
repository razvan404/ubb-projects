from sklearn import neural_network

from DataSet import DataSet
from NeuralNetwork import get_cnn_classifier, NeuralNetwork
from Plotter import Plotter
from Trainer import Trainer


def get_dataset(data: str):
    if data == 'iris':
        from sklearn.datasets import load_iris
        data = load_iris()
        inputs = data['data']
        outputs = data['target']
        feature_names = list(data['feature_names'])
        outputs_names = list(data['target_names'])

        features = []
        for feature in feature_names:
            features.append([feat[feature_names.index(feature)] for feat in inputs])
        inputs = [[feat1, feat2, feat3, feat4] for (feat1, feat2, feat3, feat4) in zip(*features)]

        dataset = DataSet(feature_names, outputs_names, input_data=inputs, output_data=outputs)

    elif data == 'digits':
        from sklearn.datasets import load_digits
        data = load_digits()
        inputs = data.images
        inputs = [el.flatten() for el in inputs]
        outputs = data['target']
        feature_names = ['image']
        outputs_names = list(data['target_names'])
        dataset = DataSet(feature_names, outputs_names, input_data=inputs, output_data=outputs)

    elif data == 'sepia':
        from SepiaFilter import load_sepia
        data = load_sepia()
        inputs = data['images']
        outputs = data['target']
        feature_names = ['image']
        outputs_names = list(data['target_names'])
        dataset = DataSet(feature_names, outputs_names, input_data=inputs, output_data=outputs,
                          is_cnn=True)

    elif data == 'sepia-cnn':
        from SepiaFilter import load_sepia
        data = load_sepia(True)
        inputs = data['images']
        outputs = data['target']
        feature_names = ['image']
        outputs_names = list(data['target_names'])
        dataset = DataSet(feature_names, outputs_names, input_data=inputs, output_data=outputs,
                          is_cnn=True)

    else:
        raise ValueError('Invalid data type')

    return dataset


def demo(classifier: any = neural_network.MLPClassifier(hidden_layer_sizes=(5,), activation='relu', max_iter=2000,
                                                        solver='sgd'), data: str = 'iris',
         tool_type: str = 'by tool', extra_plots: bool = False, is_cnn: bool = False):
    print('=' * 50)
    print(f'Predicting {data} using a neural network ({tool_type})')

    dataset = get_dataset(data)

    if extra_plots:
        Plotter.plot_outputs_histogram(dataset)
    dataset.apply_normalisation()
    trainer = Trainer(dataset, classifier=classifier)
    trainer.train(is_cnn)
    computed_outputs = trainer.classification()
    acc, precision, recall, conf_matrix = trainer.eval_model(computed_outputs, is_cnn=is_cnn)
    print(f'Accuracy: {acc}')
    print(f'Precision: {precision}')
    print(f'Recall: {recall}')
    Plotter.plot_confusion_matrix(dataset, conf_matrix, tool_type)
    print('=' * 50)


if __name__ == '__main__':
    demo(data='iris', extra_plots=True)
    demo(classifier=NeuralNetwork(), data='iris', tool_type='manual')

    demo(data='digits', extra_plots=True)
    demo(classifier=NeuralNetwork(), data='digits', tool_type='manual')

    # convert_directory_images_to_sepia()
    demo(data='sepia', extra_plots=True)
    demo(classifier=get_cnn_classifier(), data='sepia-cnn', is_cnn=True)
