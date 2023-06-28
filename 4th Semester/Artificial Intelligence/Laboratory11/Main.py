from fer import FER

from Classifiers import get_cnn_classifier
from Data import load_emojis, load_faces, load_ubb
from DataSet import DataSet
from Plotter import Plotter
from Trainer import Trainer


def get_dataset(problem: str):
    if problem == 'emojis' or problem == 'faces' or problem == 'only_faces' or problem == 'only_faces_tool':
        data = load_emojis() if problem == 'emojis' \
            else load_faces((96, 96)) if problem == 'faces' \
            else load_faces(only_faces=True) if problem == 'only_faces' \
            else load_faces(only_faces=True, by_tool=True)
        inputs = data['images']
        outputs = data['target']
        features_names = data['features_names']
        labels_name = data['target_names']
        return DataSet(features_names, 'sentiment', labels_name, input_data=inputs, output_data=outputs)
    else:
        return None


def demo_emoticons():
    # emojis classifications
    print('=' * 50)
    print('EMOJIS CLASSIFICATION')
    dataset = get_dataset('emojis')
    trainer = Trainer(dataset, get_cnn_classifier(outputs_count=2))
    trainer.train_supervised()
    acc, precision, recall, conf_matrix = trainer.eval_model()
    print(f'Accuracy: {acc}')
    print(f'Precision: {precision}')
    print(f'Recall: {recall}')
    Plotter.plot_confusion_matrix(dataset, conf_matrix, title='Emojis')
    print('=' * 50)


def demo_faces_with_fer():
    # faces fer classifications
    print('=' * 50)
    print('FACES CLASSIFICATION WITH FER')
    dataset = get_dataset('faces')
    trainer = Trainer(dataset, FER(mtcnn=True))
    computed_outputs = trainer.classification_fer()
    acc, precision, recall, conf_matrix = trainer.eval_model(computed_outputs=computed_outputs)
    print(f'Accuracy: {acc}')
    print(f'Precision: {precision}')
    print(f'Recall: {recall}')
    Plotter.plot_confusion_matrix(dataset, conf_matrix, title='Faces')
    print('=' * 50)


def demo_faces_with_face_detection_manual():
    # faces using face detection classifications
    print('=' * 50)
    print('FACES CLASSIFICATION WITH FACE DETECTION MANUAL')
    dataset = get_dataset('only_faces')
    trainer = Trainer(dataset, get_cnn_classifier(outputs_count=6))
    trainer.train_supervised()
    acc, precision, recall, conf_matrix = trainer.eval_model()
    print(f'Accuracy: {acc}')
    print(f'Precision: {precision}')
    print(f'Recall: {recall}')
    Plotter.plot_confusion_matrix(dataset, conf_matrix, title='Faces')
    print('=' * 50)


def demo_faces_with_face_detection_by_tool():
    # faces using face detection classifications
    print('=' * 50)
    print('FACES CLASSIFICATION WITH FACE DETECTION BY TOOL')
    dataset = get_dataset('only_faces_tool')
    trainer = Trainer(dataset, get_cnn_classifier(outputs_count=6))
    trainer.train_supervised(is_cnn=True, epochs=100)
    acc, precision, recall, conf_matrix = trainer.eval_model()
    print(f'Accuracy: {acc}')
    print(f'Precision: {precision}')
    print(f'Recall: {recall}')
    Plotter.plot_confusion_matrix(dataset, conf_matrix, title='Faces')
    print('=' * 50)


def demo_faces_with_fer_multilabel():
    # faces fer multilabel classifications
    print('=' * 50)
    print('FACES CLASSIFICATION WITH FER MULTILABEL')
    dataset = get_dataset('faces')
    trainer = Trainer(dataset, FER(mtcnn=True))
    trainer.classification_fer(threshold=0.2)
    print('=' * 50)


def demo_ubb():
    print('=' * 50)
    data = load_ubb((256, 256))
    threshold = 0.2
    detector = FER(mtcnn=True)
    for index, inp in enumerate(data['images']):
        emotions = detector.detect_emotions(inp)[0]['emotions']
        selected_emotions = [(emotion, emotions[emotion]) for emotion in emotions if emotions[emotion] > threshold]
        print(f'Image {index}: {selected_emotions}')
        Plotter.plot_image(inp, title=str(selected_emotions))
    print('=' * 50)


if __name__ == '__main__':
    demo_faces_with_face_detection_by_tool()
