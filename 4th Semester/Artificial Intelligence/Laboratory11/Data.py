import os

import cv2
import numpy as np


def extract_face_manual(path, detector, image_size: tuple[int, int] = (64, 64)):
    image = cv2.imread(path)
    image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    faces = detector(image)
    if len(faces) == 0:
        return image
    face = faces[0]
    x1, y1, x2, y2 = max(face.left(), 0), max(face.top(), 0),\
        min(face.right(), image_size[0]), min(face.bottom(), image_size[1])
    return image[y1:y2, x1:x2]


def extract_face_pretrained(path, detector):
    image = detector.load_image_file(path)
    faces = detector.face_locations(image)
    if len(faces) == 0:
        return image
    face = faces[0]
    x1, y1, x2, y2 = max(face[3], 0), max(face[0], 0),\
        min(face[1], image.shape[1]), min(face[2], image.shape[0])
    return image[y1:y2, x1:x2]


def process_folders(folders: list[str], images_size: tuple[int, int] = (64, 64),
                    only_faces: bool = False, by_tool: bool = False):
    emojis = []
    labels = []
    labels_names = []
    if only_faces:
        if by_tool:
            import face_recognition # facenet
            for index_label, folder in enumerate(folders):
                label = folder.split('/')[-1]
                labels_names.append(label)
                for file in os.listdir(folder):
                    if file.endswith('.jpg') or file.endswith('.png'):
                        face = extract_face_pretrained(os.path.join(folder, file), face_recognition)
                        face = cv2.resize(face, images_size)
                        emojis.append(face)
                        labels.append(index_label)
        else:
            import dlib
            detector = dlib.get_frontal_face_detector()
            for index_label, folder in enumerate(folders):
                label = folder.split('/')[-1]
                labels_names.append(label)
                for file in os.listdir(folder):
                    if file.endswith('.jpg') or file.endswith('.png'):
                        face = extract_face_manual(os.path.join(folder, file), detector)
                        face = np.asarray(np.asarray([[[i, i, i] for i in row] for row in face]))
                        face = cv2.resize(face, images_size)
                        emojis.append(face)
                        labels.append(index_label)
    else:
        for index_label, folder in enumerate(folders):
            label = folder.split('/')[-1]
            labels_names.append(label)
            for file in os.listdir(folder):
                if file.endswith('.jpg') or file.endswith('.png'):
                    emoji = cv2.imread(os.path.join(folder, file))[..., ::-1]
                    # emoji = cv2.cvtColor(emoji, cv2.COLOR_BGR2GRAY)
                    emoji = cv2.resize(emoji, images_size)
                    emojis.append(emoji)
                    labels.append(index_label)
    np_emojis = np.asarray(emojis)
    np_labels = np.asarray(labels)
    p = np.random.permutation(len(emojis))
    return np_emojis[p], np_labels[p], labels_names


def normalise_images(images: np.ndarray, images_size: tuple[int, int] = (64, 64)):
    images = images / 255.0
    images.reshape(-1, images_size[0], images_size[1], 1)


def load_emojis(images_size: tuple[int, int] = (64, 64)):
    inputs, outputs, labels_ = process_folders(['data/emoticons/positive', 'data/emoticons/negative'], images_size)
    normalise_images(inputs, images_size)
    return {
        'images': inputs,
        'target': outputs,
        'features_names': 'emoji',
        'target_names': labels_
    }


def load_faces(images_size: tuple[int, int] = (64, 64), only_faces: bool = False, by_tool: bool = False):
    sentiments = ['angry', 'fear', 'happy', 'neutral', 'sad', 'surprise']
    inputs, outputs, labels_ = process_folders([f'data/faces/{sentiment}' for sentiment in sentiments],
                                               images_size, only_faces, by_tool)
    return {
        'images': inputs,
        'target': outputs,
        'features_names': 'face',
        'target_names': labels_
    }


def load_ubb(images_size: tuple[int, int] = (64, 64)):
    inputs, outputs, labels_ = process_folders(['data/ubb'], images_size)
    return {
        'images': inputs,
        'target': outputs,
        'features_names': 'face',
        'target_names': labels_
    }
