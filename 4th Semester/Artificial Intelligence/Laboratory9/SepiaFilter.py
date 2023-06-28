import os

import cv2
from PIL import Image, ImageFilter, ImageOps, ImageEnhance
import numpy as np


IMAGE_SIZE = 64


def convert_directory_images_to_sepia():
    dir_path = 'data/original'

    for filename in os.listdir(dir_path):
        if filename.endswith('.jpg'):
            # Open the image file
            img_path = os.path.join(dir_path, filename)
            img = Image.open(img_path)

            # Apply the sepia filter
            img = ImageOps.grayscale(img)
            enhancer = ImageEnhance.Brightness(img)
            img = enhancer.enhance(1.2)
            enhancer = ImageEnhance.Contrast(img)
            img = enhancer.enhance(1.5)
            sepia_color_white = (240, 200, 160)
            sepia_color_black = (100, 60, 20)
            img = ImageOps.colorize(img, sepia_color_black, sepia_color_white)

            # Save the filtered image
            sepia_path = os.path.join('data/sepia', filename)
            img.save(sepia_path)


def process_image(path: str):
    img = Image.open(path)
    img = np.asarray(img)
    processed = []
    for i in img:
        processed += [i]
    return np.ravel(processed) / 255.0


def process_folder(is_cnn: bool = False):
    inputs_data = []
    outputs_data = []
    dir_paths = ['data/original', 'data/sepia']

    if not is_cnn:
        for label_value, dir_path in enumerate(dir_paths):
            for filename in os.listdir(dir_path):
                if filename.endswith('.jpg'):
                    inputs_data.append(process_image(os.path.join(dir_path, filename)))
                    outputs_data.append(label_value)
    else:
        for label_value, dir_path in enumerate(dir_paths):
            for img in os.listdir(dir_path):
                try:
                    img_arr = cv2.imread(os.path.join(dir_path, img))[..., ::-1]
                    resized_arr = cv2.resize(img_arr, (IMAGE_SIZE, IMAGE_SIZE))
                    inputs_data.append(resized_arr)
                    outputs_data.append(label_value)
                except Exception as e:
                    print(e)
        inputs_data = np.array(inputs_data) / 255.0
        inputs_data.reshape(-1, IMAGE_SIZE, IMAGE_SIZE, 1)
        outputs_data = np.array(outputs_data)

    return inputs_data, outputs_data


def load_sepia(is_cnn: bool = False):
    inputs_data, outputs_data = process_folder(is_cnn)
    return {
        'images': inputs_data,
        'target': outputs_data,
        'target_names': ['original', 'sepia']
    }
