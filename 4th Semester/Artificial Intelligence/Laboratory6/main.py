import os

from sklearn import linear_model
import matplotlib

from data_set import DataSet, DataSet2D
from my_regressor import MyLinearRegression2D
from trainer import LinearTrainer, LinearTrainer2D

matplotlib.use('TkAgg')


def demo(test_file: str, regressor: any = linear_model.LinearRegression()):
    print('=' * 50)
    crt_dir = os.getcwd()
    file_path = os.path.join(crt_dir, 'data', test_file)

    data_set = DataSet('Economy..GDP.per.Capita.', 'Happiness.Score', file_name=file_path)

    data_set.plot_histograms()
    data_set.plot_data_linearity()

    training_data, validation_data = data_set.split_into_training_and_validation()

    training_data.plot_data_linearity(given_label='training data', show_plot=False)
    validation_data.plot_data_linearity(symbol='g^', given_label='validation data',
                                        title='training data vs validation data')

    trainer = LinearTrainer(data_set, regressor)

    w0, w1 = trainer.get_learnt_model()
    print(f'Learnt model: f(x) = {w0} + {w1} * x')
    trainer.plot_results()
    trainer.plot_predicted_results()
    print(f'Prediction error: {trainer.compute_error()}')
    print('=' * 50)


def demo2(test_file: str, regressor: any = linear_model.LinearRegression(), text: str = 'by tool',
          extra_plots: bool = False):
    print('=' * 50)
    print(f' Testing {test_file} {text}:')
    crt_dir = os.getcwd()
    file_path = os.path.join(crt_dir, 'data', test_file)
    data_set = DataSet2D('Economy..GDP.per.Capita.', 'Freedom', 'Happiness.Score', file_name=file_path)

    if extra_plots:
        data_set.plot_histograms()
        data_set.plot_data_linearity()
        training_data, validation_data = data_set.split_into_training_and_validation(plot=True)
        trainer = LinearTrainer2D(regressor, training_set=training_data, validation_set=validation_data)
    else:
        trainer = LinearTrainer2D(regressor, data_set)

    w0, w1, w2 = trainer.get_learnt_model()

    print(f'Learnt model: f(x) = {w0} + {w1} * x1 + {w2} * x2')
    trainer.plot_results()
    trainer.plot_predicted_results()
    print(f'Prediction error: {trainer.compute_error()}')
    print('=' * 50)


if __name__ == '__main__':
    i = 3
    demo2(f'v{i}_world-happiness-report-2017.csv', MyLinearRegression2D(), 'with my linear regression',
          extra_plots=True)
    demo2(f'v{i}_world-happiness-report-2017.csv')
    # for i in range(1, 4):
    #     demo2(f'v{i}_world-happiness-report-2017.csv')
