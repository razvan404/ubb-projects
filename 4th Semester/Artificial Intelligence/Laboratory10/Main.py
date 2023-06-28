from sklearn import neural_network
from sklearn.datasets import load_iris

from DataSet import DataSet

from sklearn.cluster import KMeans

from KMeans import MyKMeans
from Plotter import Plotter
from Trainer import Trainer


def demo_iris(classifier: any = KMeans(algorithm='lloyd', copy_x=True, init='k-means++', max_iter=300,
                                       n_clusters=3, n_init=10, random_state=0, tol=0.0001, verbose=0),
              tool_type: str = 'by tool'):
    print('=' * 50)
    print(f'Predicting iris using k-means ({tool_type})')
    data = load_iris()
    inputs = data['data']
    outputs = data['target']
    feature_names = list(data['feature_names'])
    outputs_names = list(data['target_names'])
    print(outputs_names)
    dataset = DataSet(feature_names, 'target', outputs_names, input_data=inputs, output_data=outputs)
    dataset.apply_normalisation()
    trainer = Trainer(dataset, classifier)
    trainer.train_unsupervised()
    acc, precision, recall, conf_matrix = trainer.eval_model()
    print('Accuracy: ', acc)
    print('Precision: ', precision)
    print('Recall: ', recall)
    Plotter.plot_confusion_matrix(dataset, conf_matrix, f'KMeans iris {tool_type}')
    print('=' * 50)


def demo_email_spam(classifier: any = KMeans(algorithm='lloyd', copy_x=True, init='k-means++', max_iter=300,
                                             n_clusters=2, n_init=10, random_state=0, tol=0.0001, verbose=0),
                    tool_type: str = 'by tool'):
    print('=' * 50)
    print(f'Predicting emails using k-means ({tool_type})')
    dataset = DataSet(['emailText'], 'emailType', ['ham', 'spam'], file_name='data/spam.csv')
    dataset.extract_characteristics_using_fasttext()
    trainer = Trainer(dataset, classifier)
    trainer.train_unsupervised()
    acc, precision, recall, conf_matrix = trainer.eval_model()
    print('Accuracy: ', acc)
    print('Precision: ', precision)
    print('Recall: ', recall)
    Plotter.plot_confusion_matrix(dataset, conf_matrix, f'KMeans emails {tool_type}')
    print('=' * 50)


def demo_sentiments(unsupervised_classifier: any = KMeans(algorithm='lloyd', copy_x=True, init='k-means++',
                                                          max_iter=300, n_clusters=2, n_init=10, random_state=0,
                                                          tol=0.001, verbose=0),
                    supervised_classifier: any = neural_network.MLPClassifier(hidden_layer_sizes=(50,),
                                                                              activation='relu', solver='sgd',
                                                                              max_iter=2000),
                    mode: str = 'unsupervised', tool_type: str = 'by tool'):
    print('=' * 50)
    print(f'Predicting sentiments ({mode}, {tool_type})')
    dataset = DataSet(['Text'], 'Sentiment', ['negative', 'positive'], file_name='data/reviews_mixed.csv')
    dataset.extract_characteristics_using_bag_of_words()
    if mode == 'supervised':
        trainer = Trainer(dataset, supervised_classifier)
        trainer.train_supervised()
    elif mode == 'unsupervised':
        trainer = Trainer(dataset, unsupervised_classifier)
        trainer.train_unsupervised()
    elif mode == 'hybrid':
        trainer = Trainer(dataset, supervised_classifier)
        trainer.train_hybrid(unsupervised_classifier, percent=0.2)
    else:
        raise Exception('Invalid mode')
    acc, precision, recall, conf_matrix = trainer.eval_model()
    print('Accuracy: ', acc)
    print('Precision: ', precision)
    print('Recall: ', recall)
    Plotter.plot_confusion_matrix(dataset, conf_matrix, f'KMeans sentiments {mode} {tool_type}')
    print('=' * 50)


if __name__ == '__main__':
    # demo_iris(tool_type='by tool')
    # demo_iris(classifier=MyKMeans(n_clusters=3, max_iter=300, distance='euclidean'), tool_type='manual')

    # demo_email_spam(tool_type='by tool')
    # demo_email_spam(classifier=MyKMeans(n_clusters=2, max_iter=300, distance='cosine'), tool_type='manual')

    demo_sentiments(mode='unsupervised', tool_type='by tool')
    demo_sentiments(mode='supervised', tool_type='by tool')
    demo_sentiments(mode='hybrid', tool_type='by tool')
