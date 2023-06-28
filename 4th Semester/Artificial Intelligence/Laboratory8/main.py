from sklearn import linear_model
from sklearn.datasets import load_breast_cancer, load_iris

from data_set import DataSet
from logistic_regression import MyLogisticRegressionMultiLabel
from plotter import Plotter
from trainer import Trainer


def demo_breast_cancer(classifier: any = linear_model.LogisticRegression(), tool_type: str = 'by tool',
                       extra_plots: bool = False):
    print('=' * 50)
    print(f'Predicting breast cancer using logistic regression ({tool_type})')
    data = load_breast_cancer()
    inputs = data['data']
    outputs = data['target']
    feature_names = list(data['feature_names'])
    outputs_names = list(data['target_names'])
    feature1 = [feat[feature_names.index('mean radius')] for feat in inputs]
    feature2 = [feat[feature_names.index('mean texture')] for feat in inputs]
    inputs = [[feat1, feat2] for (feat1, feat2) in zip(feature1, feature2)]

    dataset = DataSet(['mean radius', 'mean texture'], outputs_names, input_data=inputs, output_data=outputs)
    if extra_plots:
        Plotter.plot_histograms(dataset)
        Plotter.plot_data_scatter_2_features(dataset)
        training_data, validation_data = dataset.split_into_training_and_validation()
        Plotter.plot_data_scatter_2_features(training_data, title='Training data before normalization')
        Plotter.plot_data_scatter_2_features(validation_data, title='Validation data before normalization')

    training_data, validation_data = dataset.apply_normalisation()
    Plotter.plot_data_scatter_2_features(training_data, title='Training data after normalization')
    Plotter.plot_data_scatter_2_features(validation_data, title='Validation data after normalization')

    trainer = Trainer(dataset, classifier=classifier)
    w = trainer.get_model()
    print(f'Predicted model: f(x) = {w[0]} + {w[1]} * x1 + {w[2]} * x2')
    predictions = trainer.predict_outputs()
    Plotter.plot_trainer_predictions(validation_data, predicted_outputs=predictions, title='Model predictions')
    error = trainer.compute_error()
    print(f'Classification error: {error * 100}%')
    print('=' * 50)


def demo_iris(classifier: any = linear_model.LogisticRegression(), tool_type: str = 'by tool',
              extra_plots: bool = False):
    print(f'Predicting iris using logistic regression ({tool_type})')
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
    if extra_plots:
        Plotter.plot_histograms(dataset)
    dataset.apply_normalisation()
    trainer = Trainer(dataset, classifier=classifier)
    w = trainer.get_model()
    print(f'Predicted model for first label: f(x) = {w[0][0]} + {w[0][1]} * x1 + {w[0][2]} * x2'
          f' + {w[0][3]} * x3 + {w[0][4]} * x4')
    print(f'Predicted model for second label: f(x) = {w[1][0]} + {w[1][1]} * x1 + {w[1][2]} * x2'
          f' + {w[1][3]} * x3 + {w[1][4]} * x4')
    print(f'Predicted model for third label: f(x) = {w[2][0]} + {w[2][1]} * x1 + {w[2][2]} * x2'
          f' + {w[2][3]} * x3 + {w[2][4]} * x4')
    error = trainer.compute_error()
    print(f'Classification error: {round(error * 10 ** 4) / 10 ** 2}%')
    cross_validation_errors = trainer.cross_validation(sets_count=4)
    print(f'Cross validation errors: {round(cross_validation_errors[0] * 10 ** 4) / 10 ** 2}', end='%')
    for err in cross_validation_errors[1:]:
        print(f', {round(err * 10 ** 4) / 10 ** 2}', end='%')
    print()


if __name__ == '__main__':
    # demo_breast_cancer(extra_plots=False)
    # demo_breast_cancer(classifier=MyStochasticLogisticRegression(), tool_type='manual', extra_plots=False)

    # Logistic Classifier - Cross validation errors: 0.0%, 6.67%, 3.33%, 3.33%
    # demo_iris()

    # My Classifier with batches - Cross validation errors: 6.67%, 3.33%, 0.0%, 3.33%
    demo_iris(classifier=MyLogisticRegressionMultiLabel(no_epochs=2000, gd_type='batch'),
              tool_type='batch, manual', extra_plots=True)

    # Log loss SGD Classifier - Cross validation errors: 3.33%, 0.0%, 46.67%, 43.33%
    # demo_iris(classifier=linear_model.SGDClassifier(loss='log_loss'), tool_type='by tool, log loss')

    # Hinge loss SGD Classifier - Cross validation errors: 23.33%, 40.0%, 33.33%, 0.0%
    # demo_iris(classifier=linear_model.SGDClassifier(loss='hinge'), tool_type='by tool, hinge loss')

    # Huber's loss SGD Classifier - Cross validation errors: 63.33%, 10.0%, 76.67%, 76.67%
    # demo_iris(classifier=linear_model.SGDClassifier(loss='huber'), tool_type='by tool, squared loss')

    # Modified Huber loss SGD Classifier - Cross validation errors: 13.33%, 26.67%, 13.33%, 6.67%
    # demo_iris(classifier=linear_model.SGDClassifier(loss='modified_huber'), tool_type='by tool, modified huber loss')

    # Squared hinge loss SGD Classifier - Cross validation errors: 10.0%, 3.33%, 16.67%, 0.0%
    # demo_iris(classifier=linear_model.SGDClassifier(loss='squared_hinge'), tool_type='by tool, squared hinge loss')

    # Squared loss SGD Classifier - Cross validation errors: 70.0%, 50.0%, 83.33%, 50.0%
    # demo_iris(classifier=linear_model.SGDClassifier(loss='squared_error'), tool_type='by tool, squared error')

    # Perceptron loss SGD Classifier - Cross validation errors: 23.33%, 3.33%, 0.0%, 13.33%
    # demo_iris(classifier=linear_model.SGDClassifier(loss='perceptron'), tool_type='by tool, perceptron loss')

    # Epsilon insensitive loss SGD Classifier - Cross validation errors: 26.67%, 46.67%, 63.33%, 53.33%
    # demo_iris(classifier=linear_model.SGDClassifier(loss='epsilon_insensitive'),
    #           tool_type='by tool, epsilon insensitive loss')

    # Squared epsilon insensitive loss SGD Classifier - Cross validation errors: 56.67%, 63.33%, 86.67%, 46.67%
    # demo_iris(classifier=linear_model.SGDClassifier(loss='squared_epsilon_insensitive'),
    #           tool_type='by tool, squared epsilon insensitive loss')
