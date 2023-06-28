import os

from sklearn import linear_model
import matplotlib

from data_set import DataSet1Input, DataSet2Inputs, DataSetMultiOutput
from my_regressor import MySGDRegression, MyBatchGDRegression
from trainer import LinearTrainer1Input, LinearTrainer2Inputs, TrainerMultiOutput

matplotlib.use('TkAgg')


def demo1(test_file: str, regressor: any = linear_model.SGDRegressor(alpha=0.001, max_iter=1000), text: str = 'by tool',
          extra_plots: bool = False):
    print('=' * 50)
    print(f' Testing {test_file} {text}:')
    crt_dir = os.getcwd()
    file_path = os.path.join(crt_dir, 'data', test_file)

    data_set = DataSet1Input('Economy..GDP.per.Capita.', 'Happiness.Score', file_name=file_path)

    if extra_plots:
        data_set.plot_histograms()
        data_set.plot_data_linearity()

    data_set.split_into_training_and_validation(plot=True)
    data_set.apply_normalisation()
    data_set.split_into_training_and_validation(plot=True, title='training data vs validation data (normalised)')

    trainer = LinearTrainer1Input(data_set, regressor)

    w0, w1 = trainer.get_learnt_model()
    print(f'Learnt model: f(x) = {w0} + {w1} * x')
    trainer.plot_results()
    trainer.plot_predicted_results()
    print(f'Prediction error: {trainer.compute_error()}')
    print('=' * 50)


def demo2(test_file: str, regressor: any = linear_model.SGDRegressor(alpha=0.001, max_iter=1000), text: str = 'by tool',
          extra_plots: bool = False):
    print('=' * 50)
    print(f' Testing {test_file} {text}:')
    crt_dir = os.getcwd()
    file_path = os.path.join(crt_dir, 'data', test_file)
    data_set = DataSet2Inputs('Economy..GDP.per.Capita.', 'Freedom', 'Happiness.Score', file_name=file_path)

    if extra_plots:
        data_set.plot_histograms()
        data_set.plot_data_linearity()

    data_set.split_into_training_and_validation(plot=True)
    data_set.apply_normalisation()
    data_set.split_into_training_and_validation(plot=True, title='training data vs validation data (normalised)')

    trainer = LinearTrainer2Inputs(data_set, regressor)

    w0, w1, w2 = trainer.get_learnt_model()

    print(f'Learnt model: f(x) = {w0} + {w1} * x1 + {w2} * x2')
    trainer.plot_results()
    trainer.plot_predicted_results()
    print(f'Prediction error: {trainer.compute_error()}')
    print('=' * 50)


def demo_single_output_regression(demo_id: int):
    if demo_id == 1:
        demo = demo1
    elif demo_id == 2:
        demo = demo2
    else:
        raise ValueError('Invalid demo id')

    demo(f'world-happiness-report-2017.csv', extra_plots=True)
    demo(f'world-happiness-report-2017.csv', MySGDRegression(), text='with my batch gradient descent regression')


def demo_multi_output_regression():
    data_set = DataSetMultiOutput(input_columns=['Economy..GDP.per.Capita.', 'Freedom'],
                                  output_columns=['Happiness.Score', 'Trust..Government.Corruption.'],
                                  file_name='data/world-happiness-report-2017.csv')
    trainer = TrainerMultiOutput(data_set, linear_model.LinearRegression())
    for i, w in enumerate(trainer.get_learnt_model()):
        print(f'{i + 1}) Learnt model f(x) = {w[0]}', end='')
        for i in range(1, len(w)):
            print(f' + {w[i]} * x{i}', end='')
        print()
    for i, err in enumerate(trainer.compute_errors()):
        print(f'{i + 1}) Prediction error: {err}')


if __name__ == '__main__':
    demo_single_output_regression(demo_id=2)
    # demo_multi_output_regression()
